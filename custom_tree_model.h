#ifndef CUSTOM_TREE_MODEL_H
#define CUSTOM_TREE_MODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QMimeData>

#include "tree_folder_object.h"

class gxCustomTreeModel : public QAbstractItemModel
{
    //Q_OBJECT
public:
    gxCustomTreeModel();
    virtual ~gxCustomTreeModel() {}
protected:
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;

    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;

    Qt::DropActions supportedDropActions() const;

    /// root of tree
    gxTreeFolderObject* treeRoot;
};

#endif // CUSTOM_TREE_MODEL_H
