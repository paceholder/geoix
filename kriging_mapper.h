#ifndef KRIGING_MAPPER_H
#define KRIGING_MAPPER_H


#include "abstract_mapper.h"
#include "kriging_params.h"
#include "kriging_core.h"

namespace Ui
{
    class KrigingSettingsWidget;
}

class gxKrigingMapper : public gxAbstractMapper
{
    Q_OBJECT
public:
    gxKrigingMapper();
    ~gxKrigingMapper() {}


    bool calcSurface(const gxPoint3DList points,
                     const gxSize3D size,
                     const int nx, const int ny,
                     std::vector<double> &result);

    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onVariogramModelActivated(int type);
    void onSill(QString sill);
    void onNugget(QString nugget);
    void onRadiusA(QString radius);
    void onRadiusB(QString radius);
    void onRotationAngle(QString angle);

private:
    Ui::KrigingSettingsWidget *ui;

    gxKrigingParams2D params;

    std::vector<double> fillResultArray(std::vector<double> &coeffs,
                                    gxPoint3DList &points,
                                    gxUniversalKriginigCore2D &krigingCore,
                                    int nx, int ny,
                                    const gxSize3D &size);

};

#endif // KRIGING_MAPPER_H
