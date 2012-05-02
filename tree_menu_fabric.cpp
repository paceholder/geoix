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


#include "tree_menu_fabric.h"

#include "project.h"
#include "tree_folder_object.h"
#include "points.h"
#include "lines.h"
#include "surface.h"
#include "well.h"
#include "cube.h"

#include "mainwindow.h"
#include "engine.h"

gxTreeMenuFabric* gxTreeMenuFabric::inst = NULL;

gxTreeMenuFabric::gxTreeMenuFabric()
{
    menu = new QMenu(NULL);

    QTreeView* projectTree = gxEngine::instance()->getMainWindow()->getProjectTree();
    createFolder = new QAction(QIcon(":/images/add_folder.png"), tr("Create Folder"), projectTree);
    createPoints = new QAction(QIcon(":/images/add_points.png"), tr("Create Points"), projectTree);
    createLines  = new QAction(QIcon(":/images/chart_stock.png"), tr("Create Lines"), projectTree);
    createSurface = new QAction(QIcon(":images/add_surface.png"), tr("Create Surface"), projectTree);
    createWell  = new QAction(QIcon(":/images/well.png"), tr("Create Well"), projectTree);
    createCube  = new QAction(QIcon(":/images/soil_layers.png"), tr("Create Cube"), projectTree);

    importPoints  = new QAction(tr("Import Points"),  projectTree);
    importLines   = new QAction(tr("Import Lines"),   projectTree);
    importSurface = new QAction(tr("Import Surface"), projectTree);
    importWell    = new QAction(tr("Import Well"),    projectTree);

    exportSurface = new QAction(tr("Export Surface"), projectTree);

    importAndCreateWells  = new QAction(tr("Import Wells"),  projectTree);
    importAndCreatePoints = new QAction(QIcon(":/images/add_points.png"), tr("Import Points"), projectTree);

    renameItem = new QAction(tr("Rename"), projectTree);
    showOptionsDialog = new QAction(tr("Options"), projectTree);

    deleteItem = new QAction(QIcon(":/images/Delete.png"), tr("Delete"), projectTree);
    deleteItem->setIconVisibleInMenu(true);

    clearData = new QAction(QIcon(":/images/clearData.png"), tr("Clear Data"), projectTree);
    clearData->setIconVisibleInMenu(true);
}


//------------------------------------------------------------------------------

gxTreeMenuFabric::~gxTreeMenuFabric()
{
    delete menu;

    delete createFolder;
    delete createLines;
    delete createPoints;
    delete createSurface;
    delete createProject;
    delete createWell;
    delete createCube;

    delete showOptionsDialog;
    delete renameItem;
    delete deleteItem;
    delete clearData;

    delete importWell;
    delete importLines;
    delete importPoints;
    delete importSurface;

    delete exportSurface;

    delete importAndCreateWells;
    delete importAndCreatePoints;
}


//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getProjectMenu(gxProject* project)
{
    menu->clear();
    menu->addAction(createFolder);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);

    connect(createFolder, SIGNAL(triggered()), project, SLOT(createFolder()));
    connect(renameItem, SIGNAL(triggered()), project, SLOT(renameItem()));
    connect(deleteItem, SIGNAL(triggered()), project, SLOT(deleteThis()));

    return menu;
}


//------------------------------------------------------------------------------


QMenu *gxTreeMenuFabric::getWellMenu(gxWell *well)
{
    menu->clear();
    menu->addAction(importWell);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);

    connect(importWell, SIGNAL(triggered()), well, SLOT(importFromFile()));
    connect(renameItem, SIGNAL(triggered()), well, SLOT(renameItem()));
    connect(clearData,  SIGNAL(triggered()), well, SLOT(clearData()));
    connect(deleteItem, SIGNAL(triggered()), well, SLOT(deleteThis()));

    return menu;

}


//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getFolderMenu(gxTreeFolderObject* folder)
{
    menu->clear();
    menu->addAction(createPoints);
    menu->addAction(createLines);
    menu->addAction(createSurface);
    menu->addAction(createFolder);
    menu->addAction(createWell);
    menu->addAction(createCube);
    menu->addSeparator();
    menu->addAction(importAndCreateWells);
    menu->addAction(importAndCreatePoints);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);

    connect(createPoints, SIGNAL(triggered()), folder, SLOT(createPoints()));
    connect(createLines,  SIGNAL(triggered()), folder, SLOT(createLines()));
    connect(createSurface, SIGNAL(triggered()), folder, SLOT(createSurface()));
    connect(createFolder, SIGNAL(triggered()), folder, SLOT(createFolder()));
    connect(createWell,   SIGNAL(triggered()), folder, SLOT(createWell()));
    connect(createCube,   SIGNAL(triggered()), folder, SLOT(createCube()));

    connect(importAndCreateWells,  SIGNAL(triggered()), folder, SLOT(importAndCreateWells()));
    connect(importAndCreatePoints, SIGNAL(triggered()), folder, SLOT(importAndCreatePoints()));


    connect(renameItem, SIGNAL(triggered()), folder, SLOT(renameItem()));
    connect(deleteItem, SIGNAL(triggered()), folder, SLOT(deleteThis()));

    return menu;
}


//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getPointsMenu(gxPoints *points)
{
    menu->clear();
    menu->addAction(importPoints);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);


    connect(importPoints, SIGNAL(triggered()), points, SLOT(importFromFile()));
    connect(renameItem, SIGNAL(triggered()), points, SLOT(renameItem()));
    connect(clearData, SIGNAL(triggered()), points, SLOT(clearData()));
    connect(deleteItem, SIGNAL(triggered()), points, SLOT(deleteThis()));

    return menu;
}


//------------------------------------------------------------------------------

QMenu* gxTreeMenuFabric::getLinesMenu(gxLines* lines)
{
    menu->clear();
    menu->addAction(importLines);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);


    connect(importLines, SIGNAL(triggered()), lines, SLOT(importFromFile()));
    connect(renameItem, SIGNAL(triggered()), lines, SLOT(renameItem()));
    connect(clearData, SIGNAL(triggered()), lines, SLOT(clearData()));
    connect(deleteItem, SIGNAL(triggered()), lines, SLOT(deleteThis()));

    return menu;
}


//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getSurfaceMenu(gxSurface *surface)
{
    menu->clear();
    menu->addAction(importSurface);
    menu->addAction(exportSurface);
    menu->addSeparator();
    menu->addAction(showOptionsDialog);
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addSeparator();
    menu->addAction(deleteItem);

    foreach(QAction* action, menu->actions())
        disconnect(action, 0, 0, 0);

    connect(importSurface, SIGNAL(triggered()), surface, SLOT(importFromFile()));
    connect(exportSurface, SIGNAL(triggered()), surface, SLOT(exportToFile()));
    connect(showOptionsDialog, SIGNAL(triggered()), surface, SLOT(options()));
    connect(renameItem, SIGNAL(triggered()), surface, SLOT(renameItem()));
    connect(clearData, SIGNAL(triggered()), surface, SLOT(clearData()));
    connect(deleteItem, SIGNAL(triggered()), surface, SLOT(deleteThis()));

    return menu;
}

//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getCubeMenu(gxCube *cube)
{
    return 0;

    Q_UNUSED(cube);

//    menu->clear();
//    menu->addAction(importSurface);
//    menu->addSeparator();
//    menu->addAction(showOptionsDialog);
//    menu->addAction(renameItem);
//    menu->addAction(clearData);
//    menu->addSeparator();
//    menu->addAction(deleteItem);

//    foreach(QAction* action, menu->actions())
//        disconnect(action, 0, 0, 0);

//    connect(importSurface, SIGNAL(triggered()), surface, SLOT(importFromFile()));
//    connect(showOptionsDialog, SIGNAL(triggered()), surface, SLOT(options()));
//    connect(renameItem, SIGNAL(triggered()), surface, SLOT(renameItem()));
//    connect(clearData, SIGNAL(triggered()), surface, SLOT(clearData()));
//    connect(deleteItem, SIGNAL(triggered()), surface, SLOT(deleteThis()));

//    return menu;
}
//------------------------------------------------------------------------------


QMenu* gxTreeMenuFabric::getTreeGeneralMenu()
{
    menu->clear();
    menu->addAction(gxEngine::instance()->getMainWindow()->actions.newProjectAct);

    return menu;
}
