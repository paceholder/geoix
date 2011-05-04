#include <math.h>
#include "bspline.h"

/// \file Содержит описание четырех базовых функций B-сплайна



double B0(double t)
{ return pow(1-t,3)/6; }

double B1(double t)
{ return (3*pow(t,3) - 6*pow(t,2) + 4)/6; }

double B2(double t)
{ return (-3*pow(t,3) + 3*pow(t,2) + 3*t +1)/6; }

double B3(double t)
{ return pow(t,3)/6; }


B Bfunct[4] = {B0, B1, B2, B3};
