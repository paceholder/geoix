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

#include "tree_abstract_object.h"

/// Base class for all objects in project tree
/*!
    Implements methods for showing menu,
    deletion and renaming of object.

    \todo maybe this class is useless. It must be replaced by gxVisualObject
*/
class gxTreeObject : public gxTreeAbstractObject
{
    Q_OBJECT
public:
    gxTreeObject(gxTreeFolderObject* parent);
    virtual ~gxTreeObject();

    int getIndex();

};
Q_DECLARE_METATYPE(gxTreeObject* );

#endif // TREE_OBJECT_H
