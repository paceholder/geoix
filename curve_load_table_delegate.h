#ifndef CURVE_LOAD_TABLE_DELEGATE_H
#define CURVE_LOAD_TABLE_DELEGATE_H

#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QWidget>

class gxCurveLoadTableDelegate: public QItemDelegate
{
public:
    gxCurveLoadTableDelegate(QObject *parent)
        : QItemDelegate(parent)
    {}

    void setFilesList(QStringList list);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QStringList filesList;

};

#endif // CURVE_LOAD_TABLE_DELEGATE_H
