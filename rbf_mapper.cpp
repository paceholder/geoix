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

bool gxRBFMapper::calcSurface(gxPoints3DList points,
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

void gxRBFMapper::removeEqualPoints(gxPoints3DList &points)
{
    qSort(points.begin(), points.end(), pointXLessThan);
    int i = points.size() - 1; // last point

    // look over all points
    while (i > 0)
    {
        // here we collect points with equall x and y
        int j = i;
        double average = 0;
        while (qAbs(points[i].x - points[j].x) < Gx::Eps &&
               qAbs(points[i].y - points[j].y) < Gx::Eps && j >= 0)
        {
            average += points[j].z;
            --j;
        }

        // if number of equall points is N > 0
        if (i - j > 0)
        {
            // remove N - 1 ponts from the end
            points.erase(points.begin() + j + 1, points.end());
            // and replace Nth point from the end with average z-value
            points[j].z = average / double(i - j);
            i = j - 1;
        }
        else --i;
    }

}



//------------------------------------------------------------------------------



void gxRBFMapper::leastSquare(gxPoints3DList &points)
{
    math::matrix<double> M(3,3);
    math::matrix<double> D(3,1);
    math::matrix<double> abc(3,1);

    for(int i = 0; i<3; ++i)
    {
        M(i,0) = 0.0;
        abc(i,0) = 0.0;
        D(i,0) = 0.0;
        for(int j=0; j<3; ++j)
        {
            M(i,j) =0.0;
        }
    }


    for(int i = 0; i < points.size(); ++i)
    {
        double X,Y,Z;
        X = points[i].x;
        Y = points[i].y;
        Z = points[i].z;

        M(0,0) += X*X;
        M(0,1) += X*Y;
        M(1,1) += Y*Y;
        M(0,2) += X;
        M(1,2) += Y;
        D(0,0) += X*Z;
        D(1,0) += Y*Z;
        D(2,0) += Z;
    }
    M(2,1) = M(1,2);
    M(2,0) = M(0,2);
    M(1,0) = M(0,1);
    M(2,2) = points.size();

    abc = M.Solve(D);

    double A = abc(0,0), B = abc(1,0), C = abc(2,0);
    for(int i = 0; i < points.size(); ++i)
    {
        points[i].z -=  A * points[i].x + B * points[i].y + C;
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


