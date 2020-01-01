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



#ifndef CURVELOADDIALOG_H
#define CURVELOADDIALOG_H

#include <QtGui>
#include <QtCore>

namespace Ui
{
    class gxCurveLoadDialog;
}

class gxCurveLoadTableModel;
class gxCurveLoadTableDelegate;

class gxCurveLoadDialog : public QDialog
{
    Q_OBJECT
public:
    gxCurveLoadDialog(QWidget *parent = 0);
    ~gxCurveLoadDialog();

public slots:
    void selectFiles();
    void clearFiles();
protected:
    bool eventFilter(QObject *object, QEvent *event);
private:
    Ui::gxCurveLoadDialog *ui;

    gxCurveLoadTableModel *model;
    gxCurveLoadTableDelegate *delegate;

    QStringList fileList;

    bool handleDragEnterEvent(QDragEnterEvent *eventEnter);
    bool handleDropEvent(QObject *object, QDropEvent *dropEvent);


};

#endif // CURVELOADDIALOG_H
