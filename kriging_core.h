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

#include "point_nd.h"
#include "math.h"
#include "matrix.h"
#include "kriging_core_functions.h"
#include "kriging_params.h"


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
class gxUniversalKriginigCore2D
{
public:
    gxUniversalKriginigCore2D(gxKrigingParams2D &krigingParams);


    /// Calculates coeffitients of spline
    std::vector<double> calculate(const gxPoint3DList points);

    double operator()(const double h) const;
    double operator()(const gxPoint3D &p1, const gxPoint3D &p2) const;

private:
    /// kriging parameters
    gxKrigingParams2D params;

    /// pointer to the RBF function
    VariogramFunction coreFunction;

    math::matrix<double> transformation;

    /// Here we set core RBF function
    void setVariogramModel();

    void createTransformation2D();
};

#endif // KRIGING_CORE_H
