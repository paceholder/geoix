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


#include "coord_system_3d.h"


gxCoordSystem3D::gxCoordSystem3D(QGLWidget *gl_panel, gxSize3D *size3d)
{
    this->gl_panel = gl_panel;
    this->size3d = size3d;
}


void gxCoordSystem3D::draw()
{
    glColor3f(1, 1, 1);

    glBegin(GL_LINE_LOOP);
        glVertex3d(size3d->getMinX(), size3d->getMinY(), size3d->getMinZ());
        glVertex3d(size3d->getMaxX(), size3d->getMinY(), size3d->getMinZ());
        glVertex3d(size3d->getMaxX(), size3d->getMaxY(), size3d->getMinZ());
        glVertex3d(size3d->getMinX(), size3d->getMaxY(), size3d->getMinZ());
    glEnd();


    // top rect
    glBegin(GL_LINE_LOOP);
        glVertex3d(size3d->getMinX(), size3d->getMinY(), size3d->getMaxZ());
        glVertex3d(size3d->getMaxX(), size3d->getMinY(), size3d->getMaxZ());
        glVertex3d(size3d->getMaxX(), size3d->getMaxY(), size3d->getMaxZ());
        glVertex3d(size3d->getMinX(), size3d->getMaxY(), size3d->getMaxZ());
    glEnd();

    // four vertical edges
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3d(size3d->getMinX(), size3d->getMinY(), size3d->getMinZ());
        glVertex3d(size3d->getMinX(), size3d->getMinY(), size3d->getMaxZ());
        glColor3f(1, 1, 1);

        glVertex3d(size3d->getMaxX(), size3d->getMinY(), size3d->getMinZ());
        glVertex3d(size3d->getMaxX(), size3d->getMinY(), size3d->getMaxZ());

        glVertex3d(size3d->getMaxX(), size3d->getMaxY(), size3d->getMinZ());
        glVertex3d(size3d->getMaxX(), size3d->getMaxY(), size3d->getMaxZ());

        glVertex3d(size3d->getMinX(), size3d->getMaxY(), size3d->getMinZ());
        glVertex3d(size3d->getMinX(), size3d->getMaxY(), size3d->getMaxZ());
    glEnd();



    double dx = size3d->getW()/10;
    double dy = size3d->getH()/10;
    double dz = size3d->getD()/10;


    QString s;
    glColor3f(1.0, 1.0, 1.0);
    for(int i = 1; i < 10; ++i)
    {
        s = QString::number(size3d->getMinX() + dx * i, 'f', 1);
        gl_panel->renderText(size3d->getMinX() + dx * i, size3d->getMinY(), size3d->getMinZ(), s);
        s = QString::number(size3d->getMinY() + dy * i, 'f', 1);
        gl_panel->renderText(size3d->getMinX(), size3d->getMinY() + dy * i, size3d->getMinZ(), s);
        s = QString::number(size3d->getMinZ() + dz * i, 'f', 1);
        gl_panel->renderText(size3d->getMinX(), size3d->getMinY(), size3d->getMinZ() + dz * i, s);
    }
}
