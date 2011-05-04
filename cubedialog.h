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

#ifndef CUBEDIALOG_H
#define CUBEDIALOG_H

#include <QDialog>

#include "tree_abstract_object.h"

namespace Ui {
    class gxCubeDialog;
}

class gxCubeDialog : public QDialog {
    Q_OBJECT
public:
    gxCubeDialog(QWidget *parent = 0);
    ~gxCubeDialog();

protected:
    void changeEvent(QEvent *e);

    bool eventFilter(QObject *object, QEvent *event);

private:
    QSharedPointer<gxTreeAbstractObject> topSurface;
    QSharedPointer<gxTreeAbstractObject> bottomSurface;

    Ui::gxCubeDialog *ui;

    bool handleDragEnterEvent(QDragEnterEvent *event);
    bool handleDropEvent(QObject *object, QDropEvent *event);
};

#endif // CUBEDIALOG_H
