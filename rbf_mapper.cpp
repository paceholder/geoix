#include "rbf_mapper.h"


#include <QtGui>
#include <QtAlgorithms>

#include "ui_rbf_settings_widget.h"

#include "rbf_domain.h"
#include "rbf_core.h"
#include "matrix.h"


const int defaulfTolerance = 0;


gxRBFMapper::gxRBFMapper()
    : gxAbstractMapper(tr("Radial Basis Spline")),
    ui(new Ui::RBFSettingsWidget),
    domainCapacity(defaulfDomainCapacity),
    tolerance(defaulfTolerance)
{
}

gxRBFMapper::~gxRBFMapper()
{
    delete ui;
}



//------------------------------------------------------------------------------

bool gxRBFMapper::calcSurface(gxPoint3DList points,
                              const gxSize3D size,
                              const int nx, const int ny,
                              QVector<double> &result)
{
    // first of all we should delete points
    // with equal x and y coords.
    removeEqualPoints(points);


    // least square method
    leastSquare(points);

    gxRBFDomain::setMaxLeafCapacity(this->domainCapacity);
    QScopedPointer<gxRBFDomain> rootDomain(new gxRBFDomain(Width, size, points));

    fillResultArray(rootDomain.data(), nx, ny, size, result);

    return true;
}


//------------------------------------------------------------------------------



void gxRBFMapper::fillResultArray(gxRBFDomain *rootDomain,
                                  const int nx, const int ny,
                                  const gxSize3D &size, QVector<double> &result)
{
    result.resize(nx * ny);
    result.fill(result.size(), 0);

    double stepX = size.getW()/double(nx -1);
    double stepY = size.getH()/double(ny -1);

    double x = 0, y = 0;
    double minx = size.getMinX(), miny = size.getMinY();

    for (int j = 0; j < ny; ++j)
    {
        y = miny + j * stepY;
        for (int i = 0; i < nx; ++i)
        {
            x = minx + i * stepX;

            result[j * nx + i] = rootDomain->getValue(x, y);
//            R[j*nX+i] = /*abc(0,0) * x + abc(1,0) * y + abc(2,0) +*/

        }
    }
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
    case 0: gxRBFCore::setFunctionType(gxRBFCore::Quadric); break;
    case 1: gxRBFCore::setFunctionType(gxRBFCore::Cubic); break;
    case 2: gxRBFCore::setFunctionType(gxRBFCore::ThinPlate); break;
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


