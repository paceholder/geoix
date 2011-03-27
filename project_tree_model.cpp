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
#include "tree_object.h"
#include "tree_folder_object.h"
#include "render_panel.h"
#include "engine.h"

gxProjectTreeModel::gxProjectTreeModel(gxTreeFolderObject *projectsRootFolder/*, QObject *parent*/)
    : //QAbstractItemModel(parent),
    projectsRoot(projectsRootFolder)
{
    this->reset(); // reset model to show changes
}


int gxProjectTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}


//------------------------------------------------------------------------------



int gxProjectTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) // we deal with project
        return this->projectsRoot->count();
    else
    {
        gxTreeAbstractObject* treeobject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());
        return treeobject->count();;
    }
}


//------------------------------------------------------------------------------



QModelIndex gxProjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);

    /// subtree root is not assigned
    if ( !projectsRoot) return QModelIndex();

    /// subtree is empty
    if ( projectsRoot->count() == 0 ) return QModelIndex();

    /// tree where we extract child
    gxTreeFolderObject* folder = projectsRoot;
    if ( parent.isValid() )
    {
        gxTreeAbstractObject * object = static_cast<gxTreeAbstractObject*>(parent.internalPointer());
        if (!object) return QModelIndex();
        if (!object->isFolder()) return QModelIndex();

        // else we deal with folder
        folder = static_cast<gxTreeFolderObject*>(object);
    }

    /// strange bug forced me to write next line
    if ( folder->count() <= row) return QModelIndex();

    return createIndex(row, column, folder->getChild(row).data());
}



//------------------------------------------------------------------------------



QModelIndex gxProjectTreeModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() ) return QModelIndex();

    gxTreeAbstractObject *childObject = static_cast<gxTreeAbstractObject*>(child.internalPointer());
    gxTreeFolderObject *folder = childObject->getParent();

    Q_ASSERT_X(childObject || folder, "parent", "parent or child is NULL");

    if (folder == projectsRoot)
        return QModelIndex();

    return createIndex(folder->getIndex(), 0, folder);
}



//------------------------------------------------------------------------------




bool gxProjectTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    gxTreeAbstractObject* object = static_cast<gxTreeAbstractObject*>(index.internalPointer());
    if ( !object ) return false;

    switch (role)
    {
    case Qt::EditRole :
        object->setName(value.toString());
        break;
    case Qt::CheckStateRole:
        // set visibility/invisibility
        if (!object->isFolder())
        {
            gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();
            if (!panel) return false;

            uint checkState = value.toUInt();

            switch ( checkState )
            {
            case Qt::Checked:
                panel->registerObject(static_cast<gxVisualObject *>(object));
                break;
            case Qt::Unchecked:
                panel->unregisterObject(static_cast<gxVisualObject *>(object));
                break;
            case Qt::PartiallyChecked:
                break;
            }
        }
    }

    emit dataChanged(index, index);

    return true;
}


//------------------------------------------------------------------------------



QVariant gxProjectTreeModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() ) return QVariant();

    gxTreeAbstractObject* object = static_cast<gxTreeAbstractObject*>(index.internalPointer());
    gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();

    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant(object->getName()); break;

    // returns icon
    case Qt::DecorationRole:
        return QVariant(object->getIcon()); break;

    // returns check state
    case Qt::CheckStateRole:
        if (!panel) return QVariant(Qt::Unchecked);

        if ( panel->isObjectRegistered(static_cast<gxVisualObject *>(object)) )
            return QVariant(Qt::Checked);
        else
            return QVariant(Qt::Unchecked);

        break;

    case Qt::ForegroundRole:
        if ( object->isFolder() )
            return QVariant();

        gxVisualObject *vo = static_cast<gxVisualObject*>(object);

        return vo->hasData() ? Qt::black : Qt::gray;

        break;
    }

    return QVariant();
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
        if (object->getParent() != projectsRoot)
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

//-----------------------------------------------------------------------------

Qt::DropActions gxProjectTreeModel::supportedDropActions() const
{
    return Qt::MoveAction;
}


//------------------------------------------------------------------------------

Qt::DropActions gxProjectTreeModel::supportedDragActions() const
{
    return /*Qt::CopyAction | */Qt::MoveAction;
}

//------------------------------------------------------------------------------


QStringList gxProjectTreeModel::mimeTypes() const
{
    QStringList types;
    types << "geoix/treeabstractobject";
    return types;
}



//------------------------------------------------------------------------------



QMimeData *gxProjectTreeModel::mimeData(const QModelIndexList &indexes) const
 {
     QMimeData *mimeData = new QMimeData();
     QByteArray encodedData;

     QDataStream stream(&encodedData, QIODevice::WriteOnly);

     foreach (QModelIndex index, indexes)
     {
         if (index.isValid())
         {
             void *abstractObject = index.internalPointer();
             if (! abstractObject) continue;
             /// here we turn pointer to 64bit int to pack it into stream
             stream << (quint64)abstractObject;
         }
     }

     mimeData->setData("geoix/treeabstractobject", encodedData);
     return mimeData;
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


        gxTreeAbstractObject * obj = (gxTreeAbstractObject*)parent.internalPointer();

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
