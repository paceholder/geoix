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


#ifndef TREE_FOLDER_OBJECT_H
#define TREE_FOLDER_OBJECT_H

#include <QVector>

#include "tree_abstract_object.h"


/// Base class for tree objects which can contain other tree objects
class gxTreeFolderObject: public gxTreeAbstractObject
{
    Q_OBJECT
public:
    gxTreeFolderObject(gxTreeFolderObject* parent = 0);
    virtual ~gxTreeFolderObject();

    void setup();

    void deleteChild(gxTreeAbstractObject* child);
    void deleteChild(int i);
    void addChild(gxTreeAbstractObject* child);
    gxTreeAbstractObject* getChild(int i);

    bool isFolder() { return true; }

    int indexOf(gxTreeAbstractObject* child);

    // will be implemented in derived classes
    virtual QMenu* getMenu();
    virtual QIcon getIcon();

    int count() { return children.size(); }

    /// This functions is used by treemodel
    int getIndex();
public slots:
    void createFolder();
    void createPoints();
    void createLines();
    void createSurface();
protected:
    QList<gxTreeAbstractObject*> children;
};

#endif // TREE_FOLDER_OBJECT_H
