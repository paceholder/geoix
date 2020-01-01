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


#include "kriging_var_core.h"

#include "math.h"
#include "matrix.h"


inline double grad_to_rad(double grad)
{
    return ( grad * M_PI ) / 180.0;
}



gxOrdinaryKrigingCore2D::gxOrdinaryKrigingCore2D(gxKrigingParams2D &krigingParams)
    : coreFunction(exponentialFunc)
    , params(krigingParams)
{
    createTransformation2D();

    setVariogramModel();
}

//------------------------------------------------------------------------------


void gxOrdinaryKrigingCore2D::setVariogramModel()
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


QVector<double> gxOrdinaryKrigingCore2D::calculate(const gxPoint3DList points,
                                                   const double X,
                                                   const double Y)
{
    QVector<double> coeffs;
    int n = points.size();

    const int K = 1; // additional rows and cols in matrix

    math::matrix<double> M(n + K, n + K), D(n + K, 1), R(n + K, 1); // matrix and free coefficients

    // Fills each matrix with zeros
    for(int i = 0; i < n + K; ++i)
    {
        R(i,0) = 0.0;
        D(i,0) = 0.0;

        for(int j = 0; j < n + K; ++j)
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
//        M(n+1,j) = points[j].x;  //
//        M(n+2,j) = points[j].y;
        M(j,n) = 1;
//        M(j,n+1) = points[j].x;
//        M(j,n+2) = points[j].y;
    }

    /// free column
    for (int i = 0; i < n; ++i)
        D(i,0) = this->operator()(points[i], gxPoint3D(X, Y));


    /// last 3 coeffs
    D(n,0) = 1;
//    D(n+1,0) = X;
//    D(n+2,0) = Y;

    // solving
    R = M.Solve(D);

    /// fetching coefficients
    coeffs.clear();
    for(int i = 0; i < n + K; ++i)
        coeffs.append(R(i,0));

    return coeffs;
}



//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore2D::variance(const gxPoint3DList points,
                                         const QVector<double> coeffs,
                                         const double X,
                                         const double Y)
{
    double result = 0.0;
    const int n = points.size();
    for(int i = 0; i < n; ++i)
        result += coeffs[i] * this->operator ()(points[i], gxPoint3D(X, Y));

    result += coeffs[n]; // + coeffs[n + 1] * X + coeffs[n + 2] * Y;

    return result;
}


//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore2D::value(const gxPoint3DList points,
                                const QVector<double> coeffs)
{
    double result = 0.0;

    for(int i = 0; i < points.size(); ++i)
        result += coeffs[i] * points[i].z();

    return result;
}

//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore2D::operator()(const double h) const
{
    return coreFunction(h, params);
}


//------------------------------------------------------------------------------


double gxOrdinaryKrigingCore2D::operator()(const gxPoint3D &p1, const gxPoint3D &p2) const
{
    /// direction vector
    double x, y;
    x = p2.x() - p1.x();
    y = p2.y() - p1.y();


    // matrix transformation (rotation)
    double h = 0.0;
    for (int i = 0; i < 2; ++i)
    {
        double d;
        d = x * transformation(1, 1) + y * transformation(2, 1);
        h += d * d;

        d = x * transformation(1, 2) + y * transformation(2, 2);
        h += d * d;
    }


    return coreFunction(sqrt(h), params);
}





//------------------------------------------------------------------------------


void gxOrdinaryKrigingCore2D::createTransformation2D()
{
    math::matrix<double> scale(3, 3);
    math::matrix<double> rotate_z(3, 3);

    scale(0, 0) = 1.0;
    scale(1, 1) = params.rangex/params.rangey;
    scale(2, 2) = 1.0;

    rotate_z(1, 1) = cos(grad_to_rad(params.anglez));
    rotate_z(2, 2) = cos(grad_to_rad(params.anglez));
    rotate_z(1, 2) = sin(grad_to_rad(params.anglez));
    rotate_z(2, 1) = -sin(grad_to_rad(params.anglez));
    rotate_z(3, 3) = 1;

    transformation = /*scale **/ rotate_z;
}
