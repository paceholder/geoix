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
//    along with Geoix.  If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#ifndef FLAT_CONTOUR_H
#define FLAT_CONTOUR_H

#include "contour.h"


#include "point_nd.h"


/// Class represents contour with constant Z-value
/*!
    Class inherits gxContour but reimplement
    some functions getting new points.
*/
class gxFlatContour : public gxContour
{
public:
    /// Consturctor
    gxFlatContour(double z)
        : gxContour()
    {
        this->z = z;
    }

    /// Destructor
    virtual ~gxFlatContour() {}

    /// Addin 2d point to the back of contour
    void addPointBack(gxPoint3D& point)
    {
        data.append(gxPoint3D(point.x(), point.y(), z));
        checkClosing();
    }

    /// Addin 2d point to the frong of contour
    void addPointFront(gxPoint3D& point)
    {
        data.prepend(gxPoint3D(point.x(), point.y(), z));
        checkClosing();
    }

    /// Returns z-value of contour
    inline double getZ() { return z; }
private:
    /// Z-value of contour
    double z;
};

/// Vector of gxFlanContour*
typedef QList<gxFlatContour*> gxFlatContourList;


#endif // FLAT_CONTOUR_H
