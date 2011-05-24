#include "curve.h"

#include <limits>

gxCurve::gxCurve()
{


}


//------------------------------------------------------------------------------


void gxCurve::getRange(double &min, double max)
{
    if (values.size() == 0)
    {
        min = Gx::BlankDouble;
        max = Gx::BlankDouble;
    }

    double m = std::numeric_limits<double>::max();
    min = +m;
    max = -m;

    QVectorIterator<QPair<double, double> > it(values);
    while(it.hasNext())
    {
        double value = it.next().second;
        if (value == Gx::BlankDouble) continue;

        if (value < min) min = value;
        if (value > max) max = value;
    }
}


//------------------------------------------------------------------------------


void gxCurve::trimBlankValues(QVector<QPair<double, double> > &vec)
{
    QMutableVectorIterator<QPair<double, double> > it(vec);
    while(it.hasNext())
    {
        if (it.next().second == Gx::BlankDouble)
            it.remove();
        else
            break;
    }

    it.toBack();


    while(it.hasPrevious())
    {
        if (it.previous().second == Gx::BlankDouble)
            it.remove();
        else
            break;
    }
}
