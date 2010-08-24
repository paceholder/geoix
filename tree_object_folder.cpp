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


#include "tree_object_folder.h"


#include "points.h"
#include "lines.h"
#include "surface.h"
#include "logger.h"

gxTreeObjectFolder::gxTreeObjectFolder(gxTreeObjectFolder* parent)
    : gxTreeObject(parent)
{
    this->name = tr("New Folder");


    // todo: Bad case!!!! Any operation with widgetItem has side effect
    // because slot ItemChanges is called
    // when setText is used
    widgetItem->setText(0, this->name);
    widgetItem->setIcon(0, QIcon(":/images/Closed_folder.png"));

    if (parent)
    {
        parent->widgetItem->addChild(widgetItem);
        parent->widgetItem->setExpanded(true);
        Gx::Log("Folder '" + name + "' created");
    }    
}


gxTreeObjectFolder::~gxTreeObjectFolder()
{
    QMutableVectorIterator<gxTreeObject*> it(childs);
    while (it.hasNext())
    {
        it.next();
        it.remove();
    }
}


void gxTreeObjectFolder::createFolder()
{
    gxTreeObjectFolder* folder = new gxTreeObjectFolder(this);
    this->addChild(folder);
}

void gxTreeObjectFolder::createPoints()
{
    gxPoints* points = new gxPoints(this);
    this->addChild(points);
}

void gxTreeObjectFolder::createLines()
{
    gxLines* lines = new gxLines(this);
    this->addChild(lines);
}


void gxTreeObjectFolder::createSurface()
{
    gxSurface* surface = new gxSurface(this);
    this->addChild(surface);
}


void gxTreeObjectFolder::deleteChild(gxTreeObject* child)
{
    QMutableVectorIterator<gxTreeObject*> it(this->childs);

    // todo indexof
    while (it.hasNext())
    {
        if (it.next() == child)
        {
            it.remove();
            break;
        }
    }

    widgetItem->setExpanded(childs.count() != 0);
}


void gxTreeObjectFolder::addChild(gxTreeObject* child)
{
    childs.append(child);
}
