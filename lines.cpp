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
//    along with Geoix.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#include "lines.h"
#include "data_loader.h"
#include "tree_menu_fabric.h"
#include <limits> // todo do not use std


gxLines::gxLines(gxTreeFolderObject* parent)
    : gxVisualObject(parent)
{
    name = tr("New Lines");
//    widgetItem->setText(0, name);
//    widgetItem->setIcon(0, QIcon(":/images/surface.png"));
//
//
//    parent->getTreeWidgetItem()->addChild(widgetItem);
//    parent->getTreeWidgetItem()->setExpanded(true);

    setRandomColor();

    contours = new gxContours;

    updateWidgetItemState();
}

gxLines::~gxLines()
{
    // delete contours
    foreach(gxContour* contour, *contours)
    {
        delete contour;
    }
}



QMenu* gxLines::getMenu()
{
    return gxTreeMenuFabric::instance()->getLinesMenu(this);
}

QIcon gxLines::getIcon()
{
    return QIcon(":/images/surface.png");
}


void gxLines::draw2D()
{
    // contours
    glColor3f(color.redF(), color.greenF(), color.blueF());

    QVectorIterator<gxContour*> it(*contours);
    while (it.hasNext())
    {
        gxContour* c = it.next();

        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < c->count(); ++i)
            {
                glVertex2d(c->at(i).x, c->at(i).y);
            }
//                    if (c->isClosed())
//                        glVertex3d(c->at(0).x, c->at(0).y, c->getZ());
        glEnd();
    }
}


void gxLines::draw3D()
{
    // contours
    glColor3f(color.redF(), color.greenF(), color.blueF());

    QVectorIterator<gxContour*> it(*contours);
    while (it.hasNext())
    {
        gxContour* c = it.next();

        glBegin(GL_LINE_STRIP);
            for(int i = 0; i < c->count(); ++i)
            {
                glVertex3d(c->at(i).x, c->at(i).y, c->at(i).z);
            }
//                    if (c->isClosed())
//                        glVertex3d(c->at(0).x, c->at(0).y, c->getZ());
        glEnd();
    }
}


void gxLines::recalcSize()
{
    recreateDisplayList();

    if (contours->count() == 0) return;

    // default size
    this->size3d.setSize(-50, -50, -50, 50, 50, 50);

    double maxdouble = std::numeric_limits<double>::max();

    gxSize3D size( maxdouble,  maxdouble,  maxdouble,
                  -maxdouble, -maxdouble, -maxdouble);

    QVectorIterator<gxContour*> it(*contours);
    while (it.hasNext())
    {
        gxContour* contour = it.next();
        QVectorIterator<gxPoint3D> itp(contour->data);
        while (itp.hasNext())
        {
            gxPoint3D p = itp.next();

            if (p.x < size.getMinX()) size.setMinX(p.x);
            if (p.x > size.getMaxX()) size.setMaxX(p.x);

            if (p.y < size.getMinY()) size.setMinY(p.y);
            if (p.y > size.getMaxY()) size.setMaxY(p.y);

            if (p.z < size.getMinZ()) size.setMinZ(p.z);
            if (p.z > size.getMaxZ()) size.setMaxZ(p.z);
        }
    }

    this->size3d.setSize(size);
}

//----------------------------------
// slots


void gxLines::importFromFile()
{
    gxDataLoader::instance()->loadLinesData(contours);
    this->recalcSize();

    updateWidgetItemState();
}

void gxLines::clearData()
{
    foreach(gxContour* contour, *contours)
    {
        delete contour;
    }

    contours->clear();

    updateWidgetItemState();
}


