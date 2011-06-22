#include "sgs_2d_mapper.h"

#include "ui_kriging_settings_widget.h"
#include "kriging_var_core.h"

/// distributions for direct and invert transformation
#include "cumulative_distribution.h"
#include "gaussian_distr.h"

const double defaultThreshold = 100;
const double defaultRadius = 100;


gxSGS2DMapper::gxSGS2DMapper()
    : gxAbstractMapper(tr("SGS 2D")),
    ui(new Ui::KrigingSettingsWidget),
    threshold(defaultThreshold),
    radius(defaultRadius)
{
}

//------------------------------------------------------------------------------

bool gxSGS2DMapper::calcSurface(gxPoint3DList points,
                                  const gxSize3D size,
                                  const int nx, const int ny,
                                  QVector<double> &result)
{
    // first of all we should delete points
    // with equal x and y coords.
    removeEqualPoints(points);


    // least square method
    // leastSquare(points);

    //QVector<double> coeffs = gxKrigingVarianceCore::calculate(points, threshold, radius);

    result = fillResultArray(points, nx, ny, size);

    return true;
}

//------------------------------------------------------------------------------


QVector<double> gxSGS2DMapper::fillResultArray(gxPoint3DList &points,
                                               int nx, int ny,
                                               const gxSize3D &size)
{
    QVector<double> result(nx * ny);
    result.fill(0);

    double stepX = size.getW()/double(nx -1);
    double stepY = size.getH()/double(ny -1);

    double x = 0, y = 0;
    double minx = size.getMinX();
    double miny = size.getMinY();

    // here we create random path through all vertices of the lattice
    QList<QPair<int, int> > path;

    for(int i = 0; i < nx; ++i)
        for(int j = 0; j < ny; ++j)
        {
            path.append(QPair<int,int>(i, j));
        }


    /// Distribution of raw data
    gxCDF cdf(points.toVector());
    /// Creation of Gaussian distribution
    gxGaussianCDF gaussCDF;


    /// direct transformation (to normal distribution)
//    gxAbstractCDF::transform(points, &cdf, &gaussCDF);



    for (int i = 0; i < nx * ny; ++i)
    {
        // random point of the grid
        int index = rand() % path.size();
//        int index = i;
        QPair<int, int> pair = path.takeAt(index);
//        QPair<int, int> pair = path.takeFirst();
        x = minx + pair.first * stepX;
        y = miny + pair.second  * stepY;


        // solving of the ordinary kriging equations
        QVector<double> coeffs = gxOrdinaryKrigingCore::calculate(points,
                                                                  threshold,
                                                                  radius,
                                                                  x, y);
        // estimation of variance
        double variance = gxOrdinaryKrigingCore::variance(points,
                                                          coeffs,
                                                          threshold,
                                                          radius,
                                                          x, y);
        // estimation of value
        double value = gxOrdinaryKrigingCore::value(points, coeffs);

        // random probability
        double random_prob = rand() / (double)RAND_MAX;

        gxGaussianCDF localCDF(value, variance);

        // generation of value corresponding to given mean and variance
        double estimated_value = localCDF.value(random_prob);
        result[pair.second * nx + pair.first] += estimated_value;

        points.append(gxPoint3D(x, y, estimated_value));

        /// remove points with equal X and Y to avoid singularity
        removeEqualPoints(points);
    }

    /// invert transformation (to normal distribution)
//    gxAbstractCDF::transform(result, &gaussCDF, &cdf);

    return result;
}


//------------------------------------------------------------------------------


void gxSGS2DMapper::onVariogramModelActivated(int type)
{
    switch(type)
    {
    case 0: gxOrdinaryKrigingCore::setVariogramModel(gxOrdinaryKrigingCore::Exponential); break;
    case 1: gxOrdinaryKrigingCore::setVariogramModel(gxOrdinaryKrigingCore::Gaussian); break;
    case 2: gxOrdinaryKrigingCore::setVariogramModel(gxOrdinaryKrigingCore::Spherical); break;
    }
}

void gxSGS2DMapper::onThreshold(QString threshold)
{
    bool ok;
    this->threshold = threshold.toDouble(&ok);
}

void gxSGS2DMapper::onRadius(QString radius)
{
    bool ok;
    this->radius = radius.toDouble(&ok);
}


//------------------------------------------------------------------------------

QWidget *gxSGS2DMapper::getSettingsWidget(QWidget *parent)
{
    QWidget *settingsWidget = new QWidget(parent);
    ui->setupUi(settingsWidget);

    QIntValidator *validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineRadius->setValidator(validator);

    validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineThreshold->setValidator(validator);

    ui->lineRadius->setText(QString::number(defaultRadius));
    ui->lineThreshold->setText(QString::number(defaultThreshold));

    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onVariogramModelActivated(int)));
    connect(ui->lineRadius, SIGNAL(textChanged(QString)), this, SLOT(onRadius(QString)));
    connect(ui->lineThreshold, SIGNAL(textEdited(QString)), this, SLOT(onThreshold(QString)));

    return settingsWidget;;
}

