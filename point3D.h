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
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef POINT3D_H
#define POINT3D_H

#include <QVector>

#include "constants.h"
#include "math.h"

/// Contains coordinates of 3d pooint
struct gxPoint3D
{
    double x;
    double y;
    double z;

    gxPoint3D(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    gxPoint3D()
    {
        x = 0; y = 0; z = 0;
    }

    inline gxPoint3D& operator=(const gxPoint3D& p)
    {
        this->x = p.x;
        this->y = p.y;
        this->z = p.z;

        return *this;
    }

    inline bool operator==(gxPoint3D& p)
    {
        return ((qAbs(this->x - p.x) < Gx::Eps) &&
                (qAbs(this->y - p.y) < Gx::Eps) &&
                (qAbs(this->z - p.z) < Gx::Eps) );
    }

    inline double distance(const gxPoint3D &point) const
    {
        return sqrt(pow(x - point.x, 2) +
                    pow(y - point.y, 2) +
                    pow(z - point.z, 2));
    }

    inline double distance(const double x,
                           const double y) const
    {
        return sqrt(pow(this->x - x, 2) +
                    pow(this->y - y, 2) +
                    pow(this->z - z, 2));
    }

    /// Comparison of x coordinate of points
    static bool pointXLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
    {
        return p1.x < p2.x;
    }

    /// Comparison of y coordinate of points
    static bool pointYLessThan(const gxPoint3D &p1, const gxPoint3D &p2)
    {
        return p1.y < p2.y;
    }
};


typedef QVector<gxPoint3D> gxPoint3DList; //Data;
#endif // POINT3D_H
