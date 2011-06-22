//------------------------------------------------------------------------
//    This file is part of Geoix.
//
//    Copyright (C) 2010 Dmitriy Pinaev
//
//    Geoix is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Geoix is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------

#include <QtCore>

#include "spliner_dialog.h"
#include "ui_spliner_dialog.h"

#include "tree_folder_object.h"
#include "visual_object.h"
#include "surface_data.h"

#include "rbf_mapper.h"
#include "kriging_mapper.h"
#include "sgs_2d_mapper.h"
#include "local_b_spline_mapper.h"

/// Constructor. Creates Dialog window for spline calculations
gxSplinerDialog::gxSplinerDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowStaysOnTopHint),
    ui(new Ui::SplinerDialog),
    folder(0)
{
    ui->setupUi(this);

    // adding mappers
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxRBFMapper()));
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxKrigingMapper()));
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxSGS2DMapper()));
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxLocalBSplineMapper()));

    // adding mappers' names
    foreach(QSharedPointer<gxAbstractMapper> mapper, mapperList)
    {
        ui->mappersComboBox->addItem(mapper.data()->getName());
    }

    setupMapper(0);

    /// setting up event filter
    ui->listWidget->installEventFilter(this);
    ui->listWidget->setAcceptDrops(true);

    ui->lineMinX->setValidator(new QDoubleValidator(this));
    ui->lineMaxX->setValidator(new QDoubleValidator(this));
    ui->lineMinY->setValidator(new QDoubleValidator(this));
    ui->lineMaxY->setValidator(new QDoubleValidator(this));
    ui->lineX->setValidator(new QDoubleValidator(this));
    ui->lineY->setValidator(new QDoubleValidator(this));
}

gxSplinerDialog::~gxSplinerDialog()
{
    delete ui;
}


//------------------------------------------------------------------------------

bool gxSplinerDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->listWidget)
    {
        switch (event->type())
        {
        case QEvent::DragEnter:
            {
                QDragEnterEvent *eventEnter = static_cast<QDragEnterEvent*>(event);
                return handleDragEnterEvent(eventEnter);
            }
        case QEvent::Drop:
            {
                QDropEvent *dropEvent = static_cast<QDropEvent*>(event);
                return handleDropEvent(dropEvent);
            }
        default: break;
        }
        return false;
    }
    else
    {
        // pass the event on to the parent class
        return QDialog::eventFilter(obj, event);
    }
}


//------------------------------------------------------------------------------


bool gxSplinerDialog::handleDragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/surface")
        || event->mimeData()->hasFormat("geoix/lines")
        || event->mimeData()->hasFormat("geoix/points"))
    {
        event->setDropAction(Qt::CopyAction);
        event->accept();
        return true;
    }
    else
    {
        event->ignore();
        return false;
    }
}



//------------------------------------------------------------------------------


bool gxSplinerDialog::handleDropEvent(QDropEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();

    foreach(QString format, event->mimeData()->formats())
    {
        const QMimeData *mimeData = event->mimeData();
        QByteArray encodedData = mimeData->data(format);

        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd())
        {
            quint64 pointer;
            stream >> pointer;

            gxTreeAbstractObject *abstractObject = reinterpret_cast<gxTreeAbstractObject*>(pointer);

            folder = abstractObject->getParent();

            this->objectList.append(abstractObject->getSharedPointer());
            ui->listWidget->addItem(abstractObject->getName());

            gxVisualObject *vo = static_cast<gxVisualObject*>(abstractObject);
            gxSize3D size = vo->getSize();

            this->ui->lineMinX->setText(QString::number(size.getMinX()));
            this->ui->lineMaxX->setText(QString::number(size.getMaxX()));
            this->ui->lineMinY->setText(QString::number(size.getMinY()));
            this->ui->lineMaxY->setText(QString::number(size.getMaxY()));

        }
    }

    return true;
}

//------------------------------------------------------------------------------

void gxSplinerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------

void gxSplinerDialog::setupMapper(int index)
{
    QWidget *settingsWidget = mapperList[index].data()->getSettingsWidget();

    // remove previous widget
    if (ui->settingsLayout->count())
    {
        QWidget * w = ui->settingsLayout->takeAt(0)->widget();
        delete w;
    }


    if (settingsWidget)
    {
        // add new widget
        ui->settingsLayout->addWidget(settingsWidget);
        ui->settingsLayout->invalidate();
    }
}


//                               slots
//------------------------------------------------------------------------------


void gxSplinerDialog::cleanup()
{
    this->objectList.clear();
    ui->listWidget->clear();
    // do nothing
}


//------------------------------------------------------------------------------


void gxSplinerDialog::onCalculate()
{
    // 1) first we get points

    gxPoint3DList allPoints;

    QListIterator<QSharedPointer<gxTreeAbstractObject> > it(this->objectList);
    while (it.hasNext())
    {
        gxVisualObject *v = static_cast<gxVisualObject*>(it.next().data());
        allPoints += v->getPoint3DList();
    }
    int index = this->ui->mappersComboBox->currentIndex();

    // 2) then, get size
    gxSize3D size;
    bool ok;
    double val;
    val = ui->lineMinX->text().toDouble(&ok); size.setMinX(val);
    val = ui->lineMaxX->text().toDouble(&ok); size.setMaxX(val);
    val = ui->lineMinY->text().toDouble(&ok); size.setMinY(val);
    val = ui->lineMaxY->text().toDouble(&ok); size.setMaxY(val);

    // 3) get cell dimensions
    double dX = ui->lineX->text().toDouble(&ok);
    double dY = ui->lineY->text().toDouble(&ok);

    // 4) correct size
    int nx = floor(size.getW()/dX + 0.5);
    int ny = floor(size.getH()/dY + 0.5);

    size.setMaxX(size.getMinX() + nx * dX);
    size.setMaxY(size.getMinY() + ny * dY);

    // 5) calc

    QVector<double> result;
    mapperList[index]->calcSurface(allPoints, size, nx + 1, ny + 1, result);

    gxSurfaceData *data = new gxSurfaceData(size);
    data->setnXY(nx + 1, ny + 1);
    data->setData(result);

    if (folder)
        folder->createSurface(data, this->ui->lineName->text());
}
