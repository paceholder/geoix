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


#ifndef SPLINER_DIALOG_H
#define SPLINER_DIALOG_H

#include <QDialog>

#include "abstract_mapper.h"
#include "tree_abstract_object.h"

namespace Ui {
    class SplinerDialog;
}

class gxTreeFolderObject;

/// Dialog for building the spline surfaces
class gxSplinerDialog : public QDialog {
    Q_OBJECT
public:
    gxSplinerDialog(QWidget *parent = 0);
    ~gxSplinerDialog();

protected:
    void changeEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::SplinerDialog *ui;

    gxTreeFolderObject *folder;

    /// list of modules for calculation of spline
    QList<QSharedPointer<gxAbstractMapper> > mapperList;

    QList<QSharedPointer<gxTreeAbstractObject> > objectList;


    bool handleDragEnterEvent(QDragEnterEvent *event);
    bool handleDropEvent(QDropEvent *event);

public slots:
    void onClose();
    void onCalculate();

private slots:
    void setupMapper(int index);
};

#endif // gxSplinerDialog_H
