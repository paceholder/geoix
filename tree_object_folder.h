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


#ifndef TREE_OBJECT_FOLDER_H
#define TREE_OBJECT_FOLDER_H

#include <QVector>

#include "tree_object.h"
#include "tree_menu_fabric.h"


/// Base class for tree objects which can contain other tree objects
class gxTreeObjectFolder : public gxTreeObject
{
    Q_OBJECT
public:
    gxTreeObjectFolder(gxTreeObjectFolder* parent = NULL);
    virtual ~gxTreeObjectFolder();

    void deleteChild(gxTreeObject* child);
    void addChild(gxTreeObject* child);

    bool isFolder()
    {
        return true;
    }

    QMenu* getMenu()
    {
        return gxTreeMenuFabric::instance()->getFolderMenu(this);
    }
public slots:
    void createFolder();
    void createPoints();
    void createLines();
    void createSurface();
protected:
    QVector<gxTreeObject*> childs;
};

#endif // TREE_OBJECT_FOLDER_H
