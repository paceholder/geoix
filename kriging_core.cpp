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


#include "kriging_core.h"

#include "math.h"
#include "matrix.h"


VariogramFunction gxKrigingCore::coreFunction = exponentialFunc;

//------------------------------------------------------------------------------


void gxKrigingCore::setVariogramModel(VariogramModel model)
{
    switch(model)
    {
    case Exponential:
        gxKrigingCore::coreFunction = exponentialFunc;
        break;
    case Gaussian:
        gxKrigingCore::coreFunction = gaussianFunc;
        break;
    case Spherical:
        gxKrigingCore::coreFunction = sphericalFunc;
        break;
    }
}



//------------------------------------------------------------------------------


QVector<double> gxKrigingCore::calculate(const gxPoint3DList points,
                                         const double threshold,
                                         const double radius)
{
    QVector<double> coeffs;
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
        for(int j = 0; j <= i; ++j)
        {
            double d = gxKrigingCore::coreFunction(threshold, radius, points[i].distance2D(points[j]));
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

    return coeffs;
}
