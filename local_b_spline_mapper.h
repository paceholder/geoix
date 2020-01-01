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
                     std::vector<double> &result);


    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onSplineLevels(QString slevels);

private:
    Ui::LocalBSettingsWidget *ui;

    int levels;

    std::vector<double> fillResultArray(const Lattice* lattice,
                                    const int nx, const int ny,
                                    const gxSize3D &size,
                                    std::vector<double> lsCoeffs);
};

#endif // LOCAL_B_SPLINE_MAPPER_H
