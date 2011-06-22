#ifndef KRIGING_VAR_CORE_H
#define KRIGING_VAR_CORE_H

#include "point3D.h"
#include "math.h"

#include "kriging_core_functions.h"

/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function is called very frequent
typedef double(*VariogramFunction)(double threshold, double radius, double r);


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


class gxOrdinaryKrigingCore
{
public:
    /// Type of RBF function
    enum VariogramModel { Exponential, Gaussian, Spherical};

    /// Here we set core RBF function
    static void setVariogramModel(VariogramModel model);

    /// Calculates coeffitients of spline
    static QVector<double> calculate(const gxPoint3DList points,
                                     const double threshold,
                                     const double radius,
                                     const double X,
                                     const double Y);

    /// calculates variance at given point
    static double variance(const gxPoint3DList points,
                           const QVector<double> coeffs,
                           const double threshold,
                           const double radius,
                           const double X,
                           const double Y);

    static double value(const gxPoint3DList points,
                        const QVector<double> coeffs);

    /// pointer to the RBF function
    static VariogramFunction coreFunction;
};

#endif // KRIGING_VAR_CORE_H
