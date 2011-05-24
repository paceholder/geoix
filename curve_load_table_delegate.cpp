#include "curve_load_table_delegate.h"

#include <QtGui>

#include "curve_load_table_model.h"

QWidget* gxCurveLoadTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);

    return comboBox;
}


//------------------------------------------------------------------------------


void gxCurveLoadTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);

    comboBox->addItem(tr("no"));

    foreach(QString file, filesList)
    {
        QFileInfo info(file);

        comboBox->addItem(info.fileName());
    }

    comboBox->setCurrentIndex(0);
}


//------------------------------------------------------------------------------


void gxCurveLoadTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (!filesList.size()) return;

    QComboBox *comboBox = static_cast<QComboBox*>(editor);

    gxCurveLoadTableModel* m = static_cast<gxCurveLoadTableModel*>(model);


    if (comboBox->currentIndex() <=0 ) m->setFileForWell(index, QString(""));

    // set current file for well
    m->setFileForWell(index, filesList[comboBox->currentIndex() - 1]);
}



//------------------------------------------------------------------------------


void gxCurveLoadTableDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}


void gxCurveLoadTableDelegate::setFilesList(QStringList list)
{
    filesList = list;
}
