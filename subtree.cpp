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


#include "subtree.h"

#include "tree_object.h"
#include <QMouseEvent>

#include "logger.h"

gxSubTree::gxSubTree(QWidget* parent)
    : QTreeWidget(parent)
{
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(treeContextMenu(const QPoint&)));

    connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
        this, SLOT(treeItemChanged(QTreeWidgetItem*,int)));

    setAcceptDrops(true);

    dragging = false;
}



void gxSubTree::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        event->accept();
    }
    else
        event->ignore();
}


void gxSubTree::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("geoix/tree-object"))
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();

        QTreeWidgetItem* item = this->itemAt(event->pos());
        if (item)
        {
            QVariant data = item->data(0, Qt::UserRole);
            gxTreeObject* object = data.value<gxTreeObject*>();

            if ((object) && (! object->isFolder()))
            {
                event->setDropAction(Qt::IgnoreAction);
                event->ignore();
            }
        }
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
        event->ignore();
    }
}


void gxSubTree::dropEvent(QDropEvent *event)
{
//    if (event->mimeData()->hasFormat("geoix/tree-object"))
//    {
//        QByteArray output = event->mimeData()->data("geoix/tree-object");
//        QDataStream stream(&output, QIODevice::ReadOnly);
//
//        qint64 pointer = 0;
//        stream >> pointer; /// get pointer out of data stream
//
//
//        gxTreeObject* object = (gxTreeObject*)pointer; // this object is moved
//        if (object)
//        {
//            /// gettin index within the childs of previous parent
//            QTreeWidgetItem* oldItem =  object->getTreeWidgetItem();
//            int index = oldItem->parent()->indexOfChild(oldItem);
//
//
//            /// getting new parent's WidgetItem
//            QTreeWidgetItem* newParentItem = itemAt(event->pos());
//            if (newParentItem)
//            {
//                /// Set new parent WidgetItem
//                oldItem = oldItem->parent()->takeChild(index);
//                newParentItem->addChild(oldItem);
//                newParentItem->setExpanded(true);
//
//                QVariant data = newParentItem->data(0, Qt::UserRole);
//                gxTreeObject* newParentObject = data.value<gxTreeObject*>();
//
//                object->changeParent(newParentObject);
//            }
//            else
//            {
//                oldItem = oldItem->parent()->takeChild(index);
//                this->addTopLevelItem(oldItem);
//            }
//
//            dragging = false;
//        }
//    }
}


void gxSubTree::mouseMoveEvent(QMouseEvent *event)
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

    dragging = false;
}


void gxSubTree::treeContextMenu(const QPoint &point)
{
    //

}

void gxSubTree::treeItemChanged(QTreeWidgetItem *item, int column)
{
    //
}
