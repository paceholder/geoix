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


gxCoordSystem2D::gxCoordSystem2D(gxGLPanel2D *gl_panel, gxSize3D *size3d)
    : metrics(gl_panel->fontMetrics())
{
    this->gl_panel = gl_panel;
    this->size3d = size3d;

    //panel = static_cast<gxGLPanel2D*>(gl_panel);

    this->gl_panel = gl_panel;

    //font metrics
//    metrics = gl_panel->fontMetrics();


    //????
    real_step = (gl_panel->getScene()->dx + gl_panel->width()/2) / 16;
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


//------------------------------------------------------------------------------


void gxCoordSystem2D::drawSemitrasparentRects()
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4d(1.0, 1.0, 1.0, 0.5);
    glBegin(GL_QUADS);
        glVertex2i(-gl_panel->width()/2, -gl_panel->height()/2 + 30);
        glVertex2i(-gl_panel->width()/2, -gl_panel->height()/2 );
        glVertex2i(+gl_panel->width()/2, -gl_panel->height()/2);
        glVertex2i(+gl_panel->width()/2, -gl_panel->height()/2 + 30);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2i(-gl_panel->width()/2, +gl_panel->height()/2);
        glVertex2i(-gl_panel->width()/2, -gl_panel->height()/2 + 30);
        glVertex2i(-gl_panel->width()/2 + 60, -gl_panel->height()/2 + 30);
        glVertex2i(-gl_panel->width()/2 + 60, +gl_panel->height()/2);
    glEnd();

    glDisable(GL_BLEND);
}

//------------------------------------------------------------------------------

void gxCoordSystem2D::drawHorizontalAxisTick(int xi, bool longTick)
{
    // every 5th tick is longer than others
    int dx = longTick ? 10 : 5;

    glBegin(GL_LINES);
        glVertex2i(xi , -gl_panel->height()/2);
        glVertex2i(xi , -gl_panel->height()/2 + dx);
    glEnd();
}


//------------------------------------------------------------------------------

void gxCoordSystem2D::drawVerticalAxisTick(int yi, bool longTick)
{
    // every 5th tick is longer than others
    int dy = longTick ? 10 : 5;

    glBegin(GL_LINES);
        glVertex2i(-gl_panel->width()/2, yi);
        glVertex2i(-gl_panel->width()/2 + dy, yi);
    glEnd();
}


void gxCoordSystem2D::drawHorizontalAxisNumber(int xi, double x)
{
    QString s = QString::number(x, 'f', 1);
    gl_panel->renderText(double(xi - metrics.width(s)/2),
                         double(-gl_panel->height()/2 + 15),
                         0.0, s);
}


void gxCoordSystem2D::drawVerticalAxisNumber(int yi, double y)
{
    QString s = QString::number(y, 'f', 1);
    gl_panel->renderText(double(-gl_panel->width()/2 + 15),
                         double(yi),
                         0.0, s);
}


void gxCoordSystem2D::drawScales()
{
    panel_step = real_step * gl_panel->getScene()->scale;

    // New step depends on current scale
    if (panel_step < 16) real_step *= 2;
    if (panel_step > 48) real_step /= 4;

    double scale = gl_panel->getScene()->scale;

    // world_x = (window_x - center_of_scene_in_window_coord) / scale + (center_of_scene_in_world_coord)

    // center_of_scene_in_world_coord
    double centerX = size3d->getMinX() + size3d->getW()/2;
    double centerY = size3d->getMinY() + size3d->getH()/2;

    // center of the scene in panel's coordinate
    int centerXpanel = gl_panel->getScene()->dx;
    int centerYpanel = gl_panel->getScene()->dy;

    double minx = ( -gl_panel->width()/2 - centerXpanel) / scale + centerX;
    double maxx = ( +gl_panel->width()/2 - centerXpanel) / scale + centerX;

    double miny = ( -gl_panel->height()/2 - centerYpanel) / scale + centerY;
    double maxy = ( +gl_panel->height()/2 - centerYpanel) / scale + centerY;

    QString s;

    // todo: OMFG REFACTORING!!!!

    /// Bottom. From center to the right border
    int xi, counter;
    double x;

    glColor3f(0.0, 0.0, 0.0);

    x = size3d->getMinX() + size3d->getW()/2;
    counter = 0;
    while (x < maxx)
    {
        xi = (x - centerX) * scale + centerXpanel;

        drawHorizontalAxisTick(xi, counter % 5 == 0);

        if (counter % 5 == 0)
            drawHorizontalAxisNumber(xi, x);

        x += real_step;
        ++counter;
    }


    x = size3d->getMinX() + size3d->getW()/2;
    counter = 0;
    while (x > minx)
    {
        xi = (x - centerX) * scale + centerXpanel;

        drawHorizontalAxisTick(xi, counter % 5 == 0);

        if ((counter % 5 == 0) && (counter))
            drawHorizontalAxisNumber(xi, x);

        x -= real_step;
        ++counter;
    }


    int yi;
    double y;

    y = size3d->getMinY() + size3d->getH()/2;
    counter = 0;
    glColor3f(0.0, 0.0, 0.0);
    while (y < maxy)
    {
        yi = (y - centerY) * scale + centerYpanel;

        drawVerticalAxisTick(yi, counter % 5 == 0);


        if (counter % 5 == 0)
            drawVerticalAxisNumber(yi, y);

        y += real_step;
        ++counter;
    }


    y = size3d->getMinY() + size3d->getH()/2;
    counter = 0;
    while (y > miny)
    {
        yi = (y - centerY) * scale + centerYpanel;

        drawVerticalAxisTick(yi, counter % 5 == 0);

        if ((counter % 5 == 0) && (counter))
            drawVerticalAxisNumber(yi, y);

        y -= real_step;
        ++counter;
    }

}
