#include "fourier.h"

QVector<gxComplex> gxFourier::directFFT(QVector<double> vector)
{
    QVector<gxComplex> vec;
    foreach(double val, vector)
    {
        vec.append(gxComplex(val));
    }

    return directFFT(vec);
}


QVector<gxComplex> gxFourier::directFFT(QVector<gxComplex> vector)
{
    expandArrayToPowerOfTwo(vector);

    kiss_fft_cfg cfg = kiss_fft_alloc(vector.size(), 0, 0, 0);

    kiss_fft_cpx *in = new kiss_fft_cpx[vector.size()];
    kiss_fft_cpx *out = new kiss_fft_cpx[vector.size()];

    for(int i = 0; i < vector.size(); ++i)
        in[i] = vector[i];

    kiss_fft(cfg, in, out);

    QVector<gxComplex> result;

    result.resize(vector.size());
    for(int i = 0; i < vector.size(); ++i)
        result[i]  = out[i];

    delete [] in;
    delete [] out;

    return result;
}


//------------------------------------------------------------------------------


QVector<gxComplex> gxFourier::inverseFFT(QVector<gxComplex> vector)
{
    expandArrayToPowerOfTwo(vector);

    kiss_fft_cfg cfg = kiss_fft_alloc(vector.size(), 1, 0, 0);

    kiss_fft_cpx *in = new kiss_fft_cpx[vector.size()];
    kiss_fft_cpx *out = new kiss_fft_cpx[vector.size()];

    for(int i = 0; i < vector.size(); ++i)
        in[i] = vector[i];

    kiss_fft(cfg, in, out);

    QVector<gxComplex> result;

    result.resize(vector.size());
    for(int i = 0; i < vector.size(); ++i)
        result[i] = out[i];

    delete [] in;
    delete [] out;


    return result;
}


//------------------------------------------------------------------------------


void gxFourier::expandArrayToPowerOfTwo(QVector<gxComplex> &vector)
{
    int n = vector.size();

    int p = 0;
    while (n > 2)
    {
        n /= 2;
        ++p;
    }

    vector.resize(2 << p);
}
