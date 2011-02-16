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

#include "mainwindow.h"

#include "tree_folder_object.h"
#include "tree_menu_fabric.h"
#include "points.h"
#include "lines.h"
#include "surface.h"
#include "logger.h"

gxTreeFolderObject::gxTreeFolderObject(gxTreeFolderObject* parent)
    : gxTreeAbstractObject(parent)
{
    name = tr("New Folder");
}


gxTreeFolderObject::~gxTreeFolderObject()
{
    // qDeleteAll(this->children);

    // since we used shared pointer no neccessety to delete all objects manually
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::setup()
{
    gxTreeFolderObject* rootFolder = gxEngine::instance()->getProjectsRoot();
    QAbstractItemModel* model = gxEngine::instance()->getMainWindow()->getProjectTree()->model();

    QModelIndex index = gxEngine::instance()->getMainWindow()->getProjectTree()->selectionModel()->currentIndex();

    model->insertRow(rootFolder->count(), index);

    gxLogger::instance()->logEvent("Folder '" + name + "' created");
}


//------------------------------------------------------------------------------


QMenu* gxTreeFolderObject::getMenu()
{
    return gxTreeMenuFabric::instance()->getFolderMenu(this);
}

//------------------------------------------------------------------------------

QIcon gxTreeFolderObject::getIcon()
{
    return QIcon(":/images/Closed_folder.png");
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createFolder()
{
    gxTreeFolderObject* folder = new gxTreeFolderObject(this);
    this->addChild(folder);

    // append new item to the model
    folder->setup();
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createPoints()
{
    gxPoints* points = new gxPoints(this);
    this->addChild(points);
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createLines()
{
    gxLines* lines = new gxLines(this);
    this->addChild(lines);
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createSurface()
{
    gxSurface* surface = new gxSurface(this);
    this->addChild(surface);
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::deleteChild(gxTreeAbstractObject* child)
{
    for(int i = 0; i < this->children.size(); ++i)
    {
        if (children[i] == child)
            children.removeAt(i);
    }
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::deleteChild(int i)
{
    if (i >= 0 && i < this->children.size() )
    {
        children.removeAt(i);
    }
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::addChild(gxTreeAbstractObject* child)
{
    child->setParent(this); // in case

    children.append(QSharedPointer<gxTreeAbstractObject>(child));
}


//------------------------------------------------------------------------------


void gxTreeFolderObject::addChild(QSharedPointer<gxTreeAbstractObject> child)
{
    children.append( child );
}


//------------------------------------------------------------------------------

QSharedPointer<gxTreeAbstractObject> gxTreeFolderObject::getChild(int i)
{
    return children[i];
}


//------------------------------------------------------------------------------

int gxTreeFolderObject::indexOf(gxTreeAbstractObject *child)
{
    int index = -1;

    for(int i = 0; i < children.size(); ++i)
    {
        if ( children[i] == child )
        {
            index = i;
            break;
        }
    }
    return index;
}


//------------------------------------------------------------------------------


int gxTreeFolderObject::getIndex()
{
    if ( !parent ) return -1;

    // the only object which could be parent is folder
    gxTreeFolderObject* folder = (gxTreeFolderObject*)parent;

    return folder->indexOf(this);
}


//------------------------------------------------------------------------------

QSharedPointer<gxTreeAbstractObject>
        gxTreeFolderObject::getSharedPointer(gxTreeAbstractObject* object)
{
    foreach(QSharedPointer<gxTreeAbstractObject> sharedPointer, children)
    {
        if (sharedPointer.data() == object)
        {
            return sharedPointer;
        }
    }

    /// end of non-void function
}
