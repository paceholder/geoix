#include "sgs_2d_mapper.h"

#include "ui_kriging_settings_widget.h"
#include "kriging_var_core.h"

/// distributions for direct and invert transformation
#include "cumulative_distribution.h"
#include "gaussian_distr.h"

const double defaultSill = 100;
const double defaultNugget = 0;
const double defaultRadius = 100;
const double defaultRotationAngle = 0;
const gxKrigingParams2D::VariogramModel defaultVariogramModel = gxKrigingParams2D::Exponential;


gxSGS2DMapper::gxSGS2DMapper()
    : gxAbstractMapper(tr("SGS 2D")),
    ui(new Ui::KrigingSettingsWidget),
    params(defaultVariogramModel,
           defaultRadius,
           defaultRadius,
           defaultRotationAngle,
           defaultSill,
           defaultNugget)
{
}

//------------------------------------------------------------------------------

bool gxSGS2DMapper::calcSurface(gxPoint3DList points,
                                  const gxSize3D size,
                                  const int nx, const int ny,
                                  std::vector<double> &result)
{
    // first of all we should delete points
    // with equal x and y coords.
    removeEqualPoints(points);


    // least square method
    // leastSquare(points);

    gxOrdinaryKrigingCore2D krigingCore(params);
    //QVector<double> coeffs = gxKrigingVarianceCore::calculate(points, threshold, radius);

    result = fillResultArray(points, krigingCore, nx, ny, size);

    return true;
}

//------------------------------------------------------------------------------


std::vector<double> gxSGS2DMapper::fillResultArray(gxPoint3DList &points,
                                               gxOrdinaryKrigingCore2D &krigingCore,
                                               int nx, int ny,
                                               const gxSize3D &size)
{
    std::vector<double> result(nx * ny);
    std::fill(result.begin(), result.end(), 0.0);

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
    /// Gaussian distribution (meance = 0, var = 1)
    gxGaussianCDF gaussCDF;


    /// direct transformation (to normal distribution)
//    gxAbstractCDF::transform(points, &cdf, &gaussCDF);



    for (int i = 0; i < nx * ny; ++i)
    {
        // random point of the grid
        int index = rand() % path.size();

        QPair<int, int> pair = path.takeAt(index);
        x = minx + pair.first * stepX;
        y = miny + pair.second  * stepY;


        // solving of the ordinary kriging equations at point (X, Y)
        QVector<double> coeffs = krigingCore.calculate(points,
                                                       x, y);
        // estimation of variance at point (X, Y)
        double variance = krigingCore.variance(points,
                                               coeffs,
                                               x, y);
        // estimation of value at point (X, Y)
        double value = krigingCore.value(points, coeffs);

        // random probability in range (0, 1)
        double random_prob = rand() / (double)RAND_MAX;

        // gaussian distribution with given parameters
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
    case 0: params.variogramModel = gxKrigingParams2D::Exponential; break;
    case 1: params.variogramModel = gxKrigingParams2D::Gaussian; break;
    case 2: params.variogramModel = gxKrigingParams2D::Spherical; break;
    }
}

void gxSGS2DMapper::onSill(QString sill)
{
    bool ok;
    params.sill = sill.toDouble(&ok);
}

void gxSGS2DMapper::onRadius(QString radius)
{
    bool ok;
    params.rangex = radius.toDouble(&ok);
}


//------------------------------------------------------------------------------

QWidget *gxSGS2DMapper::getSettingsWidget(QWidget *parent)
{
    QWidget *settingsWidget = new QWidget(parent);
    ui->setupUi(settingsWidget);

    QIntValidator *validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineRadiusA->setValidator(validator);

    validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineRadiusB->setValidator(validator);

    validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineSill->setValidator(validator);

    ui->lineRadiusA->setText(QString::number(defaultRadius));
    ui->lineRadiusB->setText(QString::number(defaultRadius));
    ui->lineSill->setText(QString::number(defaultSill));
    ui->lineNugget->setText(QString::number(defaultNugget));

    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onVariogramModelActivated(int)));
    connect(ui->lineRadiusA, SIGNAL(textChanged(QString)), this, SLOT(onRadius(QString)));
    connect(ui->lineRadiusB, SIGNAL(textChanged(QString)), this, SLOT(onRadius(QString)));
    connect(ui->lineSill, SIGNAL(textEdited(QString)), this, SLOT(onSill(QString)));

    return settingsWidget;;
}

