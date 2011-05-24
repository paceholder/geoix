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


#include "curveloaddialog.h"

#include "ui_curveloader.h"

#include "curve_load_table_model.h"
#include "curve_load_table_delegate.h"


gxCurveLoadDialog::gxCurveLoadDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowStaysOnTopHint),
    ui(new Ui::gxCurveLoadDialog),
    model(new gxCurveLoadTableModel()),
    delegate(new gxCurveLoadTableDelegate(this))
{
    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->installEventFilter(this);
    ui->tableView->setAcceptDrops(true);

    ui->tableView->setItemDelegate(delegate);

//    ui->tableView->setEditTriggers(QAbstractItemView::SelectedClicked);

    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

gxCurveLoadDialog::~gxCurveLoadDialog()
{
    delete ui;
}



//------------------------------------------------------------------------------


bool gxCurveLoadDialog::eventFilter(QObject *object, QEvent *event)
{
    if (object != ui->tableView)
        return QDialog::eventFilter(object, event);

    switch (event->type())
    {
    case QEvent::DragEnter:
        {
            QDragEnterEvent *eventEnter = static_cast<QDragEnterEvent*>(event);
            return handleDragEnterEvent(eventEnter);
        }
    case QEvent::Drop:
        {
            QDropEvent *dropEvent = static_cast<QDropEvent*>(event);
            return handleDropEvent(object, dropEvent);
        }
    default: break;
    }

    return false;
}



//------------------------------------------------------------------------------



bool gxCurveLoadDialog::handleDragEnterEvent(QDragEnterEvent *eventEnter)
{
    if (eventEnter->mimeData()->hasFormat("geoix/well"))
    {
        eventEnter->setDropAction(Qt::CopyAction);
        eventEnter->accept();
        return true;
    }
    else
    {
        eventEnter->ignore();
        return false;
    }
}


//------------------------------------------------------------------------------


bool gxCurveLoadDialog::handleDropEvent(QObject *object, QDropEvent *dropEvent)
{
    Q_UNUSED(object);


    dropEvent->setDropAction(Qt::CopyAction);
    dropEvent->accept();

    foreach(QString format, dropEvent->mimeData()->formats())
    {
        const QMimeData *mimeData = dropEvent->mimeData();
        QByteArray encodedData = mimeData->data(format);

        QDataStream stream(&encodedData, QIODevice::ReadOnly);

        while (!stream.atEnd())
        {
            quint64 pointer;
            stream >> pointer;

            gxTreeAbstractObject *abstractObject = reinterpret_cast<gxTreeAbstractObject*>(pointer);

            model->addWell(abstractObject->getSharedPointer());
        }
    }

    return true;
}


//------------------------------------------------------------------------------


void gxCurveLoadDialog::selectFiles()
{
    fileList = QFileDialog::getOpenFileNames(this,
                                             tr("Select curve data files"),
                                             QApplication::applicationDirPath(),
                                             tr("Text Files (*)"));
    if (!fileList.size()) return;

    delegate->setFilesList(fileList);
}


//------------------------------------------------------------------------------



void gxCurveLoadDialog::clearFiles()
{
    delegate->setFilesList(QStringList());
    model->clearFiles();
}
