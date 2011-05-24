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

#include "mainwindow.h"

#include "tree_folder_object.h"
#include "tree_menu_fabric.h"
#include "points.h"
#include "lines.h"
#include "surface.h"
#include "well.h"
#include "logger.h"
#include "cube.h"

#include "data_loader.h"

gxTreeFolderObject::gxTreeFolderObject(gxTreeFolderObject* parent)
    : gxTreeAbstractObject(parent)
{
    name = tr("New Folder");
    // log
    gxLogger::instance()->logEvent("Folder '" + name + "' created");
}


gxTreeFolderObject::~gxTreeFolderObject()
{
    // qDeleteAll(this->children);

    // since we used shared pointer no neccessety to delete all objects manually
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::setup()
{
    QTreeView *projectTree = gxEngine::instance()->getMainWindow()->getProjectTree();
    QAbstractItemModel* model = projectTree->model();

    QModelIndex index = gxEngine::instance()->getMainWindow()->getProjectTree()->selectionModel()->currentIndex();

    // parent folder for new object
    gxTreeFolderObject* parentFolder = static_cast<gxTreeFolderObject*>(index.internalPointer());

    model->insertRow(parentFolder->count() - 1, index);

    projectTree->expand(index);
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

void gxTreeFolderObject::deleteChild(gxTreeAbstractObject* child)
{
    for(int i = 0; i < this->children.size(); ++i)
    {
        if (children[i].data() == child)
            children.removeAt(i);
    }
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::deleteChild(int i)
{
    Q_ASSERT(i >= 0 && i < this->children.size() );

    children.removeAt(i);
}

//------------------------------------------------------------------------------


void gxTreeFolderObject::addChild(QSharedPointer<gxTreeAbstractObject> child)
{
    child->setParent(this);

    children.append( child );
}


//------------------------------------------------------------------------------

QSharedPointer<gxTreeAbstractObject> gxTreeFolderObject::getChild(int i)
{
    Q_ASSERT_X(i >=0 && i < children.size(), "gxTreeFolderObject::getChild", "index is out of range" );
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

    Q_ASSERT(index != -1);

    return index;
}


//------------------------------------------------------------------------------


int gxTreeFolderObject::getIndex()
{
    Q_ASSERT_X(parent, "getIndex", "parent of NULL object required");
    if ( !parent ) return -1;

    // the only object which could be parent is folder
    gxTreeFolderObject* folder = (gxTreeFolderObject*)parent;

    return folder->indexOf(this);;
}


//                          slots
//------------------------------------------------------------------------------


void gxTreeFolderObject::createFolder()
{
    // creation of new object
    gxTreeFolderObject* folder = new gxTreeFolderObject(this);

    // creation of sharedPointer from gxTreeFolderObject*
    QSharedPointer<gxTreeAbstractObject> sharedPointer(folder);


    // adding new folder to children
    this->addChild(sharedPointer);

    // append new item to the model
    folder->setup();
}



//------------------------------------------------------------------------------

void gxTreeFolderObject::createWell()
{
    gxWell* well = new gxWell(this);

    QSharedPointer<gxWell> sharedPointer(well);

    this->addChild(sharedPointer);

    well->update();
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createPoints()
{
    gxPoints* points = new gxPoints(this);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(points);
    this->addChild(sharedPointer);

    points->update();
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createLines()
{
    gxLines* lines = new gxLines(this);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(lines);
    this->addChild(sharedPointer);

    lines->update();
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createSurface()
{
    gxSurface* surface = new gxSurface(this);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(surface);
    this->addChild(sharedPointer);

    surface->update();
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::createSurface(gxSurfaceData *data)
{
    gxSurface* surface = new gxSurface(this, data);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(surface);
    this->addChild(sharedPointer);

    surface->update();
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::createCube()
{
    gxCube* cube = new gxCube(this);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(cube);
    this->addChild(sharedPointer);

    cube->update();
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::createCube(gxSurfaceData *topData, gxSurfaceData *bottomData)
{
    gxCube* cube = new gxCube(this, topData, bottomData);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(cube);
    this->addChild(sharedPointer);

    cube->update();
}

//------------------------------------------------------------------------------

void gxTreeFolderObject::importAndCreateWells()
{
    QList<gxPoint3DList> wellDataList;
    QStringList names;
    gxDataLoader::loadWellsData(wellDataList, names);

    for(int i = 0; i < wellDataList.size(); ++i)
    {
        gxPoint3DList points = wellDataList[i];
        gxWell* well = new gxWell(this);
        well->setData(points);
        well->setName(names[i]);

        QSharedPointer<gxWell> sharedPointer(well);

        this->addChild(sharedPointer);

        well->update();
    }
}


//------------------------------------------------------------------------------

void gxTreeFolderObject::importAndCreatePoints()
{
//    QList<gxPoint3DList> wellDataList;
//    gxDataLoader::loadWellsData(wellDataList);

//    foreach(gxPoint3DList points, wellDataList)
//    {
//        gxWell* well = new gxWell(this);
//        well->setData(points);

//        QSharedPointer<gxWell> sharedPointer(well);

//        this->addChild(sharedPointer);

//        well->update();
//    }
}

