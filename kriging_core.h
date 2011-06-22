//------------------------------------------------------------------------
//    This file is part of Geoix.
//
//    Copyright (C) 2010 Dmitriy Pinaev
//
//    Geoix is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Geoix is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef KRIGING_CORE_H
#define KRIGING_CORE_H

#include "point3D.h"
#include "math.h"
#include "kriging_core_functions.h"

/// I used pointer to the function
/// instead of switch(funtion type) operator
/// to reduce calculation time since
/// this function is called very frequent
typedef double(*VariogramFunction)(double threshold, double radius, double r);


//This class solves Kriging system:
//
//       / K | F \   /b\     /z\                   //
//       | ----- |  |   | = |   |
//       \ F | 0 /   \c/     \0/
//
//      Where   K = gamma_ij - variogram,
//              F = (1, xi, yi),
//              Z = zi,
//              i = 0..N


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
