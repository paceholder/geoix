#include "project_tree.h"

#include <QMenu>
#include <QMouseEvent>
#include "tree_object.h"
#include "visual_object.h"
#include "engine.h"
#include "render_panel.h"
#include "tree_menu_fabric.h"

void gxProjectTree::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        event->accept();
    }
    else
        event->ignore();
}


void gxProjectTree::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        QTreeWidgetItem* item = this->itemAt(event->pos());
        if (item)
        {
            QVariant data = item->data(0, Qt::UserRole);
            gxTreeObject* object = data.value<gxTreeObject*>();

            if ((object) &&
                (object->isFolder()))
            {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            }
            else
            {
                event->setDropAction(Qt::IgnoreAction);
            }
        }
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
        event->ignore();
    }
}


void gxProjectTree::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        QByteArray output = event->mimeData()->data("geoix/tree-object");
        QDataStream stream(&output, QIODevice::ReadOnly);

        qint64 pointer = 0;
        stream >> pointer;


        gxTreeObject* object = (gxTreeObject*)pointer; // this object is moved
        if (object)
        {
            /// gettin index within the childs of previous parent
            QTreeWidgetItem* oldItem =  object->getTreeWidgetItem();
            int index = oldItem->parent()->indexOfChild(oldItem);


            /// getting new parent's WidgetItem
            QTreeWidgetItem* newParentItem = itemAt(event->pos());
            if (newParentItem)
            {
                /// Set new parent WidgetItem
                oldItem = oldItem->parent()->takeChild(index);
                newParentItem->addChild(oldItem);
                newParentItem->setExpanded(true);

                QVariant data = newParentItem->data(0, Qt::UserRole);
                gxTreeObject* newParentObject = data.value<gxTreeObject*>();

                object->changeParent(newParentObject);


            }

            dragging = false;
        }
    }
}


void gxProjectTree::mouseMoveEvent(QMouseEvent *event)
{
    if( !(event->buttons() & Qt::LeftButton) && !dragging )
    {
        return;
    }

    QTreeWidgetItem* item = currentItem();
    if( !item ) return;

    QVariant data = item->data(0, Qt::UserRole);
    gxTreeObject* object = data.value<gxTreeObject*>();

    QDrag        *drag     = new QDrag( this );
    QMimeData    *mimeData = new QMimeData;
    QByteArray    output;

    QDataStream stream(&output, QIODevice::WriteOnly);

    qint64 dd = uint(object);
    stream << dd; // maybe I should use int 64 or uint

    mimeData->setData("geoix/tree-object", output);

    drag->setMimeData( mimeData );
    drag->exec( Qt::CopyAction | Qt::MoveAction );

    dragging = true;
}


void gxProjectTree::treeContextMenu(const QPoint& point)
{
    QTreeWidgetItem* item =  this->itemAt(point);

    QPoint p = this->mapToGlobal(point);

    // little offset to prevent clickin' menu by right mouse button
    p.setX( p.x()+ 5); p.setY( p.y() + 5);

    if (item)
    {
        QVariant data = item->data(0, Qt::UserRole);

        gxTreeObject* object = data.value<gxTreeObject*>();

        QMenu* menu = object->getMenu();
        if (menu)
            menu->popup(p);
    }
    else
    {
        gxTreeMenuFabric::instance()->getTreeGeneralMenu()->popup(p);
    }
}



void gxProjectTree::treeItemChanged(QTreeWidgetItem *item, int column)
{
    if (!item) return;

    // change name of object
    QVariant data = item->data(column, Qt::UserRole);
    gxTreeObject* object = data.value<gxTreeObject*>();

    if (!object) return;

    QString s = item->text(0);
    object->setName(s);


    // set visibility/invisibility
    if (!object->isFolder())
    {
        gxVisualObject* vo = (gxVisualObject*)object;

        gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();

        if (!panel) return;

        switch (item->checkState(0))
        {
        case Qt::Checked:
            panel->registerObject(vo);
            break;
        case Qt::Unchecked:
            panel->unregisterObject(vo);
            break;
        case Qt::PartiallyChecked: break;
        }
    }
}

