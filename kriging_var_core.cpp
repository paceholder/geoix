#include "kriging_var_core.h"

#include "math.h"
#include "matrix.h"


VariogramFunction gxOrdinaryKrigingCore::coreFunction = exponentialFunc;

//------------------------------------------------------------------------------


void gxOrdinaryKrigingCore::setVariogramModel(VariogramModel model)
{
    switch(model)
    {
    case Exponential:
        gxOrdinaryKrigingCore::coreFunction = exponentialFunc;
        break;
    case Gaussian:
        gxOrdinaryKrigingCore::coreFunction = gaussianFunc;
        break;
    case Spherical:
        gxOrdinaryKrigingCore::coreFunction = sphericalFunc;
        break;
    }
}



//------------------------------------------------------------------------------


QVector<double> gxOrdinaryKrigingCore::calculate(const gxPoint3DList points,
                                                 const double threshold,
                                                 const double radius,
                                                 const double X,
                                                 const double Y)
{
    QVector<double> coeffs;
    int n = points.size();

    const int K = 1; // additional rows and cols in matrix

    math::matrix<double> M(n + K, n + K), D(n + K, 1), R(n + K, 1); // matrix and free coefficients

    // Fills each matrix with zeros
    for(int i = 0; i < n + K; ++i)
    {
        R(i,0) = 0.0;
        D(i,0) = 0.0;

        for(int j = 0; j < n + K; ++j)
            M(i,j) = 0.0;
    }

    // main matrix
    for(int i = 1; i < n; ++i)
        for(int j = 0; j <= i; ++j)
        {
            double d = gxOrdinaryKrigingCore::coreFunction(threshold,
                                                           radius,
                                                           points[i].distance2D(points[j]));
            M(i,j) = d;
            M(j,i) = d;
        }

    /// extra cols and rows
    for (int j = 0; j < n; ++j)
    {
        M(n,j) = 1;
//        M(n+1,j) = points[j].x;  //
//        M(n+2,j) = points[j].y;
        M(j,n) = 1;
//        M(j,n+1) = points[j].x;
//        M(j,n+2) = points[j].y;
    }

    /// free column
    for (int i = 0; i < n; ++i)
        D(i,0) = gxOrdinaryKrigingCore::coreFunction(threshold,
                                                     radius,
                                                     points[i].distance2D(X, Y));


    /// last 3 coeffs
    D(n,0) = 1;
//    D(n+1,0) = X;
//    D(n+2,0) = Y;

    // solving
    R = M.Solve(D);

    /// fetching coefficients
    coeffs.clear();
    for(int i = 0; i < n + K; ++i)
        coeffs.append(R(i,0));

    return coeffs;
}



//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore::variance(const gxPoint3DList points,
                                       const QVector<double> coeffs,
                                       const double threshold,
                                       const double radius,
                                       const double X,
                                       const double Y)
{
    double result = 0.0;
    const int n = points.size();
    for(int i = 0; i < n; ++i)
        result += coeffs[i] * gxOrdinaryKrigingCore::coreFunction(threshold,
                                                                  radius,
                                                                  points[i].distance2D(X, Y));

    result += coeffs[n]; // + coeffs[n + 1] * X + coeffs[n + 2] * Y;

    return result;
}


//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore::value(const gxPoint3DList points,
                                    const QVector<double> coeffs)
{
    double result = 0.0;

    for(int i = 0; i < points.size(); ++i)
        result += coeffs[i] * points[i].z;

    return result;
}

