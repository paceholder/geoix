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


#include "tree_menu_fabric.h"

#include "project.h"
#include "tree_folder_object.h"
#include "points.h"
#include "lines.h"
#include "surface.h"


#include "engine.h"

gxTreeMenuFabric* gxTreeMenuFabric::inst = NULL;

gxTreeMenuFabric::gxTreeMenuFabric()
{
    menu = new QMenu(NULL);

    QTreeView* project_tree = gxEngine::instance()->getMainWindow()->getProjectTree();
    createFolder = new QAction(QIcon(":/images/add_folder.png"), tr("Create Folder"), project_tree);
    createFolder->setIconVisibleInMenu(true);

    createPoints = new QAction(QIcon(":/images/add_points.png"), tr("Create Points"), project_tree);
    createPoints->setIconVisibleInMenu(true);

    createLines = new QAction(QIcon(":/images/add_lines.png"), tr("Create Lines"), project_tree);
    createLines->setIconVisibleInMenu(true);

    createSurface = new QAction(QIcon(":images/add_surface.png"), tr("Create Surface"), project_tree);
    createSurface->setIconVisibleInMenu(true);

    importPoints  = new QAction(tr("Import Points"), project_tree);
    importLines   = new QAction(tr("Import Lines"),  project_tree);
    importSurface = new QAction(tr("Import Surface"), project_tree);

    renameItem = new QAction(tr("Rename"), project_tree);
    showOptionsDialog = new QAction(tr("Options"), project_tree);

    deleteItem = new QAction(QIcon(":/images/Delete.png"), tr("Delete"), project_tree);
    deleteItem->setIconVisibleInMenu(true);

    clearData = new QAction(QIcon(":/images/clearData.png"), tr("Clear Data"), project_tree);
    clearData->setIconVisibleInMenu(true);
}

gxTreeMenuFabric::~gxTreeMenuFabric()
{
    delete menu;

    delete createFolder;
    delete createLines;
    delete createPoints;
    delete createSurface;
    delete createProject;

    delete showOptionsDialog;
    delete renameItem;
    delete deleteItem;
    delete clearData;

    delete importLines;
    delete importPoints;
    delete importSurface;
}



QMenu* gxTreeMenuFabric::getProjectMenu(gxProject* project)
{
    menu->clear();
    menu->addAction(createFolder);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(deleteItem);

    disconnect(createFolder, 0, 0, 0);
    connect(createFolder, SIGNAL(triggered()), project, SLOT(createFolder()));
    disconnect(renameItem, 0, 0, 0);
    connect(renameItem, SIGNAL(triggered()), project, SLOT(renameItem()));
    disconnect(deleteItem, 0, 0, 0);
    connect(deleteItem, SIGNAL(triggered()), project, SLOT(deleteThis()));

    return menu;
}


QMenu* gxTreeMenuFabric::getFolderMenu(gxTreeFolderObject* folder)
{
    menu->clear();
    menu->addAction(createPoints);
    menu->addAction(createLines);
    menu->addAction(createSurface);
    menu->addAction(createFolder);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(deleteItem);

    disconnect(createPoints, 0, 0, 0);
    connect(createPoints, SIGNAL(triggered()), folder, SLOT(createPoints()));
    disconnect(createLines, 0, 0, 0);
    connect(createLines, SIGNAL(triggered()), folder, SLOT(createLines()));
    disconnect(createSurface, 0, 0, 0);
    connect(createSurface, SIGNAL(triggered()), folder, SLOT(createSurface()));
    disconnect(createFolder, 0, 0, 0);
    connect(createFolder, SIGNAL(triggered()), folder, SLOT(createFolder()));

    disconnect(renameItem, 0, 0, 0);
    connect(renameItem, SIGNAL(triggered()), folder, SLOT(renameItem()));

    disconnect(deleteItem, 0, 0, 0);
    connect(deleteItem, SIGNAL(triggered()), folder, SLOT(deleteThis()));

    return menu;
}



QMenu* gxTreeMenuFabric::getPointsMenu(gxPoints *points)
{
    menu->clear();
    menu->addAction(importPoints);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addAction(deleteItem);

    disconnect(importPoints, 0, 0, 0);
    connect(importPoints, SIGNAL(triggered()), points, SLOT(importFromFile()));

    disconnect(renameItem, 0, 0, 0);
    connect(renameItem, SIGNAL(triggered()), points, SLOT(renameItem()));

    disconnect(clearData, 0, 0, 0);
    connect(clearData, SIGNAL(triggered()), points, SLOT(clearData()));

    disconnect(deleteItem, 0, 0, 0);
    connect(deleteItem, SIGNAL(triggered()), points, SLOT(deleteThis()));

    return menu;
}


QMenu* gxTreeMenuFabric::getLinesMenu(gxLines* lines)
{
    menu->clear();
    menu->addAction(importLines);
    menu->addSeparator();
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addAction(deleteItem);

    disconnect(importLines, 0, 0, 0);
    connect(importLines, SIGNAL(triggered()), lines, SLOT(importFromFile()));

    disconnect(renameItem, 0, 0, 0);
    connect(renameItem, SIGNAL(triggered()), lines, SLOT(renameItem()));

    disconnect(clearData, 0, 0, 0);
    connect(clearData, SIGNAL(triggered()), lines, SLOT(clearData()));

    disconnect(deleteItem, 0, 0, 0);
    connect(deleteItem, SIGNAL(triggered()), lines, SLOT(deleteThis()));

    return menu;
}




QMenu* gxTreeMenuFabric::getSurfaceMenu(gxSurface *surface)
{
    menu->clear();
    menu->addAction(importSurface);
    menu->addSeparator();
    menu->addAction(showOptionsDialog);
    menu->addAction(renameItem);
    menu->addAction(clearData);
    menu->addSeparator();
    menu->addAction(deleteItem);

    disconnect(importSurface, 0, 0, 0);
    connect(importSurface, SIGNAL(triggered()), surface, SLOT(importFromFile()));

    disconnect(showOptionsDialog, 0, 0, 0);
    connect(showOptionsDialog, SIGNAL(triggered()), surface, SLOT(options()));

    disconnect(renameItem, 0, 0, 0);
    connect(renameItem, SIGNAL(triggered()), surface, SLOT(renameItem()));

    disconnect(clearData, 0, 0, 0);
    connect(clearData, SIGNAL(triggered()), surface, SLOT(clearData()));

    disconnect(deleteItem, 0, 0, 0);
    connect(deleteItem, SIGNAL(triggered()), surface, SLOT(deleteThis()));

    return menu;
}



QMenu* gxTreeMenuFabric::getTreeGeneralMenu()
{
    menu->clear();
    menu->addAction(gxEngine::instance()->getMainWindow()->actions.newProjectAct);

    return menu;
}
