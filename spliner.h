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


#ifndef SPLINER_H
#define SPLINER_H

#include <QObject>

#include "surface_data.h"
#include "point3D.h"
#include "size.h"

/// Interface for all types of spline algorithms
class gxSpliner : public QObject
{
    Q_OBJECT
public:
    gxSpliner() {}
    virtual ~gxSpliner() {}

    void virtual calculate(QVector<gxPoint3D>& points, // input
                           gxSurfaceData* data) = 0;   // output

signals:
    void progress(double); // 0..1
protected:
    QString name;

    QVector<gxPoint3D> points;
    gxSize3D size3d;
};

#endif // SPLINER_H
