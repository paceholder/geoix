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


#ifndef SCENE_2D_H
#define SCENE_2D_H


#include <QGLWidget>

#include "size.h"
#include <math.h>

#include "size.h"


/// Class contains all params of transformations
/// applied to the 2d render panel
class gx2dScene : public QObject
{
    Q_OBJECT
public:
    inline gx2dScene(gxSize3D* size3d)
    {
        this->size3d = size3d;
        dx = 0;
        dy = 0;

        rotZ = 0;

        scale = 1;
    }
    virtual ~gx2dScene() {}

    /// \todo remove or rename
    inline void scaleZUp() { scale *= 1.25; }
    inline void scaleZDown() { scale /= 1.25; }

    /// Modification of current GL_MODELVIEW matrix
    inline void applyTransformations()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslated(dx, dy, 0);

        glRotated(rotZ, 0.0, 0.0, 1.0);

        glScalef(scale, scale, 1.0);

        glTranslated(-size3d->getMinX(),     -size3d->getMinY(), 0);
        glTranslated(-size3d->getW()/2.0, -size3d->getH()/2.0, 0);
    }
private:
    gxSize3D* size3d;
public:
    double scale;
    double dx, dy;
    double rotZ;
};

#endif // SCENE_2D_H
