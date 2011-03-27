#include "tree_abstract_object.h"

#include "tree_folder_object.h"

#include "mainwindow.h"
#include "engine.h"

#include <QtGui>
#include <QtCore>

void gxTreeAbstractObject::deleteThis()

{
    QModelIndex index = gxEngine::instance()->getMainWindow()->getProjectTree()->currentIndex();

    QAbstractItemModel* model = gxEngine::instance()->getMainWindow()->getProjectTree()->model();
    model->removeRow(index.row(), index.parent());
}

//------------------------------------------------------------------------------

QSharedPointer<gxTreeAbstractObject> gxTreeAbstractObject::getSharedPointer()
{
    // if parent if null
    if (!parent) return QSharedPointer<gxTreeAbstractObject>();


    // look over each object in children list
    foreach(QSharedPointer<gxTreeAbstractObject> sharedPointer, parent->children)
    {
        if (sharedPointer.data() == this)
        {
            return sharedPointer;
        }
    }

    // if object is nof found
    return QSharedPointer<gxTreeAbstractObject>();
}


//------------------------------------------------------------------------------

void gxTreeAbstractObject::setParent(gxTreeFolderObject* newParent)
{
    this->parent = newParent;
}
