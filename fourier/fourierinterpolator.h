#ifndef FOURIERINTERPOLATOR_H
#define FOURIERINTERPOLATOR_H

#include "welldata.h"
class FourierInterpolator
{
public:
    FourierInterpolator(int ns = 4);

    void interpolate(QList<WellData> wells);

    QVector<double> getInterpolatedValue(QList<WellData> wells, double x, double y);
private:
    int numSamples;

    QList<QVector<double> > realCoeffs;
    QList<QVector<double> > imgCoeffs;
};

#endif // FOURIERINTERPOLATOR_H
