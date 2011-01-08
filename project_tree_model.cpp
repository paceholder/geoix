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

#include "tree_object.h"
#include "render_panel.h"
#include "engine.h"

gxProjectTreeModel::gxProjectTreeModel(gxProjectList* projects, QObject* parent)
    : QAbstractItemModel(parent)
{
    this->projects = projects;
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
    {
        return this->projects->size();
    }
    else
    {
        gxTreeAbstractObject* treeobject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());

        return treeobject->count();
    }
}


//------------------------------------------------------------------------------



QModelIndex gxProjectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);

    /// Invalid parent means that we have to return index for project
    if ( !parent.isValid() )
    {
        return createIndex(row, column, this->projects->at(row));
    }
    else
    {
        // else we deal with folder
        gxTreeFolderObject* folder = static_cast<gxTreeFolderObject*>(parent.internalPointer());

        if ( folder )
            return createIndex(row, column, folder->getChild(row));
        else
            return QModelIndex();
    }
}



//------------------------------------------------------------------------------



QModelIndex gxProjectTreeModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() ) return QModelIndex();

    gxTreeAbstractObject *childObject = static_cast<gxTreeAbstractObject*>(child.internalPointer());
    gxTreeFolderObject *folder = childObject->getParent();

    if ( folder )
    {
        gxTreeFolderObject *parentFolder = folder->getParent();

        if ( parentFolder )
            return createIndex(parentFolder->indexOf(folder), 0, folder);
        else
            // if folder has no parent, it is definitely gxProgect
            return createIndex(this->projects->indexOf( (gxProject *)folder), 0, folder);
    }
    else
    {
        return QModelIndex();
    }
}



//------------------------------------------------------------------------------




bool gxProjectTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
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

    // returns font
//    case Qt::FontRole:
//        if ( ! object->isFolder() )
//        {
//            gxVisualObject *vo = static_cast<gxVisualObject*>(object);
//
//            QFont font;
////            font.se
////            font.setBold( vo->hasData() );
//            return font;
//        }
//        break;

    case Qt::ForegroundRole:
        if ( ! object->isFolder() )
        {
            gxVisualObject *vo = static_cast<gxVisualObject*>(object);

            if ( vo->hasData())
                return Qt::black;
            else
                return Qt::gray;
        }
        break;

    default : return QVariant(); break;
    }
}


Qt::ItemFlags gxProjectTreeModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}


bool gxProjectTreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success;

    beginInsertRows(parent, row, row + count - 1);
    endInsertRows();

    return success;
}
