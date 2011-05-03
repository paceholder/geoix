#include "abstract_mapper.h"

#include "constants.h"

void gxAbstractMapper::removeEqualPoints(gxPoint3DList &points)
{
    qSort(points.begin(), points.end(), gxPoint3D::pointXLessThan);

    gxPoint3DList newPointList;

    while (points.size())
    {
        gxPoint3DList toBeAveraged;

        // take fist
        gxPoint3D point = points.takeFirst();

        // put in temporal array
        toBeAveraged.append(point);

        // looking for duplicate
        while (points.size()
            && fabs(points.first().y - point.y) < Gx::Eps)
        {
            toBeAveraged.append(points.takeFirst());
        }

        newPointList.append(average(toBeAveraged));
    }

    points = newPointList;
}



gxPoint3D gxAbstractMapper::average(gxPoint3DList &toBeAveraged)
{
    gxPoint3D averaged;
    QListIterator<gxPoint3D> it(toBeAveraged);
    while(it.hasNext())
    {
        gxPoint3D point = it.next();
        averaged += point;
    }

    averaged.x /= double(toBeAveraged.size());
    averaged.y /= double(toBeAveraged.size());
    averaged.z /= double(toBeAveraged.size());

    return averaged;
}




QVector<double> gxAbstractMapper::leastSquare(gxPoint3DList &points)
{
    math::matrix<double> M(3,3);
    math::matrix<double> D(3,1);
    math::matrix<double> abc(3,1);

    for(int i = 0; i<3; ++i)
    {
        M(i,0) = 0.0;
        abc(i,0) = 0.0;
        D(i,0) = 0.0;
        for(int j=0; j<3; ++j)
        {
            M(i,j) =0.0;
        }
    }


    for(int i = 0; i < points.size(); ++i)
    {
        double X,Y,Z;
        X = points[i].x;
        Y = points[i].y;
        Z = points[i].z;

        M(0,0) += X*X;
        M(0,1) += X*Y;
        M(1,1) += Y*Y;
        M(0,2) += X;
        M(1,2) += Y;
        D(0,0) += X*Z;
        D(1,0) += Y*Z;
        D(2,0) += Z;
    }
    M(2,1) = M(1,2);
    M(2,0) = M(0,2);
    M(1,0) = M(0,1);
    M(2,2) = points.size();

    abc = M.Solve(D);

    double A = abc(0,0), B = abc(1,0), C = abc(2,0);
    for(int i = 0; i < points.size(); ++i)
    {
        points[i].z -=  A * points[i].x + B * points[i].y + C;
    }

    QVector<double> result;
    result << A << B << C;
    return result;
}
