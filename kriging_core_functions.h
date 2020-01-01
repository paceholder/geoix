#ifndef KRIGING_CORE_FUNCTIONS_H
#define KRIGING_CORE_FUNCTIONS_H


#include "kriging_params.h"

inline double exponentialFunc(double h, const gxKrigingParams2D &params)
{
    return params.nugget + (params.sill - params.nugget) * (1 - exp(- h / params.rangex));
}


inline double gaussianFunc(double h, const gxKrigingParams2D &params)
{
    return params.nugget + (params.sill - params.nugget) * (1 - exp(-  h * h / ( params.rangex * params.rangex)));
}


inline double sphericalFunc(double h, const gxKrigingParams2D &params)
{
    if (h < params.rangex)
        return params.nugget + (params.sill - params.nugget) * (1.5 * h / params.rangex - 0.5 * (h * h * h)/(params.rangex * params.rangex * params.rangex));
    else
        return params.sill;
}



/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function is called very frequent
typedef double(*VariogramFunction)(double h, const gxKrigingParams2D &params);

#endif // KRIGING_CORE_FUNCTIONS_H
