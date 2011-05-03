//------------------------------------------------------------------------
//    This file is part of Geoix.
//
//    Copyright (C) 2010 Dmitriy Pinaev
//
//    Geoix is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 4 of the License, or
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


#ifndef CUBE_H
#define CUBE_H

#include "visual_object.h"
#include "surface_data.h"
#include "surface.h"

/// class represents 3d volume of rock
/// restricted by top surface and botton surface
class gxCube : gxVisualObject
{
    Q_OBJECT
public:
    enum GridSurface
    {
        Up,
        Down
    };
    enum SedimentationModel
    {
        One,
        Two,
        Three
    };

    gxCube(gxTreeFolderObject* parent);

    virtual ~gxCube();

    void setRestrictingSurfaces(gxSurface* top,
                                gxSurface* bottom,
                                gxCube::GridSurface gridDefiningSurface,
                                gxCube::SedimentationModel sedimentationModel);

    virtual void draw2D() {}

    virtual void draw3D() {}

    virtual void recalcSize() {}

private:
    QSharedPointer<gxSurfaceData> topSurfase;
    QSharedPointer<gxSurfaceData> bottomSurface;
};


#endif // CUBE_H
