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



#include "curve_load_table_model.h"

#include "well.h"
#include "tree_folder_object.h"


gxCurveLoadTableModel::gxCurveLoadTableModel()
{

}

void gxCurveLoadTableModel::addWell(QSharedPointer<gxTreeAbstractObject> well)
{
    // no duplicates
    QListIterator<QPair<QSharedPointer<gxTreeAbstractObject>, QString> > it(wells);

    while(it.hasNext())
    {
        if (it.next().first.data() == well.data() ) return;
    }

    wells.append(QPair<QSharedPointer<gxTreeAbstractObject>, QString>(well, QString()));

    //this->reset();
}


void gxCurveLoadTableModel::setFileForWell(const QModelIndex index, QString filename)
{
    this->wells[index.row()].second = filename;
}

void gxCurveLoadTableModel::clearFiles()
{
    QMutableListIterator<QPair<QSharedPointer<gxTreeAbstractObject>, QString> > it(wells);

    while(it.hasNext())
        it.next().second.clear();

    //this->reset();
}


//------------------------------------------------------------------------------


int gxCurveLoadTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return wells.size();
}


int gxCurveLoadTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QModelIndex gxCurveLoadTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column, row);
}


QModelIndex gxCurveLoadTableModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant gxCurveLoadTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch(section)
        {
        case 0:
            if ( role == Qt::DisplayRole )
              return tr("Well Name");
            break;
        case 1:
            if ( role == Qt::DisplayRole )
              return tr("File Name");
            break;
        }
    }
    else
    {
        return QString::number(section);
    }

    return QVariant();
}

//------------------------------------------------------------------------------


Qt::ItemFlags gxCurveLoadTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if (index.column() == 1) flags |= Qt::ItemIsEditable;

    return flags;
}

//------------------------------------------------------------------------------

QVariant gxCurveLoadTableModel::data(const QModelIndex &index, int role) const
{
    const gxWell* well = static_cast<gxWell*>(wells[index.row()].first.data());

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0:
            return well->getName();
            break;
        case 1:
            {
                QFileInfo info(wells[index.row()].second);
                return info.fileName();
            }
            break;
        }
        break;
    case Qt::ToolTipRole:
        switch (index.column())
        {
        case 0:
            return well->getParent()->getName() + "/" + well->getName();
            break;
        case 1:
            return wells[index.row()].second;
            break;
        }
        break;
    }

    return QVariant();
}


//------------------------------------------------------------------------------


bool gxCurveLoadTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(index);
    Q_UNUSED(role);
    Q_UNUSED(value);
    return false;
}
