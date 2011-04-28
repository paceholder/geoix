#ifndef ABSTRACT_MAPPER_H
#define ABSTRACT_MAPPER_H

#include <QtCore>

#include "point3D.h"
#include "size.h"
#include "matrix.h"

class gxAbstractMapper : public QObject
{
    Q_OBJECT
public:
    gxAbstractMapper(QString splineName)
        : name(splineName)
    {}
    /// abstract function which is reimplemented in
    /// subclasses
    virtual bool calcSurface(const gxPoint3DList points,
                             const gxSize3D size,
                             const int nx, const int ny,
                             QVector<double> &result) = 0;

    QString getName() { return name; }

    /// returns widget which is embedded in
    /// mapping window
    virtual QWidget *getSettingsWidget(QWidget *parent = 0) = 0;
protected:
    QString name;

//    void removeEqualPoints(gxPoint3DList &points);
//    void leastSquare(gxPoint3DList &points);

    void removeEqualPoints(gxPoint3DList &points)
    {
        qSort(points.begin(), points.end(), gxPoint3D::pointXLessThan);
        int i = points.size() - 1; // last point

        // look over all points
        while (i > 0)
        {
            // here we collect points with equall x and y
            int j = i;
            double average = 0;
            while (qAbs(points[i].x - points[j].x) < Gx::Eps &&
                   qAbs(points[i].y - points[j].y) < Gx::Eps && j >= 0)
            {
                average += points[j].z;
                --j;
            }

            // if number of equall points is N > 0
            if (i - j > 0)
            {
                // remove N - 1 ponts from the end
                points.erase(points.begin() + j + 1, points.end());
                // and replace Nth point from the end with average z-value
                points[j].z = average / double(i - j);
                i = j - 1;
            }
            else --i;
        }

    }


    void leastSquare(gxPoint3DList &points)
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
    }

};


#endif // ABSTRACT_MAPPER_H
