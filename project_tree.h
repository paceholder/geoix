#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <QTreeWidget>

class gxProjectTree : public QTreeWidget
{
    Q_OBJECT
public:
    gxProjectTree(QWidget* parent);
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
