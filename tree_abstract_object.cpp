#include "tree_abstract_object.h"

#include "engine.h"

#include <QtGui>
#include <QtCore>

void gxTreeAbstractObject::deleteThis()

{
    QModelIndex index = gxEngine::instance()->getMainWindow()->getProjectTree()->currentIndex();

    QAbstractItemModel* model = gxEngine::instance()->getMainWindow()->getProjectTree()->model();
    model->removeRow(index.row(), index.parent());
}
