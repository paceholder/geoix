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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef SURF_PROP_DIALOG_H
#define SURF_PROP_DIALOG_H

#include <QDialog>

namespace Ui {
    class surf_prop_dialog;
}


class gxSurface;

class gxSurfaceOptionsDialog : public QDialog {
    Q_OBJECT
public:
    gxSurfaceOptionsDialog(QWidget *parent = 0);
    ~gxSurfaceOptionsDialog();

    void setData(gxSurface* surface) { this->surface = surface; }


protected:
    void changeEvent(QEvent *e);

private:
    Ui::surf_prop_dialog *ui;
    gxSurface* surface;
};

#endif // SURF_PROP_DIALOG_H
