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


#ifndef SURFACE_DATA_ITERATOR_H
#define SURFACE_DATA_ITERATOR_H

#include <QObject>

#include "constants.h"
#include "surface_data.h"


/// Iterates through the points of surface from x0 to xN, row by row
class gxSurfaceDataIterator : public QObject
{
    Q_OBJECT
public:
    gxSurfaceDataIterator(gxSurfaceData* data)
        : QObject()
    {
        this->data = data;
        init();
    }

    ~gxSurfaceDataIterator() {}

    inline void init() { pos = -1; }
    inline bool goNext()
    {
        if (data->values.count() == 0)
            return false;

        double val = Gx::BlankDouble;

        while (val == Gx::BlankDouble)
        {
            ++pos;
            if (pos == data->nx * data->ny)
                return false;

            val = data->values[pos];
        }

        Q_ASSERT(pos >= 0);
        Q_ASSERT(pos < data->nx * data->ny);

        return true;
    }

    inline int getPos() { return pos; }
    inline int getX() { return pos % data->nx; }
    inline int getY() { return pos / data->nx; }

private:
    gxSurfaceData* data;

    int pos;
};



#endif // SURFACE_DATA_ITERATOR_H
