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

#include <QtCore>

#include "spliner_dialog.h"
#include "ui_spliner_dialog.h"

//#include "drop_widget.h"
#include "rbf_mapper.h"

/// Constructor. Creates Dialog window for spline calculations
spliner_dialog::spliner_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spliner_dialog)
{
    ui->setupUi(this);

    // adding mappers
    mapperList.append(QSharedPointer<gxAbstractMapper>(new gxRBFMapper()));

    // adding mappers' names
    foreach(QSharedPointer<gxAbstractMapper> mapper, mapperList)
    {
        ui->mappersComboBox->addItem(mapper.data()->getName());
    }

    setupMapper();

    /// Widget wich takes drops and create signals on dropping event
//    gxDropWidget* widget = new gxDropWidget(this);
//    widget->setGeometry(0, 0, 40, 20);
//    widget->setMinimumSize(40, 20);
//    widget->show();
//    widget->setLayout(ui->verticalLayout_6);
//
//    ui->verticalLayout_6->insertWidget(0, widget);

}

spliner_dialog::~spliner_dialog()
{
    delete ui;
}

void spliner_dialog::changeEvent(QEvent *e)
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

void spliner_dialog::setupMapper()
{
    int index = ui->mappersComboBox->currentIndex();

    QWidget *settingsWidget = mapperList[index].data()->getSettingsWidget(this);
    if (settingsWidget)
    {
//        // remove previous widget
        ui->settingsLayout->takeAt(0);
//        // add new widget
        ui->settingsLayout->addWidget(settingsWidget);
    }
}
