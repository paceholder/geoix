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

#include "visual_object.h"
#include "rbf_mapper.h"
#include "kriging_mapper.h"

/// Constructor. Creates Dialog window for spline calculations
spliner_dialog::spliner_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spliner_dialog)
{
    ui->setupUi(this);

    // adding mappers
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxRBFMapper()));
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxKrigingMapper()));

    // adding mappers' names
    foreach(QSharedPointer<gxAbstractMapper> mapper, mapperList)
    {
        ui->mappersComboBox->addItem(mapper.data()->getName());
    }

    setupMapper(0);

    /// setting up event filter
    ui->listWidget->installEventFilter(this);
    ui->listWidget->setAcceptDrops(true);
}

spliner_dialog::~spliner_dialog()
{
    delete ui;
}


//------------------------------------------------------------------------------

bool spliner_dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->listWidget)
    {
        switch (event->type())
        {
        case QEvent::DragEnter:
        {
            QDragEnterEvent *eventEnter = static_cast<QDragEnterEvent*>(event);

            if (eventEnter->mimeData()->hasFormat("geoix/surface")
                || eventEnter->mimeData()->hasFormat("geoix/lines")
                || eventEnter->mimeData()->hasFormat("geoix/points"))
            {
                eventEnter->acceptProposedAction();

//                eventEnter->setDropAction(Qt::CopyAction);
//                eventEnter->accept();
                return true;
            }
            else
            {
                eventEnter->ignore();
                return false;
            }

        }
        case QEvent::Drop:
        {
            QDropEvent *dropEvent = static_cast<QDropEvent*>(event);

            Qt::DropAction action = dropEvent->dropAction();

            dropEvent->acceptProposedAction();
            dropEvent->setDropAction(Qt::CopyAction);
            dropEvent->accept();

            foreach(QString format, dropEvent->mimeData()->formats())
            {
                const QMimeData *mimeData = dropEvent->mimeData();
                QByteArray encodedData = mimeData->data(format);

                QDataStream stream(&encodedData, QIODevice::ReadOnly);

                while (!stream.atEnd())
                {
                    quint64 pointer;
                    stream >> pointer;

                    gxTreeAbstractObject *abstractObject = reinterpret_cast<gxTreeAbstractObject*>(pointer);

                    this->objectList.append(abstractObject->getSharedPointer());
                    ui->listWidget->addItem(abstractObject->getName());
                }
            }

            return true;
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

void spliner_dialog::changeEvent(QEvent *e)
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

void spliner_dialog::setupMapper(int index)
{
//    int index = ui->mappersComboBox->currentIndex();

    QWidget *settingsWidget = mapperList[index].data()->getSettingsWidget();
    if (settingsWidget)
    {
        // remove previous widget
        if (ui->settingsLayout->count())
        {
            QWidget * w = ui->settingsLayout->takeAt(0)->widget();
            delete w;
        }

        ui->settingsLayout->invalidate();

        // add new widget
        ui->settingsLayout->addWidget(settingsWidget);

        ui->settingsLayout->invalidate();
    }
}


//                               slots
//------------------------------------------------------------------------------


void spliner_dialog::onClose()
{
}


//------------------------------------------------------------------------------


void spliner_dialog::onCalculate()
{
    // first we get points

//    gxPointExtractor pointExtractor;
    gxPoint3DList allPoints;

    QListIterator<QSharedPointer<gxTreeAbstractObject> > it(this->objectList);
    while (it.hasNext())
    {
        gxVisualObject *v = static_cast<gxVisualObject*>(it.next().data());
        allPoints += v->getPoint3DList();
    }
    int index = this->ui->mappersComboBox->currentIndex();

    QVector<double> result;
    mapperList[index]->calcSurface(allPoints, gxSize3D(), 20, 20, result);
}
