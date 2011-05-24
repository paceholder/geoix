#ifndef FOURIER_H
#define FOURIER_H

#include "fourier/kiss_fft.h"

#include <QtCore>

typedef kiss_fft_cpx gxComplex;

class gxFourier
{
public:
    static QVector<gxComplex> directFFT(QVector<double> vector);
    static QVector<gxComplex> directFFT(QVector<gxComplex> vector);
    static QVector<gxComplex> inverseFFT(QVector<gxComplex> vector);
private:
    static void expandArrayToPowerOfTwo(QVector<gxComplex> &vector);
};



#endif // FOURIER_H
