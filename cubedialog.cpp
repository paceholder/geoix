#include "cubedialog.h"
#include "ui_cubedialog.h"

gxCubeDialog::gxCubeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gxCubeDialog)
{
    ui->setupUi(this);

    QStringList list;
    list << "Top" << "Bottom";
    ui->cbBaseGrid->addItems(list);

    list.clear();
    list << "From top" << "From bottom" << "Proportional";
    ui->cbSedimentationModel->addItems(list);
}

gxCubeDialog::~gxCubeDialog()
{
    delete ui;
}

void gxCubeDialog::changeEvent(QEvent *e)
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
