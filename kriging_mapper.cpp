#include "kriging_mapper.h"

#include "ui_kriging_settings_widget.h"
#include "kriging_core.h"


const double defaultSill = 100;
const double defaultNugget = 0;
const double defaultRadius = 100;
const double defaultRotationAngle = 0;
const gxKrigingParams2D::VariogramModel defaultVariogramModel = gxKrigingParams2D::Exponential;


gxKrigingMapper::gxKrigingMapper()
    : gxAbstractMapper(tr("Kriging")),
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

bool gxKrigingMapper::calcSurface(gxPoint3DList points,
                                  const gxSize3D size,
                                  const int nx, const int ny,
                                  std::vector<double> &result)
{
    // first of all we should delete points
    // with equal x and y coords.
    removeEqualPoints(points);

//    least square method
//    leastSquare(points);


    gxUniversalKriginigCore2D krigingCore(params);
    std::vector<double> coeffs = krigingCore.calculate(points);

    result = fillResultArray(coeffs, points, krigingCore, nx, ny, size);

    return true;
}

//------------------------------------------------------------------------------


std::vector<double> gxKrigingMapper::fillResultArray(std::vector<double>  &coeffs,
                                                 gxPoint3DList &points,
                                                 gxUniversalKriginigCore2D &krigingCore,
                                                 int nx, int ny,
                                                 const gxSize3D &size)
{
    std::vector<double> result(nx * ny);
    std::fill(result.begin(), result.end(), 0.0);

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

            int cell =  j * nx + i;
            result[cell] = 0;

            for(int k = 0; k < coeffs.size() - 3; ++k)
                result[cell] += coeffs[k] * krigingCore(points[k], gxPoint3D(x, y));

            int k = coeffs.size();
            result[cell] +=  coeffs[k-3] + coeffs[k-2] * x + coeffs[k-1] * y;

        }
    }

    return result;
}


//------------------------------------------------------------------------------

void gxKrigingMapper::onVariogramModelActivated(int type)
{
    switch(type)
    {
    case 0: params.variogramModel = gxKrigingParams2D::Exponential; break;
    case 1: params.variogramModel = gxKrigingParams2D::Gaussian; break;
    case 2: params.variogramModel = gxKrigingParams2D::Spherical; break;
    }
}

void gxKrigingMapper::onSill(QString sill)
{
    bool ok;
    params.sill = sill.toDouble(&ok);
}

void gxKrigingMapper::onNugget(QString nugget)
{
    bool ok;
    params.nugget = nugget.toDouble(&ok);
}

void gxKrigingMapper::onRadiusA(QString radius)
{
    bool ok;
    params.rangex = radius.toDouble(&ok);
}

void gxKrigingMapper::onRadiusB(QString radius)
{
    bool ok;
    params.rangey = radius.toDouble(&ok);
}


void gxKrigingMapper::onRotationAngle(QString angle)
{
    bool ok;
    params.anglez = angle.toDouble(&ok);
}


//------------------------------------------------------------------------------

QWidget *gxKrigingMapper::getSettingsWidget(QWidget *parent)
{
    QWidget *settingsWidget = new QWidget(parent);
    ui->setupUi(settingsWidget);

    QIntValidator *intValidator1 = new QIntValidator();
    intValidator1->setBottom(0);
    ui->lineRadiusA->setValidator(intValidator1);

    QIntValidator *intValidator2 = new QIntValidator();
    intValidator2->setBottom(0);
    ui->lineRadiusB->setValidator(intValidator2);

    QIntValidator *validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineSill->setValidator(validator);

    validator = new QIntValidator();
    validator->setBottom(0);
    ui->lineNugget->setValidator(validator);

    ui->lineRadiusA->setText(QString::number(defaultRadius));
    ui->lineRadiusB->setText(QString::number(defaultRadius));
    ui->lineSill->setText(QString::number(defaultSill));
    ui->lineNugget->setText(QString::number(defaultNugget));
    ui->lineRotationAngle->setText(QString::number(defaultRotationAngle));

    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onVariogramModelActivated(int)));
    connect(ui->lineRadiusA, SIGNAL(textChanged(QString)), this, SLOT(onRadiusA(QString)));
    connect(ui->lineRadiusB, SIGNAL(textChanged(QString)), this, SLOT(onRadiusB(QString)));
    connect(ui->lineSill, SIGNAL(textEdited(QString)), this, SLOT(onSill(QString)));
    connect(ui->lineNugget, SIGNAL(textEdited(QString)), this, SLOT(onNugget(QString)));
    connect(ui->lineRotationAngle, SIGNAL(textEdited(QString)), this, SLOT(onRotationAngle(QString)));

    return settingsWidget;
}
