#include "local_b_spline_mapper.h"

#include "ui_localb_settings_widget.h"

#include "lattice.h"
#include "bspline.h"

const int defaultLevelNumber = 8;


gxLocalBSplineMapper::gxLocalBSplineMapper()
    : gxAbstractMapper(tr("Local B-Spline")),
    ui(new Ui::LocalBSettingsWidget),
    levels(defaultLevelNumber)
{

}

gxLocalBSplineMapper::~gxLocalBSplineMapper()
{
    delete ui;
}


//------------------------------------------------------------------------------

bool gxLocalBSplineMapper::calcSurface(gxPoint3DList points,
                                       gxSize3D size,
                                       int nx, int ny,
                                       std::vector<double> &result)
{
    QScopedPointer<Lattice> latt(new Lattice(size));
    QScopedPointer<Lattice> latt_f(new Lattice(size));

    std::vector<double> lsCoeffs = leastSquare(points);


    for (int l = 0; l < levels; ++l) // it итераций
    {
        // организуем итерацию по контрольным точкам

        // 1.  заполняем сетку коэффициентами B-сплайна
        for (int k = 0; k < points.size(); ++k )
        {

            double s, t; // B-spline аргументы

            // TODO it's should be without recalculation of xi, yi
            // считаем долю интервала между точками сетки 0..1
            s = latt->GetPartX(points[k].x());
            t = latt->GetPartY(points[k].y());

            // номер ячейки в сетке для текущей точки
            int xi, yi;
            xi = latt->GetIndexX(points[k].x()) - 1;
            yi = latt->GetIndexY(points[k].y()) - 1;

            // надо предусмотрет выход xi, yi за границы
            if (xi > latt->step) { --xi; s = 1;}
            if (yi > latt->step) { --yi; t = 1;}

            if (xi < 0) { xi = 0; s = 0;}
            if (yi < 0) { yi = 0; t = 0;}

//            size = step + 3
//            last elem = step + 2


            double w_s = Summ_w_ab(s, t); // normalizing multiplier

            // заполняем узлы сетки значениями вокруг данной точки
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                {
                    int m = xi + i;
                    int n = yi + j;

                    double w_ab = W_ab(i, j, s, t);
//                    try
//                    {
                        latt->cgrid[m][n].delta += w_ab * w_ab * w_ab * points[k].z() / w_s;
                        latt->cgrid[m][n].w += w_ab * w_ab;
//                    }
//                    catch(...)
//                    {
//                        int i = 0;
//                    }
                }

        } // for k


        // теперь считаем значения сетки
        double w, delta;
        for (int i = 0; i < latt->cgrid.size(); ++i)
            for (int j = 0; j < latt->cgrid[i].size(); ++j)
            {
                w = latt->cgrid[i][j].w;
                delta = latt->cgrid[i][j].delta;
                if (w !=0)
                    latt->cgrid[i][j].value = delta/w;
            }

        // 2. считаем P = P - F(Ф)
        for(int i = 0; i < points.size(); ++i)
        {
            points[i].z() -= latt->GetZ(points[i].x(), points[i].y());
        }

        // 3. считаем fi' = fi' + Ф
        // где fi' - сетка для перемасштабирования
        latt_f->Add(latt.data());

        // Для послденей итерации перемасштабирование делать не надо
        if (l != levels - 1) // на 11 вываливается
        {
            //4. Перемасштабирование. Количество узлов по х и по у вырос вдвое
            latt_f->Refine();

            // 5. Меняем размер сетки, для записи новых коэффициентов
            latt->Rescale();
        }

    } //for l

    result = fillResultArray(latt_f.data(), nx, ny, size, lsCoeffs);

    return true;
}


//------------------------------------------------------------------------------



std::vector<double> gxLocalBSplineMapper::fillResultArray(const Lattice* lattice,
                                                      const int nx, const int ny,
                                                      const gxSize3D &size,
                                                      std::vector<double> lsCoeffs)
{
    std::vector<double> result(nx * ny);

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
            int cell = j * nx + i;

            result[cell] = lattice->GetZ(x, y);
            result[cell] += lsCoeffs[0] * x + lsCoeffs[1] * y + lsCoeffs[2];
        }
    }

    return result;
}


//------------------------------------------------------------------------------

QWidget *gxLocalBSplineMapper::getSettingsWidget(QWidget *parent)
{
    QWidget *settingsWidget = new QWidget(parent);
    ui->setupUi(settingsWidget);

    QIntValidator *validator = new QIntValidator();
    validator->setBottom(1);
    ui->lineLevels->setValidator(validator);

    ui->lineLevels->setText(QString::number(defaultLevelNumber));

    connect(ui->lineLevels, SIGNAL(textChanged(QString)), this, SLOT(onSplineLevels(QString)));

    return settingsWidget;
}

void gxLocalBSplineMapper::onSplineLevels(QString slevels)
{
    bool ok;
    this->levels = slevels.toInt(&ok);
}
