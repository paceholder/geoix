#ifndef SUBTREE_H
#define SUBTREE_H


#include <QTreeWidget>

class gxSubTree : public QTreeWidget
{
    Q_OBJECT
public:
    gxSubTree(QWidget* parent);

    virtual ~gxSubTree() {}

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



#endif // SUBTREE_H
