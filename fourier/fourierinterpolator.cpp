#include "fourierinterpolator.h"

#include "../rbf_core.h"
#include "../fourier.h"


FourierInterpolator::FourierInterpolator(int ns)
    : numSamples(ns)
{

}


void FourierInterpolator::interpolate(QList<WellData> wells)
{
    /// get vectors
    QList<QVector<double> > wellDatas;
    foreach(WellData well, wells)
    {
        QVector<double> values = well.getValues(numSamples);
        wellDatas.append(values);
    }

    QList<QVector<gxComplex> > complexWellDatas;
    // now get fourier coeffs
    foreach(QVector<double> vector, wellDatas)
    {
        complexWellDatas.append(gxFourier::directFFT(vector));
    }

    realCoeffs.clear();
    imgCoeffs.clear();

    // interpolation layer by layer (all freqs)
    for(int i = 0; i < this->numSamples; ++i)
    {
        gxPoint3DVector points;

        // real
        // i-th frequence
        for(int j = 0; j < complexWellDatas.size(); ++j)
            points.append(gxPoint3D(wells[j].X, wells[j].Y, complexWellDatas[j][i].r));

        QVector<double> coeffs;
        gxRBFCore::calculate(points, coeffs); // set of coeffs for each freq
        realCoeffs.append(coeffs);


        //image

        points.clear();

        for(int j = 0; j < complexWellDatas.size(); ++j)
            points.append(gxPoint3D(wells[j].X, wells[j].Y, complexWellDatas[j][i].i));

        coeffs.clear();
        gxRBFCore::calculate(points, coeffs);
        imgCoeffs.append(coeffs);
        // i - number of layer
    }


}

QVector<double> FourierInterpolator::getInterpolatedValue(QList<WellData> wells, double x, double y)
{
    QVector<double> interpolatedReal;
    QVector<double> interpolatedImg;

    interpolatedReal.resize(numSamples);
    interpolatedImg.resize(numSamples);

    interpolatedReal.fill(0);
    interpolatedImg.fill(0);

    for(int i = 0; i < numSamples; ++i) // for every freq
    {
        // interpolation at each level

        // real at first
        double res = 0;
        int l = realCoeffs[i].size();
        for(int j = 0; j < l - 3; ++j)
            res += realCoeffs[i][j] * gxRBFCore::coreFunction(gxPoint3D(wells[j].X, wells[j].Y).distance2D(x, y));

        res += realCoeffs[i][l-3] + realCoeffs[i][l-2] * x + realCoeffs[i][l-1] * y;

        interpolatedReal[i] = res;


        // img then
        // real at first
        res = 0;
        l = imgCoeffs[i].size();
        for(int j = 0; j < l - 3; ++j)
            res += imgCoeffs[j][j] * gxRBFCore::coreFunction(gxPoint3D(wells[j].X, wells[j].Y).distance2D(x, y));

        res += realCoeffs[i][l-3] + realCoeffs[i][l-2] * x + imgCoeffs[i][l-1] * y;

        interpolatedImg[i] = res;
    }

    // here we have interpolated Re and Im arrays at (x,y) point

    QVector<gxComplex> vector;

    for(int i = 0; i < numSamples; ++i)
    {
        vector.append(gxComplex(interpolatedReal[i], interpolatedImg[i]));
    }

    QVector<gxComplex> result = gxFourier::inverseFFT(vector);

    QVector<double> realResult;
    foreach(gxComplex cpx, result)
    {
        realResult.prepend(cpx.r);
    }

    return realResult;
}

