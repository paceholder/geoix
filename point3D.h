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

    bool operator==(gxPoint3D& p)
    {
        return ((qAbs(this->x - p.x) < Gx::Eps) &&
                (qAbs(this->y - p.y) < Gx::Eps) &&
                (qAbs(this->z - p.z) < Gx::Eps) );
    }
};


/// Contains coordinates of 2d pooint
struct gxPoint2D
{
    double x;
    double y;

    gxPoint2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    gxPoint2D()
    {
        x = 0; y = 0;
    }

    inline gxPoint2D& operator=(const gxPoint2D& p)
    {
        this->x = p.x;
        this->y = p.y;
        return *this;
    }

    bool operator==(gxPoint2D& p)
    {
        return ((qAbs(this->x - p.x) < Gx::Eps) &&
                (qAbs(this->y - p.y) < Gx::Eps));
    }
};


typedef QVector<gxPoint3D> gxPointsData;
#endif // POINT3D_H
