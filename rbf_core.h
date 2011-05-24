#ifndef RBF_CORE_H
#define RBF_CORE_H

#include "point3D.h"
#include "math.h"


/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function if called very frequent
typedef double(*RBFFunction)(double r);


/// Wrapper around RBF routines
class gxRBFCore
{
public:
    /// Type of RBF function
    enum RBFFunctionType { Quadric, Cubic, ThinPlate };

    /// Here we set core RBF function
    static void setFunctionType(RBFFunctionType type);

    /// Calculates coeffitients of spline
    static bool calculate(const gxPoint3DVector points, QVector<double> &coeffs);

    /// pointer to the RBF function
    static RBFFunction coreFunction;
};

#endif // RBF_CORE_H
