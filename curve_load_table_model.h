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
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef CURVE_LOAD_TABLE_MODEL_H
#define CURVE_LOAD_TABLE_MODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QSharedPointer>

#include "tree_abstract_object.h"

class gxCurveLoadTableModel : public QAbstractItemModel
{
public:
    gxCurveLoadTableModel();

    void addWell(QSharedPointer<gxTreeAbstractObject> well);
    void setFileForWell(const QModelIndex index, QString filename);
    void clearFiles();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    QList<QPair<QSharedPointer<gxTreeAbstractObject>, QString> > wells;
};

#endif // CURVE_LOAD_TABLE_MODEL_H
