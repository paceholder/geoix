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
#include <QPainter>

#include "surface.h"
#include "color_slider.h"

gxSurfaceOptionsDialog::gxSurfaceOptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::surf_prop_dialog)
{
    ui->setupUi(this);

    QRegExp re("[0-9]+([\.,][0-9]+)?"); // только числа, целые или float
    QRegExpValidator* v = new QRegExpValidator(re, this);

    ui->lineStep->setValidator(v);

    ui->groupBoxColor->layout()->addWidget(new gxColorSlider(ui->groupBoxColor));


}


gxSurfaceOptionsDialog::~gxSurfaceOptionsDialog()
{
    delete ui;
}


void gxSurfaceOptionsDialog::updateUI()
{
    ui->lineName->setText(surface->getName());

    QPainter p(ui->frameBackground);

    p.setBrush(this->surface->getColor());

}



void gxSurfaceOptionsDialog::setData(gxSurface *surface)
{
    this->surface = surface;

    ui->lineName->setText(surface->getName());

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
