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


#ifndef SURFACE_DATA_H
#define SURFACE_DATA_H

#include <QVector>

#include "size.h"
#include "constants.h"

#include <GL/gl.h>

class gxSurface;
class gxDataLoader;

/// Represents data of surface object
/*!
    Contains parameters which characterise
    size structure of surface

    \param nx
    \param ny

    \param size3d
 */
class gxSurfaceData
{
    friend class gxSurface;
    friend class gxDataLoader;
    friend class gxSurfaceDataIterator;
    friend class gxContourer;
public:
    /// Constructor
    /*! Gets size of parent surface */
    gxSurfaceData(gxSize3D size = gxSize3D())
        : size3d(size),
        nullValue(Gx::BlankDouble),
        nx(0), ny(0)
    {
    }
    ~gxSurfaceData() {}

    /// Provide access to the data of surface
    inline double& at(const int i, const int j)
    {
        return values[j*nx + i];
    }

    inline double at(const int i, const int j) const
    {
        return values[j * nx + i];
    }

    double at(const double x, const double y) const;

    inline void clear()
    {
        setnXY(0, 0);
    }

    static void setNormal(double x1, double y1, double z1, double x2, double y2, double z2);


    /// Returns the number of knots in each direction
    inline int nX() { return nx; }
    inline int nY() { return ny; }

    /// Sets the number of knots in each direction
    /*!
        Resizing of inner array happens after this operation
    */
    inline void setnX(int i) { nx = i; values.resize(nx * ny); }

    /// The same as setnX
    inline void setnY(int j) { ny = j; values.resize(nx * ny); }

    double getStepX() const;
    double getStepY() const;


    /// Returns value of real X coordinate in array's row with number i
    inline double getX(int i) const
    {
        return (size3d.getMinX() + i * getStepX());
    }

    /// Returns value of real Y coordinate in array's column with number j
    inline double getY(int j) const
    {
        return (size3d.getMinY() + j * getStepY());
    }

    /// Sets the size of surface array pointsX x pointsY
    void setnXY(int i, int j);

    void setData(QVector<double> vector);

    void setSize(gxSize3D size = gxSize3D()) { this->size3d = size; }

    gxSize3D getSize() const { return this->size3d; }

    void setNullValue(double n)
    {
        /// todo: I SHOULD RESET ALL NULLS TO NEW VALUE
        this->nullValue = n;
    }

    double getNullValue() const { return nullValue; }
private:
    gxSize3D size3d; ///< Size of parent surface

    double nullValue;


    /// \private Array of surface z-values
    /*!
        This is one-dimension array but it contains 2d data

        Number of purpose cell caclucates as  j*nx+i
        where j is surface knot x coordinate
        and i is surface knot y coordinate
    */
    QVector<double> values;

    int nx; ///< Number of knots in x direction
    int ny; ///< Number of knots in y direction
};

#endif // SURFACE_DATA_H
