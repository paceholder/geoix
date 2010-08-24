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


#include "surf_prop_dialog.h"
#include "ui_surf_prop_dialog.h"

#include <QRegExpValidator>

gxSurfaceOptionsDialog::gxSurfaceOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::surf_prop_dialog)
{
    ui->setupUi(this);

    //QRegExp re("[0-9]+\.+[0-9]+");
    QRegExp re("[0-9]+([\.,][0-9]+)?");
    QRegExpValidator* v = new QRegExpValidator(re, this);

    ui->lineStep->setValidator(v);
}

gxSurfaceOptionsDialog::~gxSurfaceOptionsDialog()
{
    delete ui;
}

void gxSurfaceOptionsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
