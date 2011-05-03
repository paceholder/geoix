#ifndef RBF_MAPPER_H
#define RBF_MAPPER_H

#include "abstract_mapper.h"

namespace Ui
{
    class RBFSettingsWidget;
}


/// !!!! should do it local member ?
class gxRBFDomain;

class gxRBFMapper : public gxAbstractMapper
{
    Q_OBJECT
public:
    gxRBFMapper();
    ~gxRBFMapper();

    bool calcSurface(const gxPoint3DList points,
                     const gxSize3D size,
                     const int nx, const int ny,
                     QVector<double> &result);

    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onSplineTypeActivated(int type);
    void onDomainCapacity(QString capacity);
    void onTolerance(int tolerance);

private:
    Ui::RBFSettingsWidget *ui;

    int domainCapacity;
    int tolerance;

    QVector<double> fillResultArray(gxRBFDomain &rootDomain,
                                    const int nx, const int ny,
                                    const gxSize3D &size,
                                    QVector<double> lsCoeffs);

};

#endif // RBF_MAPPER_H
