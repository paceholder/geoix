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


#include "coord_system_2d.h"


gxCoordSystem2D::gxCoordSystem2D(QGLWidget *gl_panel, gxSize3D *size3d)
{
    this->gl_panel = gl_panel;
    this->size3d = size3d;

    panel = (gxGLPanel2D*)gl_panel;

    real_step = (panel->getScene()->dx + panel->width()/2) / 16;
}


void gxCoordSystem2D::drawSceneRectangle()
{

    int factor = 1;
    unsigned pattern;

    glEnable(GL_LINE_STIPPLE);

        pattern = 0x0F0F; // 0000 1111 0000 1111
        glLineStipple(factor, pattern);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_LINE_LOOP);
            glVertex2d(size3d->getMinX(), size3d->getMinY());
            glVertex2d(size3d->getMaxX(), size3d->getMinY());
            glVertex2d(size3d->getMaxX(), size3d->getMaxY());
            glVertex2d(size3d->getMinX(), size3d->getMaxY());
        glEnd();

        pattern = 0xF0F0; // 1111 0000 1111 0000
        glLineStipple(factor, pattern);
        glColor3f(0.0, 0.0, 0.0);

        glBegin(GL_LINE_LOOP);
            glVertex2d(size3d->getMinX(), size3d->getMinY());
            glVertex2d(size3d->getMaxX(), size3d->getMinY());
            glVertex2d(size3d->getMaxX(), size3d->getMaxY());
            glVertex2d(size3d->getMinX(), size3d->getMaxY());
        glEnd();

    glDisable(GL_LINE_STIPPLE);

}


void gxCoordSystem2D::drawSemitrasparentRects()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4d(1.0, 1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
        glVertex2i(-panel->width()/2, -panel->height()/2 + 30);
        glVertex2i(-panel->width()/2, -panel->height()/2 );
        glVertex2i(+panel->width()/2, -panel->height()/2);
        glVertex2i(+panel->width()/2, -panel->height()/2 + 30);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2i(-panel->width()/2, +panel->height()/2);
        glVertex2i(-panel->width()/2, -panel->height()/2 + 30);
        glVertex2i(-panel->width()/2 + 60, -panel->height()/2 + 30);
        glVertex2i(-panel->width()/2 + 60, +panel->height()/2);
    glEnd();

    glDisable(GL_BLEND);
}

void gxCoordSystem2D::drawScales()
{
    panel_step = real_step * panel->getScene()->scale;

    // New step depends on current scale
    if (panel_step < 16) real_step *= 2;
    if (panel_step > 48) real_step /= 4;

    double scale = panel->getScene()->scale;

    // world_x = (window_x - center_of_scene_in_window_coord) / scale + (center_of_scene_in_world_coord)

    // center_of_scene_in_world_coord
    double centerX = size3d->getMinX() + size3d->getW()/2;
    double centerY = size3d->getMinY() + size3d->getH()/2;
    int centerXpanel = panel->getScene()->dx;
    int centerYpanel = panel->getScene()->dy;

    double minx = ( -panel->width()/2 - centerXpanel) / scale + centerX;
    double maxx = ( +panel->width()/2 - centerXpanel) / scale + centerX;

    double miny = ( -panel->height()/2 - centerYpanel) / scale + centerY;
    double maxy = ( +panel->height()/2 - centerYpanel) / scale + centerY;

    QString s;
    QFontMetrics metrics = panel->fontMetrics();

    // todo: OMFG REFACTORING!!!!

    /// Bottom. From center to the right border
    int xi, counter;
    double x = size3d->getMinX() + size3d->getW()/2;
    counter = 0;
    glColor3f(0.0, 0.0, 0.0);
    while (x < maxx)
    {
        xi = (x - centerX) * scale + centerXpanel;

        glBegin(GL_LINES);
            glVertex2i(xi , -panel->height()/2);
            // every 5th tick is longer than others
            if (counter % 5 == 0)
                glVertex2i(xi , -panel->height()/2 + 10);
            else
                glVertex2i(xi , -panel->height()/2 + 5);
        glEnd();


        if (counter % 5 == 0)
        {
            s = QString::number(x, 'f', 1);
            panel->renderText(double(xi - metrics.width(s)/2),
                              double(-panel->height()/2 + 15),
                              0.0, s);
        }

        x += real_step;
        ++counter;
    }


    x = size3d->getMinX() + size3d->getW()/2;
    counter = 0;
    while (x > minx)
    {
        xi = (x - centerX) * scale + centerXpanel;

        glBegin(GL_LINES);
            glVertex2i(xi , -panel->height()/2);
            // every 5th tick is longer than others
            if (counter % 5 == 0)
                glVertex2i(xi , -panel->height()/2 + 10);
            else
                glVertex2i(xi , -panel->height()/2 + 5);
        glEnd();


        if ((counter % 5 == 0) && (counter))
        {
            s = QString::number(x, 'f', 1);
            panel->renderText(double(xi - metrics.width(s)/2),
                              double(-panel->height()/2 + 15),
                              0.0, s);
        }

        x -= real_step;
        ++counter;
    }


    int yi;
    double y = size3d->getMinY() + size3d->getH()/2;
    counter = 0;
    glColor3f(0.0, 0.0, 0.0);
    while (y < maxy)
    {
        yi = (y - centerY) * scale + centerYpanel;

        // tick
        glBegin(GL_LINES);
            glVertex2i(-panel->width()/2, yi);

            // every 5th tick is longer than others
            if (counter % 5 == 0)
                glVertex2i(-panel->width()/2 + 10, yi);
            else
                glVertex2i(-panel->width()/2 + 5, yi);
        glEnd();


        if (counter % 5 == 0)
        {
            s = QString::number(y, 'f', 1);
            panel->renderText(double(-panel->width()/2 + 15),
                              double(yi),
                              0.0, s);
        }

        y += real_step;
        ++counter;
    }


    y = size3d->getMinY() + size3d->getH()/2;
    counter = 0;
    while (y > miny)
    {
        yi = (y - centerY) * scale + centerYpanel;

        // tick
        glBegin(GL_LINES);
            glVertex2i(-panel->width()/2, yi);
            // every 5th tick is longer than others
            if (counter % 5 == 0)
            {
                glVertex2i(-panel->width()/2 + 10, yi);
            }
            else
                glVertex2i(-panel->width()/2 + 5, yi);
        glEnd();

        if ((counter % 5 == 0) && (counter))
        {
            s = QString::number(y, 'f', 1);
            panel->renderText(double(-panel->width()/2 + 15),
                              double(yi),
                              0.0, s);
        }

        y -= real_step;
        ++counter;
    }

}
