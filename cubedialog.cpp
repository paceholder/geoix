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



#include "cubedialog.h"
#include "ui_cubedialog.h"

#include "tree_abstract_object.h"
#include "visual_object.h"
#include "surface.h"


gxCubeDialog::gxCubeDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowStaysOnTopHint),
    ui(new Ui::gxCubeDialog),
    folder(0)
{
    ui->setupUi(this);

    QStringList list;
    list << "Top" << "Bottom";
    ui->cbBaseGrid->addItems(list);

    list.clear();
    list << "From top" << "From bottom" << "Proportional";
    ui->cbSedimentationModel->addItems(list);

    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(1);
    ui->lineNumberOfSublayers->setValidator(validator);

    /// setting up event filter
    ui->dropWidgetTop->installEventFilter(this);
    ui->dropWidgetBottom->installEventFilter(this);

    ui->dropWidgetTop->setAcceptDrops(true);
    ui->dropWidgetBottom->setAcceptDrops(true);

}

gxCubeDialog::~gxCubeDialog()
{
    delete ui;
}

void gxCubeDialog::changeEvent(QEvent *e)
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


bool gxCubeDialog::eventFilter(QObject *object, QEvent *event)
{
    if (!(object == ui->dropWidgetTop || object == ui->dropWidgetBottom))
        return QDialog::eventFilter(object, event);

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
            return handleDropEvent(object, dropEvent);
        }
    default: break;
    }
    return false;
}


//------------------------------------------------------------------------------


bool gxCubeDialog::handleDragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/surface"))
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


bool gxCubeDialog::handleDropEvent(QObject *object, QDropEvent *event)
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

            if (object == ui->dropWidgetTop)
                this->topSurface = abstractObject->getSharedPointer();
            else
                this->bottomSurface = abstractObject->getSharedPointer();

            QLabel *label = static_cast<QLabel*>(object);

            label->setText(abstractObject->getName());
        }
    }

    return true;
}


//------------------------------------------------------------------------------


void gxCubeDialog::createCube()
{
    gxSurface *topSurf = static_cast<gxSurface*>(topSurface.data());
    gxSurface *botSurf = static_cast<gxSurface*>(bottomSurface.data());
    gxSurface *baseSurface = ui->cbBaseGrid->currentIndex() == 0 ? topSurf : botSurf;

    /// intersection of sizes of two surfaces
    gxSize3D size = topSurf->getSize().intersect(botSurf->getSize());

    /// ajust z min and max
    size.setMaxZ(qMax(topSurf->getSize().getMaxZ(), botSurf->getSize().getMaxZ()));
    size.setMinZ(qMin(topSurf->getSize().getMinZ(), botSurf->getSize().getMinZ()));

    //if (size.volume() < 0) return;

    const gxSurfaceData *topSurfData = topSurf->getData();
    const gxSurfaceData *botSurfData = botSurf->getData();
    const gxSurfaceData *baseSurfaceData = baseSurface->getData();

    /// get bound indexes
    int minxi, minyi, maxxi, maxyi;

    minxi = (int)ceil((size.getMinX() - baseSurfaceData->getSize().getMinX()) / baseSurfaceData->getStepX());
    minyi = (int)ceil((size.getMinY() - baseSurfaceData->getSize().getMinY()) / baseSurfaceData->getStepY());

    maxxi = (int)floor((size.getMaxX() - baseSurfaceData->getSize().getMinX()) / baseSurfaceData->getStepX());
    maxyi = (int)floor((size.getMaxY() - baseSurfaceData->getSize().getMinY()) / baseSurfaceData->getStepY());

    if ((minxi >= maxxi) || (minyi >= maxyi))
        return;

    /// correct size using new indexes
    size.setSize(baseSurfaceData->getX(minxi),
                 baseSurfaceData->getY(minyi),
                 size.getMinZ(),
                 baseSurfaceData->getX(maxxi),
                 baseSurfaceData->getY(maxyi),
                 size.getMaxZ());

    /// then set this dimensions to new surface data
    gxSurfaceData *newTopSurfaceData = new gxSurfaceData(size);
    newTopSurfaceData->setnXY(maxxi - minxi + 1, maxyi - minyi + 1);

    gxSurfaceData *newBottomSurfaceData = new gxSurfaceData(size);
    newBottomSurfaceData->setnXY(maxxi - minxi + 1, maxyi - minyi + 1);

    ///fill top and bottom surfaces
    for(int i = minxi; i <= maxxi; ++i)
    {
        double x = baseSurfaceData->getX(i);
        for(int j = minyi; j <= maxyi; ++j)
        {
            double y = baseSurfaceData->getY(j);

            newTopSurfaceData->at(i - minxi, j - minyi) = topSurfData->at(x, y);
            newBottomSurfaceData->at(i - minxi, j - minyi) = botSurfData->at(x, y);

        }

    }

    if (folder)
        folder->createCube(newTopSurfaceData, newBottomSurfaceData);
}
