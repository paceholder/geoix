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


#include "point_nd.h"

#include "math.h"
#include "constants.h"


template <int Dimension>
gxPoint<Dimension>::gxPoint(const double *data)
{
    for(int i = 0; i < Dimension; ++i)
        coords[i] = data[i];
}


template <int Dimension>
gxPoint<Dimension>::gxPoint(QVector<double> vector)
{
    Q_ASSERT(vector.size() == Dimension);
    for(int i = 0; i < Dimension; ++i)
        coords[i] = vector[i];
}

template <int Dimension>
gxPoint<Dimension>::gxPoint(double x, double y, double z)
{
    Q_ASSERT(3 <= Dimension);

    coords[0] = x;
    coords[1] = y;
    coords[2] = z;
}

template <int Dimension>
gxPoint<Dimension>& gxPoint<Dimension>::operator=(const gxPoint<Dimension> &p)
{
    for(int i = 0; i < Dimension; ++i)
        this->coords[i] = p.coords[i];

    return *this;
}

template <int Dimension>
bool gxPoint<Dimension>::operator==(const gxPoint<Dimension> &p)
{
    for(int i = 0; i < Dimension; ++i)
        if (this->coords[i] != p.coords[i])
            return false;

    return true;
}

template <int Dimension>
gxPoint<Dimension>& gxPoint<Dimension>::operator+=(gxPoint<Dimension> &p)
{
    for(int i = 0; i < Dimension; ++i)
        this->coords[i] += p.coords[i];

    return *this;
}

template <int Dimension>
double gxPoint<Dimension>::distance2D(const gxPoint<Dimension> &p) const
{
    return sqrt(pow(coords[0] - p.coords[0], 2.0) +
                pow(coords[1] - p.coords[1], 2.0));
}

template <int Dimension>
double gxPoint<Dimension>::distance2D(const double x, const double y) const
{
    return sqrt(pow(coords[0] - x, 2.0) +
                pow(coords[1] - y, 2.0));
}

/// Comparison of x coordinate of points
template <int Dimension>
bool gxPoint<Dimension>::pointXLessThan(const gxPoint<Dimension> &p1, const gxPoint<Dimension> &p2)
{
    return p1.coords[0] < p2.coords[0];
}

/// Comparison of y coordinate of points
template <int Dimension>
bool gxPoint<Dimension>::pointYLessThan(const gxPoint<Dimension> &p1, const gxPoint<Dimension> &p2)
{
    return p1.coords[1] < p2.coords[1];
}
