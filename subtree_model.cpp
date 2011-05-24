#include "subtree_model.h"

#include "engine.h"


gxSubtreeModel::gxSubtreeModel()
    : gxCustomTreeModel()
{
    this->setSupportedDragActions(Qt::MoveAction);


    treeRoot = new gxTreeFolderObject();
    treeRoot->setName("Subtree Root");
    this->reset(); // reset model to show changes

}



//------------------------------------------------------------------------------


gxSubtreeModel::~gxSubtreeModel()
{
    delete treeRoot;
}


//------------------------------------------------------------------------------




Qt::ItemFlags gxSubtreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index)
                                 | Qt::ItemIsEditable
                                 | Qt::ItemIsDropEnabled;

    if (index.isValid())
    {
        gxTreeAbstractObject *object = static_cast<gxTreeAbstractObject*>(index.internalPointer());
        Q_ASSERT_X( object, "flags", "objects is NULL" );

        if ( !object->isFolder() )
            defaultFlags |= Qt::ItemIsUserCheckable;


        // project branch can not be dragged
        if (object != treeRoot)
            defaultFlags |=  Qt::ItemIsDragEnabled;
    }

    return defaultFlags;
}



//------------------------------------------------------------------------------


bool gxSubtreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool success = true;

    beginInsertRows(parent, row, row + count - 1);
    // epic shit
    endInsertRows();

    return success;
}

//------------------------------------------------------------------------------

bool gxSubtreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool success = true;

    beginRemoveRows(parent, row, row + count - 1);

        if ( parent.isValid() )
        {
            gxTreeFolderObject *folder = static_cast<gxTreeFolderObject*>(parent.internalPointer());
            Q_ASSERT_X(folder->isFolder(), "removeRows", "folder is not folder =)");

            folder->deleteChild(row);
        }
        else
            treeRoot->deleteChild(row);

    endRemoveRows();

    return success;
}


//------------------------------------------------------------------------------


bool gxSubtreeModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(row);
    Q_UNUSED(column);


    if (action == Qt::IgnoreAction || action == Qt::CopyAction)
        return false;

//    if (!data->hasFormat("geoix/treeabstractobject"))
//        return false;


    QByteArray encodedData = data->data(data->formats()[0]);
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    while (!stream.atEnd())
    {
        quint64 pointer;
        stream >> pointer;
        void *object = (void*)pointer;

        gxTreeAbstractObject *abstractObject = static_cast<gxTreeAbstractObject*>(object);

        gxTreeAbstractObject *parentObject = treeRoot;
        if (parent.isValid())
            parentObject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());


        // if this object is moved to the same parent we stop the dragging
        if (abstractObject->getParent() == parentObject )
            return false;

        QSharedPointer<gxTreeAbstractObject> sharedPointer = abstractObject->getSharedPointer();


        gxTreeFolderObject* newFolder = static_cast<gxTreeFolderObject*>(parentObject);

        beginInsertRows(parent, newFolder->count(), newFolder->count());
        newFolder->addChild(sharedPointer);
        endInsertRows();


        break; ///  <<<<<======
    }

    return true;
}
