#include "kriging_var_mapper.h"

//#include "ui_kriging_settings_widget.h"
#include "kriging_var_core.h"


const double defaultThreshold = 100;
const double defaultRadius = 100;


gxKrigingVarianceMapper::gxKrigingVarianceMapper()
    : gxAbstractMapper(tr("Kriging Variance")),
//    ui(new Ui::KrigingSettingsWidget),
    threshold(defaultThreshold),
    radius(defaultRadius)
{
}

//------------------------------------------------------------------------------

bool gxKrigingVarianceMapper::calcSurface(gxPoint3DList points,
                                  const gxSize3D size,
                                  const int nx, const int ny,
                                  QVector<double> &result)
{
    // first of all we should delete points
    // with equal x and y coords.
    //removeEqualPoints(points);


    // least square method
//    leastSquare(points);

    //QVector<double> coeffs = gxKrigingVarianceCore::calculate(points, threshold, radius);

    result = fillResultArray(points, nx, ny, size);

    return true;
}

//------------------------------------------------------------------------------


QVector<double> gxKrigingVarianceMapper::fillResultArray(gxPoint3DList &points,
                                                         int nx, int ny,
                                                         const gxSize3D &size)
{
    QVector<double> result(nx * ny);
    result.fill(0);

    double stepX = size.getW()/double(nx -1);
    double stepY = size.getH()/double(ny -1);

    double x = 0, y = 0;
    double minx = size.getMinX(), miny = size.getMinY();

    for (int j = 0; j < ny; ++j)
    {
        y = miny + j * stepY;
        for (int i = 0; i < nx; ++i)
        {
//            x = minx + i * stepX;

//            int cell =  j * nx + i;
//            result[cell] = 0;

//            for(int k = 0; k < coeffs.size() - 3; ++k)
//                result[cell] += coeffs[k] * gxKrigingVarianceCore::coreFunction(threshold, radius, points[k].distance2D(x, y));

//            int k = coeffs.size();
//            result[cell] +=  coeffs[k-3] + coeffs[k-2] * x + coeffs[k-1] * y;

        }
    }

    return result;
}


//------------------------------------------------------------------------------

void gxKrigingVarianceMapper::onVariogramModelActivated(int type)
{
    switch(type)
    {
    case 0: gxKrigingVarianceCore::setVariogramModel(gxKrigingVarianceCore::Exponential); break;
    case 1: gxKrigingVarianceCore::setVariogramModel(gxKrigingVarianceCore::Gaussian); break;
    case 2: gxKrigingVarianceCore::setVariogramModel(gxKrigingVarianceCore::Spherical); break;
    }
}

void gxKrigingVarianceMapper::onThreshold(QString threshold)
{
    bool ok;
    this->threshold = threshold.toDouble(&ok);
}

void gxKrigingVarianceMapper::onRadius(QString radius)
{
    bool ok;
    this->radius = radius.toDouble(&ok);
}


//------------------------------------------------------------------------------

QWidget *gxKrigingVarianceMapper::getSettingsWidget(QWidget *parent)
{
//    QWidget *settingsWidget = new QWidget(parent);
//    ui->setupUi(settingsWidget);

//    QIntValidator *validator = new QIntValidator();
//    validator->setBottom(0);
//    ui->lineRadius->setValidator(validator);

//    validator = new QIntValidator();
//    validator->setBottom(0);
//    ui->lineThreshold->setValidator(validator);

//    ui->lineRadius->setText(QString::number(defaultRadius));
//    ui->lineThreshold->setText(QString::number(defaultThreshold));

//    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onVariogramModelActivated(int)));
//    connect(ui->lineRadius, SIGNAL(textChanged(QString)), this, SLOT(onRadius(QString)));
//    connect(ui->lineThreshold, SIGNAL(textEdited(QString)), this, SLOT(onThreshold(QString)));

//    return settingsWidget;
    return 0;
}

