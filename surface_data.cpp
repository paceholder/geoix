#include "surface_data.h"


double gxSurfaceData::getStepX()
{
    if (nx != 0)
        return (size3d.getW()/(double)(nx-1));
    else
        return Gx::BlankDouble;
}

double gxSurfaceData::getStepY()
{
    if (ny != 0)
        return (size3d.getH()/(double)(ny-1));
    else
        return Gx::BlankDouble;
}


void gxSurfaceData::setnXY(int i, int j)
{
    nx = i; ny = j;
    values.resize(nx * ny);
}


void gxSurfaceData::setData(QVector<double> vector)
{
    Q_ASSERT_X(values.size() == vector.size(), "set data to surface data", "size error");

    values = vector;
}
