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



#include "project_tree_model.h"
#include "project.h"
#include "engine.h"

gxProjectTreeModel::gxProjectTreeModel(gxTreeFolderObject *projectTreeRoot)
    : gxCustomTreeModel()
{
    treeRoot = projectTreeRoot;
    this->reset(); // reset model to show changes
}



//------------------------------------------------------------------------------




Qt::ItemFlags gxProjectTreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index)
                                 | Qt::ItemIsEditable;

    if (index.isValid())
    {
        gxTreeAbstractObject *object = static_cast<gxTreeAbstractObject*>(index.internalPointer());

        if ( object->isFolder() )
            defaultFlags |= Qt::ItemIsDropEnabled;
        else
            defaultFlags |= Qt::ItemIsUserCheckable;


        // project branch can not be dragged
        if (object->getParent() != treeRoot)
            defaultFlags |=  Qt::ItemIsDragEnabled;
    }

    return defaultFlags;
}


//------------------------------------------------------------------------------


bool gxProjectTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success = true;

    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();

    return success;
}


//------------------------------------------------------------------------------

bool gxProjectTreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool success = true;

    beginRemoveRows(parent, row, row + count - 1);

        if ( parent.isValid() )
        {
            gxTreeFolderObject *folder = static_cast<gxTreeFolderObject*>(parent.internalPointer());
            folder->deleteChild(row);
        }
        else
            gxEngine::instance()->deleteProject(row);

    endRemoveRows();

    return success;
}


//------------------------------------------------------------------------------


bool gxProjectTreeModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (action == Qt::CopyAction)
        return false;

    if (!data->hasFormat("geoix/treeabstractobject"))
        return false;

    QByteArray encodedData = data->data("geoix/treeabstractobject");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        quint64 pointer;
        stream >> pointer;
        void *object = (void*)pointer;

        gxTreeAbstractObject *abstractObject = static_cast<gxTreeAbstractObject*>(object);

        gxTreeAbstractObject *parentObject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());

        // if this object is moved to the same parent we stop the dragging
        if (abstractObject->getParent() == parentObject )
            return false;

        QSharedPointer<gxTreeAbstractObject> sharedPointer = abstractObject->getSharedPointer();

        gxTreeFolderObject* newFolder = static_cast<gxTreeFolderObject*>(parent.internalPointer());


        //gxTreeAbstractObject * obj = (gxTreeAbstractObject*)parent.internalPointer();

        beginInsertRows(parent, newFolder->count(), newFolder->count());
        newFolder->addChild(sharedPointer);
        endInsertRows();
////
//        QMessageBox::information(0, tr("ololo"), sharedPointer->getParent()->getName());
//        QMessageBox::information(0, tr("ololo"), QString::number(newFolder->count()));
//        QMessageBox::information(0, "ololo",  fol->getName());
//        QMessageBox::information(0, "ololo",  QString::number(fol->count()));

        // NOW I READ JUST ONE ITEM
        // coz I dont know how I will process multiselection in tree
        break; ///  <<<<<======
        // !!!
    }

    return false;
}
