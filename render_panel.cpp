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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------

#include <QPixmap>
#include <limits>

#include "render_panel.h"
#include "engine.h"
#include "logger.h"

gxRenderPanel::gxRenderPanel(QWidget* parent)
    : QWidget(parent)
{
    setGeometry(10, 10, 400, 400);
    setMouseTracking(true);
    setMinimumSize(20, 20);

    border_width = 5;
    resizing = false;
    moving = false;

    // creates size object
    size3d = new gxSize3D(-50, -50, -50, 50, 50, 50);
    recalcSize();

    // update four resiz spots on the angles of rectangle
    updateResizeSpots();

    // make this window active (mover it on the top of stack)
    this->activateWindow();


    this->setAcceptDrops(true);
}

gxRenderPanel::~gxRenderPanel()
{
    delete gl_panel;
    delete size3d;
}

//------------------------------------------------------------------


void gxRenderPanel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
        event->ignore();
    }
}


void gxRenderPanel::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
        event->ignore();
    }
}


void gxRenderPanel::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        QByteArray output = event->mimeData()->data("geoix/tree-object");
        QDataStream stream(&output, QIODevice::ReadOnly);

        qint64 pointer = 0;
        stream >> pointer;


        gxTreeObject* object = (gxTreeObject*)pointer; // this object is moved
        if (object)
        {
            if (!object->isFolder())
            {
                gxVisualObject* vo = (gxVisualObject*)object;
                this->registerObject(vo);
                gxEngine::instance()->recheckTreeItems();
            }
        }
    }
}



//------------------------------------------------------------------



void gxRenderPanel::registerObject(gxVisualObject* object)
{
    if (! isObjectRegistered(object))
    {
        connect(object, SIGNAL(objectDelete()), this, SLOT(objectDeleted()));
        //object->recreateDisplayList();
        objects.append(object);
        recalcSize();
    }
    this->draw();
}


void gxRenderPanel::unregisterObject(gxVisualObject* object)
{
    disconnect(object, SIGNAL(objectDelete()), this, 0);
    int i = objects.indexOf(object);
    if (i >= 0)
    {
        objects.remove(i);
        recalcSize();
    }

    this->draw();
}


bool gxRenderPanel::isObjectRegistered(gxVisualObject* object)
{
    return (objects.indexOf(object) >= 0);
}


void gxRenderPanel::recreateDisplayLists()
{
    QVectorIterator<gxVisualObject*> it(objects);

    while (it.hasNext())
        it.next()->recreateDisplayList();
}


void gxRenderPanel::drawBorder()
{
    QPainter painter(this);

    painter.fillRect(0, 0,
                     width(),
                     height(),
                     border_active_color);

    painter.fillRect(border_width,
                     border_width*2,
                     width() - border_width*2,
                     height() - border_width*3,
                     Qt::white);


    QPainterPath path;
    // outside border
    path.moveTo(0, 0);
    path.lineTo(width()-1 ,0);
    path.lineTo(width()-1 , height()-1);
    path.lineTo(0 , height()-1);
    path.closeSubpath();


    path.moveTo(border_width, border_width*2);
    path.lineTo(width()-border_width-1, border_width*2);
    path.lineTo(width()-border_width-1, height()-border_width-1);
    path.lineTo(border_width, height()-border_width-1);
    path.closeSubpath();

    painter.drawPath(path);

    painter.setBrush(Qt::white);
    painter.drawRect(resizeSpots[Qt::TopLeftCorner]);
    painter.drawRect(resizeSpots[Qt::TopRightCorner]);
    painter.drawRect(resizeSpots[Qt::BottomLeftCorner]);
    painter.drawRect(resizeSpots[Qt::BottomRightCorner]);
}


void gxRenderPanel::updateResizeSpots()
{
    resizeSpots[Qt::TopLeftCorner] = QRect(0,0, border_width, border_width*2);
    resizeSpots[Qt::TopRightCorner] = QRect(width()-border_width-1, 0, border_width, border_width*2);
    resizeSpots[Qt::BottomLeftCorner] = QRect(0, height()-border_width-1, border_width, border_width);
    resizeSpots[Qt::BottomRightCorner] = QRect(width()-border_width-1, height()-border_width-1, border_width, border_width);
}


void gxRenderPanel::recalcSize()
{
    if (objects.count() > 0)
    {
        double maxdouble = std::numeric_limits<double>::max();

        gxSize3D size( maxdouble,  maxdouble,  maxdouble,
                      -maxdouble, -maxdouble, -maxdouble);

        QVectorIterator<gxVisualObject*> it(objects);
        while (it.hasNext())
        {
            gxVisualObject* object = it.next();

            gxSize3D objSize = object->getSize();

            if (objSize.getMinX() < size.getMinX()) size.setMinX(objSize.getMinX());
            if (objSize.getMinY() < size.getMinY()) size.setMinY(objSize.getMinY());
            if (objSize.getMinZ() < size.getMinZ()) size.setMinZ(objSize.getMinZ());

            if (objSize.getMaxX() > size.getMaxX()) size.setMaxX(objSize.getMaxX());
            if (objSize.getMaxY() > size.getMaxY()) size.setMaxY(objSize.getMaxY());
            if (objSize.getMaxZ() > size.getMaxZ()) size.setMaxZ(objSize.getMaxZ());
        }

        this->size3d->setSize(size);
    }
    else
    {
        // default size
       //size3d->setSize(-50, -50, -50, 50, 50, 50);
    }
}


QPixmap gxRenderPanel::renderPixmap()
{
    return this->gl_panel->renderPixmap(0,0, true);
}


//---------------------------------------
//     events

void gxRenderPanel::mouseMoveEvent(QMouseEvent* event)
{
    QPoint p = event->globalPos();

    int x, y;
    // mouse offset
    x = p.x()-oldMousePos.x();
    y = p.y()-oldMousePos.y();

    oldMousePos = p;

    movingHandler(x, y);

    resizingHandler(x, y, p);

    event->accept();
}


void gxRenderPanel::movingHandler(int x, int y)
{

    if (this->x() + x < 0) x = 0;
    if (this->y() + y < 0) y = 0;
    if (this->x() + this->width() + x > parentWidget()->width()) x = 0;
    if (this->y() + this->height() + y > parentWidget()->height()) y = 0;

    // moving
    if (moving)
    {
        QPoint p(this->x() + x, this->y() + y);
        move(p);
    }
}

void gxRenderPanel::resizingHandler(int x, int y, QPoint &p)
{
    // resizing
    if (resizing)
    {
        QSize sz = this->size();
        QPoint pt = this->pos();
        switch(resizeDirection)
        {
        case Qt::TopLeftCorner:
            if (pt.x() + x < 0) x = 0;
            if (pt.y() + y < 0) y = 0;
            setGeometry(pt.x() + x, pt.y() + y, sz.width() - x, sz.height() - y);
            break;
        case Qt::TopRightCorner:
            if (pt.x() + sz.width() + x > parentWidget()->width()) x = 0;
            if (pt.y() + y < 0) y = 0;
            setGeometry(pt.x(), pt.y() + y, sz.width() + x, sz.height() - y);
            break;
        case Qt::BottomLeftCorner:
            if (pt.x() + x < 0) x = 0;
            if (pt.y() + sz.height() + y > parentWidget()->width()) y = 0;
            setGeometry(pt.x() + x, pt.y(), sz.width() - x, sz.height() + y);
            break;
        case Qt::BottomRightCorner:
            if (pt.x() + sz.width() + x > parentWidget()->width()) x = 0;
            if (pt.y() + sz.height() + y > parentWidget()->width()) y = 0;
            setGeometry(pt.x(), pt.y(), sz.width() + x, sz.height() + y);
            break;
        }
    }


    p = this->mapFromGlobal(p);
    if (resizeSpots[Qt::TopLeftCorner].contains(p) ||
        resizeSpots[Qt::BottomRightCorner].contains(p))
    {
        QCursor q;
        q.setShape(Qt::SizeFDiagCursor);
        this->setCursor(q);
    }
    else
        if (resizeSpots[Qt::TopRightCorner].contains(p) ||
            resizeSpots[Qt::BottomLeftCorner].contains(p))
    {
        QCursor q;
        q.setShape(Qt::SizeBDiagCursor);
        this->setCursor(q);
    }
    else
    {
        QCursor q;
        q.setShape(Qt::ArrowCursor);
        this->setCursor(q);
    }
}


void gxRenderPanel::mousePressEvent(QMouseEvent* event)
{
    this->raise();
    gxEngine::instance()->raisePanel(this);



    if (event->buttons() == Qt::LeftButton)
    {
        QPoint p = event->pos();

        // now checkin whether mouse point at the resize spot or not
        QList<Qt::Corner> keys = resizeSpots.keys();
        QListIterator<Qt::Corner> it(keys);

        while(it.hasNext())
        {
            if (resizeSpots[it.peekNext()].contains(p))
            {
                resizeDirection = it.peekNext();
                resizing = true;
                grabMouse();
                break;
            }
            it.next();
        }

        // if resizin is not switched on, switch the moving on
        if (!resizing)
            moving = true;

    }

    event->accept();
}



void gxRenderPanel::mouseReleaseEvent(QMouseEvent * event)
{
    this->releaseMouse();
    resizing = false;
    moving = false;

    event->accept();
}



void gxRenderPanel::resizeEvent(QResizeEvent *event)
{
    updateResizeSpots();
    int b = this->border_width;
    this->gl_panel->setGeometry(b, b*2, width() - b*2, height() - b*3);

    event->accept();
}



//--------------------------
//      slots


void gxRenderPanel::objectDeleted()
{
    gxVisualObject* obj = (gxVisualObject*)sender();
    int i = objects.indexOf(obj);
    if (i >= 0)
        objects.erase(objects.begin() + i);

    recalcSize();
}


