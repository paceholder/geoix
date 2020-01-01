#ifndef FOURIERINTERPOLATOR_H
#define FOURIERINTERPOLATOR_H

#include "welldata.h"

/*!
  Class fulfill interpolation of Fourier coefficients
  and can construct new complex curve from interpolated coeffs.
*/
class FourierInterpolator
{
public:
    /// @param ns - length of FFT array
    FourierInterpolator(int ns = 128);

    /// Transforms each curve and interpolate each group of coeffs separately
    void interpolate(QList<WellData> wells);

    /// Construct new curve at point (x,y) from interpolated coeffs
    QVector<double> getInterpolatedValue(QList<WellData> wells, double x, double y);
private:
    int numSamples;

    QList<QVector<double> > realCoeffs;
    QList<QVector<double> > imgCoeffs;
};

#endif // FOURIERINTERPOLATOR_H
