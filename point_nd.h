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


#ifndef POINT3D_H
#define POINT3D_H

#include <QVector>

/// Template n-dimensional Point class
/*!
  Class describes multidimensional point with arbitrary number of dimentions.

*/
template <int Dimension>
struct gxPoint
{
    double coords[Dimension];

    gxPoint(const double *data);

    gxPoint(QVector<double> vector);

    gxPoint(double x = 0, double y = 0, double z = 0);

    gxPoint<Dimension>& operator=(const gxPoint<Dimension> &p);

    bool operator==(const gxPoint<Dimension> &p);

    gxPoint<Dimension> &operator+=(gxPoint<Dimension> &p);

    double distance2D(const gxPoint<Dimension> &p) const;

    double distance2D(const double x, const double y) const;

    const double* data() const { return coords; }

    /// Comparison of x coordinate of points
    static bool pointXLessThan(const gxPoint<Dimension> &p1, const gxPoint<Dimension> &p2);

    /// Comparison of y coordinate of points
    static bool pointYLessThan(const gxPoint<Dimension> &p1, const gxPoint<Dimension> &p2);

    inline double &x() { return coords[0]; }
    inline double &y() { Q_ASSERT( 1 < Dimension); return coords[1]; }
    inline double &z() { Q_ASSERT( 2 < Dimension); return coords[2]; }
    inline double &v() { Q_ASSERT( 3 < Dimension); return coords[3]; }

    inline double x() const { return coords[0]; }
    inline double y() const { Q_ASSERT( 1 < Dimension); return coords[1]; }
    inline double z() const { Q_ASSERT( 2 < Dimension); return coords[2]; }
    inline double v() const { Q_ASSERT( 3 < Dimension); return coords[3]; }
};


typedef gxPoint<2> gxPoint2D;
typedef gxPoint<3> gxPoint3D;
typedef gxPoint<4> gxPoint4D;

typedef QList<gxPoint2D> gxPoint2DList;
typedef QVector<gxPoint2D> gxPoint2DVector;

typedef QList<gxPoint3D> gxPoint3DList;
typedef QVector<gxPoint3D> gxPoint3DVector;

typedef QList<gxPoint4D> gxPoint4DList;
typedef QVector<gxPoint4D> gxPoint4DVector;



#include "point_nd.cpp"


#endif // POINT3D_H
