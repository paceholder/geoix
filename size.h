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


#ifndef SIZE_H
#define SIZE_H

#include <math.h>
#include <QObject>

/// Class contains 3d size variables
class gxSize3D : QObject
{
    Q_OBJECT
public:
    /// Constructor
    gxSize3D()
        : QObject()
    {
        setSize(0,0,0,0,0,0);
    }

    /// Constructor
    gxSize3D(const double minx, const double miny, const double minz,
             const double maxx, const double maxy, const double maxz)
    {
        setSize(minx, miny, minz,
                maxx, maxy, maxz);
    }

    /// Constructor
    gxSize3D(const gxSize3D& size)
        : QObject()
    {
        setSize(size.minx, size.miny, size.minz,
                size.maxx, size.maxy, size.maxz);
    }


    gxSize3D& operator=(const gxSize3D& size)
    {
        setSize(size.minx, size.miny, size.minz,
                size.maxx, size.maxy, size.maxz);
        return *this;
    }


    inline double getMinX() const { return minx; }
    inline double getMinY() const { return miny; }
    inline double getMinZ() const { return minz; }

    inline double getMaxX() const { return maxx; }
    inline double getMaxY() const { return maxy; }
    inline double getMaxZ() const { return maxz; }

    double getW() const { return maxx - minx; }
    double getH() const { return maxy - miny; }
    double getD() const { return maxz - minz; }

    void setMinX(const double x) { this->minx = x; }
    void setMinY(const double y) { this->miny = y; }
    void setMinZ(const double z) { this->minz = z; }

    void setMaxX(const double x) { this->maxx = x; }
    void setMaxY(const double y) { this->maxy = y; }
    void setMaxZ(const double z) { this->maxz = z; }

    void setMinPoint(const double x, const double y, const double z) { minx = x, miny = y, minz = z; }
    void setMaxPoint(const double x, const double y, const double z) { maxx = x, maxy = y, maxz = z; }

    void setSize(const double minx, const double miny, const double minz,
                 const double maxx, const double maxy, const double maxz)
    {
        this->minx = minx; this->miny = miny; this->minz = minz;
        this->maxx = maxx; this->maxy = maxy; this->maxz = maxz;
    }

    void setSize(const gxSize3D& size)
    {
        setSize(size.minx, size.miny, size.minz,
                size.maxx, size.maxy, size.maxz);
    }

    /// Characteristic size
    /*!
        Returns diameter of sphere circumscribed around the box W x H x D
    */
    inline double getDiameter()
    {
        return sqrt(pow(getW(), 2) + pow(getH(), 2) + pow(getD(), 2));
    }

    /// returns area of field (width * height)
    inline double area() const { return getW() * getH(); }

private:
    double minx;
    double miny;
    double minz;

    double maxx;
    double maxy;
    double maxz;
};


#endif // SIZE_H
