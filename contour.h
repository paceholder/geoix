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


#ifndef CONTOUR_H
#define CONTOUR_H

#include <QObject>
#include <QVector>

#include "point3D.h"
#include "constants.h"

class gxLines;

/// Class represents line which consists of 3d points
class gxContour : public QObject
{
    Q_OBJECT

    /// wtf?
    friend class gxLines;
public:
    /// Constructor
    gxContour()
        : QObject(),
        closed(false)
    { }

    /// Destructor
    virtual ~gxContour() {}


    /// Adds new point to the back of vector
    void addPointBack(gxPoint3D& point)
    {
        data.append(point);
        checkClosing();
    }

    /// Adds new point to the front of vector
    void addPointFront(gxPoint3D& point)
    {
        data.prepend(point);
        checkClosing();
    }

    /// Clears vector of points.
    void clearData() { data.clear(); }

    /// Returns point by its number in vector.
    /// Actully I don't know that is the best way to hadle i out of vector ranges..
    inline const gxPoint3D& at(int i)
    {
        Q_ASSERT(i >= 0);
        Q_ASSERT(i < data.count());

        return data[i];
    }

    /// Simple
    inline int count() { return data.count(); }

    /// Returns variable standing for gxContour closing state.
    /// In other words gxContour could be simple line or loop.
    bool isClosed() { return closed; }

protected:
    /// Vector of 3d points
    QVector<gxPoint3D> data;

    /// Whether contour closed or not
    bool closed;

    /// After adding new points it's necesary to check wheter contour is closed.
    void checkClosing()
    {
        if ((data.count() > 1) &&
            (data.first() == data.last()))
        {
            data.pop_back();
            this->closed = true;
        }
        else
            this->closed = false;
    }
};

/// Vector of gxContour
typedef QVector<gxContour*> gxContours;

#endif // CONTOUR_H
