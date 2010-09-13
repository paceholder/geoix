#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <QTreeWidget>

class gxProjectTree : public QTreeWidget
{
    Q_OBJECT
public:
    gxProjectTree(QWidget* parent)
        : QTreeWidget(parent)
    {
        connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(treeContextMenu(const QPoint&)));

        connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
            this, SLOT(treeItemChanged(QTreeWidgetItem*,int)));

        setAcceptDrops(true);

        dragging = false;
    }

    virtual ~gxProjectTree() {}

protected:
    bool dragging;
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);


public slots:
    void treeContextMenu(const QPoint& point);
    void treeItemChanged(QTreeWidgetItem *item, int column);
};

#endif // PROJECT_TREE_H
