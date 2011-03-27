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

#ifndef SUBTREE_MODEL_H
#define SUBTREE_MODEL_H


#include <QAbstractItemModel>

class gxTreeFolderObject;

class gxSubtreeModel : QAbstractItemModel
{
    Q_OBJECT
public:
    gxSubtreeModel(/*gxTreeFolderObject* projectsRootFolder, QObject* parent*/);
    virtual ~gxSubtreeModel();
protected:
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant data(const QModelIndex &index, int role) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::DropActions supportedDropActions() const;
    Qt::DropActions supportedDragActions() const;

    QStringList mimeTypes() const;

    QMimeData *mimeData(const QModelIndexList &indexes) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
private:
    /// this folder can only contain other folders and object but not Projects
    /// Items contained in this folder are not included to any of projects
    gxTreeFolderObject* subtreeRoot;
};

#endif // SUBTREE_MODEL_H
