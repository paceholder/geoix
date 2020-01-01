#ifndef CURVE_H
#define CURVE_H

#include <QtCore>

#include "constants.h"

/// Just for now this class will support curves with arbitrary step
class gxCurve
{
public:
    gxCurve();

    void setData(QVector<QPair<double, double> > newValues)
    {
        trimBlankValues(newValues);
        values = newValues;

        if (values.size() > 0)
        {
            top = values.front().first;
            bottom = values.back().first;
        }
    }

    void getRange(double &min, double max);

private:
    double top;
    double bottom;

    /// pairs depth - value
    QVector<QPair<double, double> > values;

    void trimBlankValues(QVector<QPair<double, double> > &vec);
};

#endif // CURVE_H
