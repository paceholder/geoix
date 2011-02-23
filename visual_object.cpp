#include "visual_object.h"

#include "engine.h"
#include "mainwindow.h"

void gxVisualObject::update()
{
    QTreeView *projectTree = gxEngine::instance()->getMainWindow()->getProjectTree();
    QAbstractItemModel* model = projectTree->model();

    QModelIndex index = gxEngine::instance()->getMainWindow()->getProjectTree()->selectionModel()->currentIndex();

    // parent folder for new object
    gxTreeFolderObject* parentFolder = static_cast<gxTreeFolderObject*>(index.internalPointer());

    model->insertRow(parentFolder->count() - 1, index);

    projectTree->expand(index);
}


//------------------------------------------------------------------------------



void gxVisualObject::recreateDisplayList()
{
    if ( gl_list_3d ) glDeleteLists(gl_list_3d, 1);
    gl_list_3d = 0;

    if ( gl_list_2d ) glDeleteLists(gl_list_2d, 1);
    gl_list_2d= 0;
}


//------------------------------------------------------------------------------


void gxVisualObject::setRandomColor()
{
    srand((unsigned)time(0));
    double r = (double)rand()/(double)(RAND_MAX-1);
    double g = (double)rand()/(double)(RAND_MAX-1);
    double b = (double)rand()/(double)(RAND_MAX-1);
    r *= 0.7; g *= 0.7; b *= 0.7;

    color.setRgbF(0.3 + r, 0.3 + g, 0.3 + b);
}
