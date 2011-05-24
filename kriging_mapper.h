#ifndef KRIGING_MAPPER_H
#define KRIGING_MAPPER_H


#include "abstract_mapper.h"

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
                     QVector<double> &result);

    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onVariogramModelActivated(int type);
    void onThreshold(QString threshold);
    void onRadius(QString radius);

private:
    Ui::KrigingSettingsWidget *ui;

    /// threshold value of variogram
    double threshold;

    /// radius of variogram
    double radius;

    QVector<double> fillResultArray(QVector<double> &coeffs,
                                    gxPoint3DList &points,
                                    int nx, int ny,
                                    const gxSize3D &size);

};

#endif // KRIGING_MAPPER_H
