#ifndef KRIGING_CORE_FUNCTIONS_H
#define KRIGING_CORE_FUNCTIONS_H

inline double exponentialFunc(double threshold, double radius, double r)
{
    return threshold * (1 - exp(- r / radius));
}
inline double gaussianFunc(double threshold, double radius, double r)
{
    return threshold* (1 - exp(-  r*r/(radius*radius)));
}
inline double sphericalFunc(double threshold, double radius, double r)
{
    if (r < radius)
        return threshold * (1.5 * r/radius - 0.5 * (r*r*r)/(radius*radius*radius));
    else
        return threshold;
}


#endif // KRIGING_CORE_FUNCTIONS_H
