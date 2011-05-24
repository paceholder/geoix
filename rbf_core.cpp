#include "rbf_core.h"
#include "matrix.h"

static double quadricFunc(double r) { return r; }
static double cubicFunc(double r) { return r*r*r; }
static double thinPlateFunc(double r) { return r ? r*log(r) : 0; }


RBFFunction gxRBFCore::coreFunction = quadricFunc;


/// once we set appropriate function
/// we use it without any extra "switch"
void gxRBFCore::setFunctionType(RBFFunctionType type)
{

    switch(type)
    {
    case Quadric:
        gxRBFCore::coreFunction = quadricFunc;
        break;
    case Cubic:
        gxRBFCore::coreFunction = cubicFunc;
        break;
    case ThinPlate:
        gxRBFCore::coreFunction = thinPlateFunc;
        break;
    }
}



//------------------------------------------------------------------------------



bool gxRBFCore::calculate(const gxPoint3DVector points,
                          QVector<double> &coeffs)
{
    int n = points.size();
    math::matrix<double> M(n+3,n+3), D(n+3,1), R(n+3,1); // matrix and free coefficients

    // Fills each matrix with zeros
    for(int i = 0; i < n + 3; ++i)
    {
        R(i,0) = 0.0;
        D(i,0) = 0.0;

        for(int j = 0; j < n + 3; ++j)
            M(i,j) = 0.0;
    }

    // main matrix
    for(int i = 1; i < n; ++i)
        for(int j = 0; j < i; ++j)
        {
            double d = gxRBFCore::coreFunction(points[i].distance2D(points[j]));
            M(i,j) = d;
            M(j,i) = d;
        }

    /// extra cols and rows
    for (int j = 0; j < n; ++j)
    {
        M(n,j) = 1;
        M(n+1,j) = points[j].x;  //
        M(n+2,j) = points[j].y;
        M(j,n) = 1;
        M(j,n+1) = points[j].x;
        M(j,n+2) = points[j].y;
    }

    // actually not necessary
    for(int i = n; i < n + 3; ++i)
        for (int j = n; j < n + 3; ++j)
            M(i,j) = 0.0;

    /// not necessary
    D(n,0) = 0.0;
    D(n+1,0) = 0.0;
    D(n+2,0) = 0.0;

    /// free column
    for (int i = 0; i < n; ++i)
        D(i,0) = points[i].z;


    // solving
    R = M.Solve(D); // TODO

    /// fetching coefficients
    coeffs.clear();
    for(int i = 0; i < n + 3; ++i)
        coeffs.append(R(i,0));

    return true;

}
