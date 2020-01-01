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

#include <QtCore/QVector>

#include "tree_abstract_object.h"

class gxSurfaceData;

/// Base class for tree objects which can contain other tree objects
class gxTreeFolderObject: public gxTreeAbstractObject
{
    Q_OBJECT

    friend class gxTreeAbstractObject;
public:
    gxTreeFolderObject(gxTreeFolderObject* parent = 0);
    virtual ~gxTreeFolderObject();


    /// some stuff for insertion this item to the project tree
    void setup();

    /// removes object from children list
    void deleteChild(gxTreeAbstractObject* child);

    /// removes i'th object from children list
    void deleteChild(int i);

    /// adds object to the children list
    void addChild(QSharedPointer<gxTreeAbstractObject> child);

    /// returns child by index
    QSharedPointer<gxTreeAbstractObject> getChild(int i);

    /// if the object is folder?
    bool isFolder() { return true; }

    /// returns index of object
    int indexOf(gxTreeAbstractObject* child);

    /// returns context menu
    virtual QMenu* getMenu();

    /// returns icon for the tree
    virtual QIcon getIcon();

    /// returns count of children
    int count() { return children.size(); }

    /// This functions is used by treemodel
    int getIndex();

    virtual QString getMimeType() { return QString("geoix/folder"); }

public slots:
    void createFolder();
    void createPoints();
    void createLines();
    void createSurface();
    void createSurface(gxSurfaceData *data, QString name = QString());
    void createWell();
    void createCube(gxSurfaceData *topData, gxSurfaceData *bottomData);
    void createCube();

    void importAndCreateWells();
    void importAndCreatePoints();
protected:
    QList<QSharedPointer<gxTreeAbstractObject> > children;
};

#endif // TREE_FOLDER_OBJECT_H
