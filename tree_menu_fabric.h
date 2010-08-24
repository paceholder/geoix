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


#ifndef TREE_MENU_FABRIC_H
#define TREE_MENU_FABRIC_H


#include <QMenu>
#include <QAction>

#include "tree_object.h"
#include "engine.h"


class gxProject;
class gxTreeObjectFolder;
class gxPoints;
class gxLines;
class gxSurface;
class gxVisualObject;


/// Class builds different context menus for all
/// types of visual and non-visual objects
/// in project tree.
class gxTreeMenuFabric : public QObject
{
    Q_OBJECT
private:
    static gxTreeMenuFabric* inst;

    QMenu* menu;

    // list of all actions
    QAction* createProject;
    QAction* createFolder;
    QAction* createPoints;
    QAction* createLines;
    QAction* createSurface;

    QAction* importPoints;
    QAction* importSurface;
    QAction* importLines;

    QAction* showOptionsDialog;
    QAction* clearData;
    QAction* renameItem;
    QAction* deleteItem;




//    QMenu* getVisualObjectMenu(gxVisualObject*);

public:
    static gxTreeMenuFabric* instance()
    {
        if (!inst)
        {
            inst = new gxTreeMenuFabric();
        }

       return inst;
    }


    gxTreeMenuFabric();
    virtual ~gxTreeMenuFabric();


    QMenu* getProjectMenu(gxProject* project);
    QMenu* getFolderMenu(gxTreeObjectFolder* project);
    QMenu* getPointsMenu(gxPoints* points);
    QMenu* getLinesMenu(gxLines* lines);
    QMenu* getSurfaceMenu(gxSurface* surface);
    QMenu* getTreeGeneralMenu();
};

#endif // TREE_MENU_FABRIC_H
