#include "subtree_model.h"


#include "tree_folder_object.h"
#include "engine.h"
#include "render_panel.h"

gxSubtreeModel::gxSubtreeModel(/*gxTreeFolderObject *projectsRootFolder, QObject *parent*/)
//    :  QAbstractItemModel(parent),
//    subtreeRoot(projectsRootFolder)
{
    subtreeRoot = new gxTreeFolderObject();
    this->reset(); // reset model to show changes
}



//------------------------------------------------------------------------------


gxSubtreeModel::~gxSubtreeModel()
{
    delete subtreeRoot;
}


//------------------------------------------------------------------------------


int gxSubtreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}



//------------------------------------------------------------------------------


int gxSubtreeModel::rowCount(const QModelIndex &parent) const
{
    // we deal with project
    if (parent.isValid())
    {
        gxTreeAbstractObject* treeobject = static_cast<gxTreeAbstractObject*>(parent.internalPointer());
        return treeobject->count();
    }
    else
        return subtreeRoot->count();
}




//------------------------------------------------------------------------------



QModelIndex gxSubtreeModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(column);

    /// subtree root is not assigned
    if ( !subtreeRoot) return QModelIndex();

    /// subtree is empty
    if ( subtreeRoot->count() == 0 ) return QModelIndex();

    /// tree where we extract child
    gxTreeFolderObject* folder = subtreeRoot;
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



QModelIndex gxSubtreeModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() ) return QModelIndex();

    gxTreeAbstractObject *childObject = static_cast<gxTreeAbstractObject*>(child.internalPointer());
    gxTreeFolderObject *folder = childObject->getParent();

    Q_ASSERT_X(childObject || folder, "parent", "parent or child is NULL");

    /// subtree root has empty index and invisible in tree
    if (folder == subtreeRoot)
        return QModelIndex();

    return createIndex(folder->getIndex(), 0, folder);
}



//------------------------------------------------------------------------------




bool gxSubtreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
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



QVariant gxSubtreeModel::data(const QModelIndex &index, int role) const
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
        if (object != subtreeRoot)
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
            gxEngine::instance()->deleteProject(row);

    endRemoveRows();

    return success;
}


//-----------------------------------------------------------------------------

Qt::DropActions gxSubtreeModel::supportedDropActions() const
{
    return Qt::MoveAction;
}


//------------------------------------------------------------------------------

Qt::DropActions gxSubtreeModel::supportedDragActions() const
{
    return /*Qt::CopyAction | */Qt::MoveAction;
}



//------------------------------------------------------------------------------


QStringList gxSubtreeModel::mimeTypes() const
{
    QStringList types;
    types << "geoix/treeabstractobject";
    return types;
}



//------------------------------------------------------------------------------



QMimeData *gxSubtreeModel::mimeData(const QModelIndexList &indexes) const
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


bool gxSubtreeModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction || action == Qt::CopyAction)
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

        gxTreeAbstractObject *parentObject = subtreeRoot;
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

    return false;
}
