#ifndef KRIGING_VAR_CORE_H
#define KRIGING_VAR_CORE_H

#include "point_nd.h"
#include "math.h"
#include "matrix.h"
#include "kriging_core_functions.h"

/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function is called very frequent
//typedef double(*VariogramFunction)(double h, gxKrigingParams2D &params);


//This class solves Kriging system for point (X, Y):
//
//       / K | 1 \   /l\     /k\       //
//       | ----- |  |   | = |   |
//       \ 1 | 0 /   \m/     \1/
//
//      Where   K = gamma_ij - variogram,
//              i = 0..N
//              m - Lagrange coefficient
//
//              interpolation: summ(l_i * Z_i) + m_i * 1
//              variance:


class gxOrdinaryKrigingCore2D
{
public:
    /// constructor
    gxOrdinaryKrigingCore2D(gxKrigingParams2D &krigingParams);


    /// Type of RBF function
    enum VariogramModel { Exponential, Gaussian, Spherical};

    /// Here we set core RBF function
    void setVariogramModel();

    /// Calculates coeffitients of spline
    QVector<double> calculate(const gxPoint3DList points,
                              const double X,
                              const double Y);

    /// calculates variance at given point
    double variance(const gxPoint3DList points,
                    const QVector<double> coeffs,
                    const double X,
                    const double Y);

    double value(const gxPoint3DList points,
                        const QVector<double> coeffs);

    double operator()(const double h) const;
    double operator()(const gxPoint3D &p1, const gxPoint3D &p2) const;

private:
    /// pointer to the RBF function
    VariogramFunction coreFunction;

    gxKrigingParams2D params;

    math::matrix<double> transformation;

    void createTransformation2D();
};

#endif // KRIGING_VAR_CORE_H
