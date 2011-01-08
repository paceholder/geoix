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





#ifndef TREE_ABSTRACT_OBJECT_H
#define TREE_ABSTRACT_OBJECT_H

#include <QtCore>
#include <QtGui>


class gxTreeFolderObject;

/// This is interface for any object of the tree
class gxTreeAbstractObject : public QObject
{
    Q_OBJECT
public:
    gxTreeAbstractObject(gxTreeFolderObject* parent = 0)
    {
        this->parent = parent;
    }
    virtual ~gxTreeAbstractObject() {}

    /// Abstract function for getting the menu of object
    virtual QMenu* getMenu() = 0;

    /// Will return TRUE in Folder class
    virtual bool isFolder() { return false; }

    /// Sets new name for the object
    void setName(QString name) { this->name = name; }

    /// Returns current object's name
    QString  getName() { return this->name; }

    /// Abstract function which returns icon for each tree object
    virtual QIcon getIcon() = 0;

    /// Only Folder can have childrens
    virtual int count() { return 0; }

    /// returns parent's pointer
    gxTreeFolderObject* getParent() { return parent; }

    /// If object has parent function returns index of this object among parent's children
    virtual int getIndex() = 0;

    /// todo: should think about it
    virtual void changeParent(gxTreeFolderObject* newParent) { this->parent = newParent; }
protected:
    gxTreeFolderObject* parent;
    QString name;    

public slots:
    void deleteThis();
};

Q_DECLARE_METATYPE(gxTreeAbstractObject*);

#endif // TREE_ABSTRACT_OBJECT_H
