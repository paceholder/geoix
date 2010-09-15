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

#include "tree_object_folder.h"



gxTreeObject::gxTreeObject(gxTreeObjectFolder* parent)
{
    this->parent = parent;

    name = tr("Some Object");

    QTreeWidget* tree = gxEngine::instance()->getMainWindow()->getProjectTree();

    if (parent)
        widgetItem = new QTreeWidgetItem(parent->getTreeWidgetItem());
    else
        widgetItem = new QTreeWidgetItem(tree);

    widgetItem->setText(0, name);

    QVariant data = qVariantFromValue((gxTreeObject*)this);
    widgetItem->setData(0, Qt::UserRole, data);

    widgetItem->setFlags(widgetItem->flags() | Qt::ItemIsEditable);
}



gxTreeObject::~gxTreeObject()
{
    if (parent)
    {
        parent->deleteChild(this);
    }

    delete widgetItem;
}


void gxTreeObject::changeParent(gxTreeObject *newParent)
{
    if (!newParent) return;

    this->parent = (gxTreeObjectFolder*)newParent;
}


void gxTreeObject::deleteThis()
{
    // bla bla
    // ask user whether delete it or not

    delete this; // govnokod
}


void gxTreeObject::renameItem()
{
    gxEngine::instance()->getMainWindow()->getProjectTree()->editItem(widgetItem);
}
