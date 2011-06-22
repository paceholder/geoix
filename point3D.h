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


//template <int Dimension>
//struct gxPoint
//{
//    double coords[Dimension];

//    gxPoint(QVector)
//};




/// Contains coordinates of 3d pooint
struct gxPoint3D
{
    double x;
    double y;
    double z;

    gxPoint3D(double x = 0, double y = 0, double z = 0);

    gxPoint3D& operator=(const gxPoint3D& p);

    bool operator==(gxPoint3D &p);

    gxPoint3D &operator+=(gxPoint3D &p);

    double distance2D(const gxPoint3D &point) const;

    double distance2D(const double x, const double y) const;

    /// Comparison of x coordinate of points
    static bool pointXLessThan(const gxPoint3D &p1, const gxPoint3D &p2);

    /// Comparison of y coordinate of points
    static bool pointYLessThan(const gxPoint3D &p1, const gxPoint3D &p2);
};


typedef QList<gxPoint3D> gxPoint3DList;
typedef QVector<gxPoint3D> gxPoint3DVector;
#endif // POINT3D_H
