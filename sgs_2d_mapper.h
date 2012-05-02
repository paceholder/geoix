#ifndef KRIGING_VAR_MAPPER_H
#define KRIGING_VAR_MAPPER_H


#include "abstract_mapper.h"
#include "kriging_params.h"
#include "kriging_var_core.h"

namespace Ui
{
    class KrigingSettingsWidget;
}


/// Sequential Gaussian Simulation 2D
class gxSGS2DMapper : public gxAbstractMapper
{
    Q_OBJECT
public:
    gxSGS2DMapper();
    ~gxSGS2DMapper() {}


    bool calcSurface(const gxPoint3DList points,
                     const gxSize3D size,
                     const int nx, const int ny,
                     std::vector<double> &result);

    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onVariogramModelActivated(int type);
    void onSill(QString sill);
    void onRadius(QString radius);

private:
    Ui::KrigingSettingsWidget *ui;

    gxKrigingParams2D params;

    std::vector<double> fillResultArray(gxPoint3DList &points,
                                    gxOrdinaryKrigingCore2D &krigingCore,
                                    int nx, int ny,
                                    const gxSize3D &size);

};

#endif // KRIGING_VAR_MAPPER_H
