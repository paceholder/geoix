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


#ifndef CONTOURER_FAST_H
#define CONTOURER_FAST_H

#include <QtCore/QMap>
#include <QtCore/QQueue>

#include "flat_contour.h"
#include "edge.h"


typedef QMap<int,QPair<int, int> > gxMap;


class gxSurfaceData;

/// Class is intended to build isolines of current gxSurface
class gxContourer
{
public:
    /// Constructor. Takes z-step between isolines.
    gxContourer(double step);

    /// Destructor
    virtual ~gxContourer() {}

    /// Starts work of class.
    /*!
        \param data is the surface's data
        \param contours is container to fill
    */
    void run(gxSurfaceData* data, gxFlatContourList* contours);

    /// Marks all edges in current grid crossin currens plane z=curz
    void markEdges(double curz);

    /// Clears vector of edges
    void resetEdges() { edges.fill(0); }

    /// Run through the marked edges
    void runEdges();

    /// Run cycle through marked edges checkin each egde of triangle current edge is belong to.
    void walkEdge(QQueue<gxEdge>& runedges);

    /// Adds 3d point to the current gxContour
    void addPoint(int pos, int vector, int direction);
private:
    double step;

    double curz; // current z (depth)

    /// Currently building contour
    gxFlatContour* curcont;

    /// SurfaceData to analyse
    gxSurfaceData* data;

    /// Contours set to fill
    gxFlatContourList* contours;

    /// Vector contains marked edges
    QVector<uchar> edges; // bit
};

#endif // CONTOURER_FAST_H




































