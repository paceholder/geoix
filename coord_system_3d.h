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


#ifndef COORD_SYSTEM_3D_H
#define COORD_SYSTEM_3D_H

#include <GL/gl.h>
#include "size.h"

#include <QGLWidget>


/// Class represents 3d coordinate system.
/*!
    This coordinate system draw itself in
    3d rendering panel.
    Probably it's worth to merge 2d and 3d coordinate system in one object.
*/
class gxCoordSystem3D : public QObject
{
    Q_OBJECT
public:
    /// Constructor
    gxCoordSystem3D(QGLWidget* gl_panel, gxSize3D* size3d);
    /// Cirtual destructor
    virtual ~gxCoordSystem3D() {}

    /// 3d rendering
    void draw();
private:
    /// Size of coord system.
    /// gxCoordSystem3D doesn't own size object.
    gxSize3D* size3d;

    /// No comments
    QGLWidget* gl_panel;
};

#endif // COORD_SYSTEM_3D_H
