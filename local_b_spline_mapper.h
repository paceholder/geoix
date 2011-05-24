#ifndef LOCAL_B_SPLINE_MAPPER_H
#define LOCAL_B_SPLINE_MAPPER_H

#include "abstract_mapper.h"

namespace Ui
{
    class LocalBSettingsWidget;
}


class Lattice;

class gxLocalBSplineMapper : public gxAbstractMapper
{
    Q_OBJECT
public:
    gxLocalBSplineMapper();
    ~gxLocalBSplineMapper();

    bool calcSurface(gxPoint3DList points,
                     gxSize3D size,
                     int nx, int ny,
                     QVector<double> &result);


    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onSplineLevels(QString slevels);

private:
    Ui::LocalBSettingsWidget *ui;

    int levels;

    QVector<double> fillResultArray(const Lattice* lattice,
                                    const int nx, const int ny,
                                    const gxSize3D &size,
                                    QVector<double> lsCoeffs);
};

#endif // LOCAL_B_SPLINE_MAPPER_H
