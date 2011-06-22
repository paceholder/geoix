#include "surface_data.h"


double gxSurfaceData::getStepX() const
{
    if (nx != 0)
        return (size3d.getW()/(double)(nx-1));
    else
        return Gx::BlankDouble;
}


//------------------------------------------------------------------------------

double gxSurfaceData::getStepY() const
{
    if (ny != 0)
        return (size3d.getH()/(double)(ny-1));
    else
        return Gx::BlankDouble;
}


//------------------------------------------------------------------------------


void gxSurfaceData::setnXY(int i, int j)
{
    nx = i; ny = j;
    values.resize(nx * ny);
}


//------------------------------------------------------------------------------

void gxSurfaceData::setData(QVector<double> vector)
{
    Q_ASSERT_X(values.size() == vector.size(), "set data to surface data", "size error");

    values = vector;
}


//------------------------------------------------------------------------------


double gxSurfaceData::at(const double x, const double y) const
{
    if (!size3d.inRange(x, y)) return nullValue;

    int intx = floor((x - size3d.getMinX())/ getStepX());
    int inty = floor((y - size3d.getMinY())/ getStepY());

    Q_ASSERT_X(intx >=0, "at", "range violation");
    Q_ASSERT_X(inty >=0, "at", "range violation");

    double fracx = (x - size3d.getMinX()) / getStepX() - intx;
    double fracy = (y - size3d.getMinY()) / getStepY() - inty;

    if (intx == nx - 1) { --intx; fracx = 1; }
    if (inty == ny - 1) { --inty; fracy = 1; }

    double d1 = at(intx, inty);
    double d2 = at(intx + 1, inty);
    double d3 = at(intx + 1, inty + 1);
    double d4 = at(intx, inty + 1);

    if (at(intx, inty) == nullValue
        || at(intx + 1, inty) == nullValue
        || at(intx + 1, inty + 1) == nullValue
        || at(intx, inty + 1) == nullValue)
    return nullValue;

    double d5 = d1 + (d2 - d1) * fracx;
    double d6 = d4 + (d3 - d4) * fracx;

    return d5 + (d6 - d5) * fracy;

}


//------------------------------------------------------------------------------


void gxSurfaceData::setNormal(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double x, y, z, l;

    x =   y1 * z2 - y2 * z1;
    y = - x1 * z2 + x2 * z1;
    z =   x1 * y2 - x2 * y1;

    l = sqrt(x*x + y*y + z*z);

    x /= l;
    y /= l;
    z /= l;

    glNormal3d(x, y, z);
}
