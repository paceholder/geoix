#ifndef RBF_MAPPER_H
#define RBF_MAPPER_H

#include "abstract_mapper.h"

#include "math.h"
namespace Ui
{
    class RBFSettingsWidget;
}

typedef double(*RBF)(double r);

static double Quadric(double r) { return r; }
static double Cubic(double r) { return r*r*r; }
static double ThinPlate(double r) { return r ? r*log(r) : 0; }

class gxRBFMapper : public gxAbstractMapper
{
    Q_OBJECT
public:
    gxRBFMapper();
    ~gxRBFMapper();

    bool calcSurface(const double *x, const double *y, const double *z,
                     double minx, double miny,
                     double maxx, double maxy,
                     int nx, int ny,
                     double *result);

    QWidget *getSettingsWidget(QWidget *parent);

public slots:
    void onSplineTypeActivated(int type);
    void onDomainCapacity(QString capacity);
    void onTolerance(int tolerance);

private:
    Ui::RBFSettingsWidget *ui;

    RBF coreFunction;
    int domainCapacity;
    int tolerance;

};

#endif // RBF_MAPPER_H
