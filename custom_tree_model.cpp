#include "custom_tree_model.h"


#include "render_panel.h"
#include "engine.h"

gxCustomTreeModel::gxCustomTreeModel()
    : QAbstractItemModel()
{}


int gxCustomTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}



//------------------------------------------------------------------------------


int gxCustomTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        gxTreeAbstractObject* treeobject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());
        return treeobject->count();
    }
    else
        return treeRoot->count();
}



//------------------------------------------------------------------------------



QModelIndex gxCustomTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);

    /// subtree root is not assigned
    if ( !treeRoot) return QModelIndex();

    /// subtree is empty
    if ( treeRoot->count() == 0 ) return QModelIndex();

    /// tree where we extract child
    gxTreeFolderObject* folder = treeRoot;
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



QModelIndex gxCustomTreeModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() ) return QModelIndex();

    gxTreeAbstractObject *childObject = static_cast<gxTreeAbstractObject*>(child.internalPointer());
    gxTreeFolderObject *folder = childObject->getParent();

    Q_ASSERT_X(childObject || folder, "parent", "parent or child is NULL");

    /// subtree root has empty index and invisible in tree
    if (folder == treeRoot)
        return QModelIndex();

    return createIndex(folder->getIndex(), 0, folder);
}



//------------------------------------------------------------------------------




bool gxCustomTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
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



QVariant gxCustomTreeModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() ) return QVariant();

    gxTreeAbstractObject* object = static_cast<gxTreeAbstractObject*>(index.internalPointer());
    if (!object) return QVariant();


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


QStringList gxCustomTreeModel::mimeTypes() const
{
    QStringList types;
    types << "geoix/treeabstractobject";
    return types;
}



//------------------------------------------------------------------------------



QMimeData *gxCustomTreeModel::mimeData(const QModelIndexList &indexes) const
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


//-----------------------------------------------------------------------------



Qt::DropActions gxCustomTreeModel::supportedDropActions() const
{
    return Qt::MoveAction;
}


//------------------------------------------------------------------------------



Qt::DropActions gxCustomTreeModel::supportedDragActions() const
{
    return /*Qt::CopyAction | */Qt::MoveAction;
}
