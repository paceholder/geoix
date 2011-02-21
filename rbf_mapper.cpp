#include "rbf_mapper.h"


#include <QtGui>

#include "ui_rbf_settings_widget.h"


const int defaulfDomainCapacity = 500;
const int defaulfTolerance = 0;


gxRBFMapper::gxRBFMapper()
    : gxAbstractMapper(tr("Radial Basis Spline")),
    ui(new Ui::RBFSettingsWidget),
    coreFunction(Quadric),
    domainCapacity(defaulfDomainCapacity),
    tolerance(defaulfTolerance)
{
}

gxRBFMapper::~gxRBFMapper()
{
    delete ui;
}



//------------------------------------------------------------------------------


bool gxRBFMapper::calcSurface(const double *x, const double *y, const double *z,
                         double minx, double miny,
                         double maxx, double maxy,
                         int nx, int ny,
                         double *result)
{
    return false;
}




//------------------------------------------------------------------------------


QWidget *gxRBFMapper::getSettingsWidget(QWidget *parent)
{
    QWidget *settingsWidget = new QWidget(parent);
    ui->setupUi(settingsWidget);

    QIntValidator *validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineEdit->setValidator(validator);

    ui->lineEdit->setText(QString::number(defaulfDomainCapacity));

    return settingsWidget;
}


void gxRBFMapper::onSplineTypeActivated(int type)
{
    switch(type)
    {
    case 0: coreFunction = Quadric;
    case 1: coreFunction = Cubic;
    case 2: coreFunction = ThinPlate;
    }
}

void gxRBFMapper::onDomainCapacity(QString capacity)
{
    bool ok;
    this->domainCapacity = capacity.toInt(&ok);
}

void gxRBFMapper::onTolerance(int tolerance)
{
    this->tolerance = tolerance;
}


