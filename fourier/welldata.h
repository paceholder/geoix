#ifndef WELLDATA_H
#define WELLDATA_H

#include <QtCore>

class WellData
{
public:
    WellData();

    double X;
    double Y;

    static double xRange;
    static double yRange;

    double getValue(double depth);

    QVector<double> getValues(int i);
private:
    static double wellDepth; // = 2 * Pi
    static int numCoeffs;

    QVector<double> freqCoeffs;


};

#endif // WELLDATA_H
