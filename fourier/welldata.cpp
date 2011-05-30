#include "welldata.h"

#include <math.h>
#include <time.h>




double WellData::wellDepth = M_PI * 2;
int WellData::numCoeffs = 3;

double WellData::xRange = 1.0;
double WellData::yRange = 1.0;

WellData::WellData()
{
    for(int i = 0; i < numCoeffs; ++i)
    {
        double n = 5.0 * rand()/(double)RAND_MAX;
        freqCoeffs.append(n);
    }

    X = xRange * rand()/(double)RAND_MAX;
    Y = yRange * rand()/(double)RAND_MAX;
}

double WellData::getValue(double depth)
{
    double result = 1;

    for(int i = 0; i < numCoeffs; ++i)
        result *= sin(freqCoeffs[i] * depth * 2 * M_PI);// / (double)numCoeffs;

    return result;
}


QVector<double> WellData::getValues(int i)
{
    QVector<double> result;
    for(int j = 0; j < i; ++j)
        result.append(getValue(j/(double)i));

    return result;
}