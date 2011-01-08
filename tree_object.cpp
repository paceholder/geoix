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


#include "tree_object.h"

#include "tree_folder_object.h"
#include "engine.h"



gxTreeObject::gxTreeObject(gxTreeFolderObject* parent)
    :gxTreeAbstractObject(parent)
{
    name = tr("Some Tree Object");

    QVariant data = qVariantFromValue((gxTreeObject*)this);
}



gxTreeObject::~gxTreeObject()
{
    //
}


int gxTreeObject::getIndex()
{
    /// The only object could be parent is gxTreeFolderObject
    /// And.. gxTreeObject could not be created without parent object

    gxTreeFolderObject* folder = (gxTreeFolderObject*) parent;
    return folder->indexOf(this);
}

