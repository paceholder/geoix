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


#ifndef SPLINER_DIALOG_H
#define SPLINER_DIALOG_H

#include <QDialog>

namespace Ui {
    class spliner_dialog;
}

/// Dialog for building the spline surfaces
class spliner_dialog : public QDialog {
    Q_OBJECT
public:
    spliner_dialog(QWidget *parent = 0);
    ~spliner_dialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::spliner_dialog *ui;
};

#endif // SPLINER_DIALOG_H
