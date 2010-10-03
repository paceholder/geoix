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


#ifndef TREE_OBJECT_H
#define TREE_OBJECT_H

#include <QMenu>
#include <QTreeWidget>
#include <QVariant>


class gxTreeObjectFolder;

/// Base class for all objects in project tree
/*!
    Implements methods for showing menu,
    deletion and renaming of object.
*/
class gxTreeObject : public QObject
{
    Q_OBJECT
protected:
    QTreeWidgetItem* widgetItem;
    QString name;

    gxTreeObjectFolder* parent;
public:
    gxTreeObject(gxTreeObjectFolder* parent = NULL);
    virtual ~gxTreeObject();

    virtual QMenu* getMenu() = 0;

    virtual bool isFolder()
    {
        return false;
    }

    QTreeWidgetItem* getTreeWidgetItem() { return widgetItem; }

    void setName(QString& name) { this->name = name; }
    QString  getName() { return this->name; }

    //void updateTreeWidgetItemState();
    void changeParent(gxTreeObject* newParent);

public slots:
    void deleteThis();
    void renameItem();
};
Q_DECLARE_METATYPE(gxTreeObject* );

#endif // TREE_OBJECT_H
