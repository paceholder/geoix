#ifndef KRIGING_CORE_H
#define KRIGING_CORE_H

#include "point3D.h"
#include "math.h"


/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function is called very frequent
typedef double(*VariogramFunction)(double threshold, double radius, double r);


/// Wrapper around RBF routines
class gxKrigingCore
{
public:
    /// Type of RBF function
    enum VariogramModel { Exponential, Gaussian, Spherical};

    /// Here we set core RBF function
    static void setVariogramModel(VariogramModel model);

    /// Calculates coeffitients of spline
    static QVector<double> calculate(const gxPoint3DList points,
                                     const double threshold,
                                     const double radius);

    /// pointer to the RBF function
    static VariogramFunction coreFunction;
};

#endif // KRIGING_CORE_H
