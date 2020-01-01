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



inline double grad_to_rad(double grad)
{
    return ( grad * M_PI ) / 180.0;
}




gxUniversalKriginigCore2D::gxUniversalKriginigCore2D(gxKrigingParams2D &krigingParams)
    : params(krigingParams),
      coreFunction(exponentialFunc),
      transformation(2, 2)
{
    /// creates rotation / scale matrix
    createTransformation2D();

    setVariogramModel();
}


//------------------------------------------------------------------------------


void gxUniversalKriginigCore2D::setVariogramModel()
{
    switch(params.variogramModel)
    {
    case gxKrigingParams2D::Exponential:
        coreFunction = exponentialFunc;
        break;
    case gxKrigingParams2D::Gaussian:
        coreFunction = gaussianFunc;
        break;
    case gxKrigingParams2D::Spherical:
        coreFunction = sphericalFunc;
        break;
    }
}



//------------------------------------------------------------------------------


std::vector<double> gxUniversalKriginigCore2D::calculate(const gxPoint3DList points)
{
    std::vector<double> coeffs;
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
            double d = this->operator()(points[i], points[j]);
            M(i,j) = d;
            M(j,i) = d;
        }

    /// extra cols and rows
    for (int j = 0; j < n; ++j)
    {
        M(n,j) = 1;
        M(n+1,j) = points[j].x();  //
        M(n+2,j) = points[j].y();
        M(j,n) = 1;
        M(j,n+1) = points[j].x();
        M(j,n+2) = points[j].y();
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
        D(i,0) = points[i].z();

    // solving
    R = M.Solve(D); // TODO

    /// fetching coefficients
    coeffs.clear();
    for(int i = 0; i < n + 3; ++i)
        coeffs.push_back(R(i,0));

    return coeffs;
}


//------------------------------------------------------------------------------


double gxUniversalKriginigCore2D::operator()(const double h) const
{
    return coreFunction(h, params);
}


//------------------------------------------------------------------------------


double gxUniversalKriginigCore2D::operator()(const gxPoint3D &p1, const gxPoint3D &p2) const
{
    /// direction vector
    double x, y;
    x = p2.x() - p1.x();
    y = p2.y() - p1.y();


    // matrix transformation (rotation)
    double h = 0.0;
    double d;
    d = x * transformation(0, 0) + y * transformation(1, 0);
    h += d * d;

    d = x * transformation(0, 1) + y * transformation(1, 1);
    h += d * d;

    h = sqrt(h);

    return coreFunction(h, params);
}


//------------------------------------------------------------------------------


void gxUniversalKriginigCore2D::createTransformation2D()
{
    math::matrix<double> scale(2, 2);
    math::matrix<double> rotate_z(2, 2);

    scale(0, 0) = 1.0;
    scale(1, 1) = params.rangex/params.rangey;
//    scale(2, 2) = 1.0;

    double a, b;

    a = cos(grad_to_rad(params.anglez));
    b = sin(grad_to_rad(params.anglez));

    rotate_z(0, 0) = a;
    rotate_z(1, 1) = a;
    rotate_z(0, 1) = b;
    rotate_z(1, 0) = -b;
//    rotate_z(2, 2) = 1;

    transformation = rotate_z * scale;
}
