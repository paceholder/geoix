#ifndef PROJECT_TREE_H
#define PROJECT_TREE_H

#include <QTreeWidget>

/// Tree contains all projects
/*!
    Provides interface for interacting with
    projects, objects, menus, dragging.
*/
class gxProjectTree : public QTreeWidget
{
    Q_OBJECT
public:
    gxProjectTree(QWidget* parent);
    virtual ~gxProjectTree() {}

protected:
    bool dragging; //< Is dragging active
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);


public slots:
    /// Invoke context menu for project tree
    void treeContextMenu(const QPoint& point);
    /// Invoked on renaming of checking of the tree item
    void treeItemChanged(QTreeWidgetItem *item, int column);
};

#endif // PROJECT_TREE_H
