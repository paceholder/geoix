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


#ifndef COORD_SYSTEM_2D_H
#define COORD_SYSTEM_2D_H

#include <QGLWidget>
#include <GL/gl.h>

#include "gl_panel_2d.h"
#include "size.h"


/// Class represents 2d coordinate system.
/*!
    This coordinate systep draw itself in
    2d rendering panel.
    Probably it's worth to merge 2d and 3d coordinate system in one object.
*/
class gxCoordSystem2D : public QObject
{
    Q_OBJECT
public:
    /// Constructor
    explicit gxCoordSystem2D(gxGLPanel2D* gl_panel, gxSize3D* size3d);
    virtual ~gxCoordSystem2D() {}

    /// Function render coordinate system to 2d rendering window
    void draw()
    {
        // Rect around the objects
        drawSceneRectangle();

        // further draw usin' panel's coordinates
        glLoadIdentity();

        // semitransparent rectangles
        drawSemitrasparentRects();

        // Ticks and numbers
        drawScales();
    }
private:
    gxSize3D* size3d;

    gxGLPanel2D* gl_panel;

    int panel_step;
    double real_step;

    QFontMetrics metrics;

    /// Draws ticks at the bottom of the window
    void drawHorizontalAxisTick(int xi, bool longTick);

    /// Draws ticks at the left side of the window
    void drawVerticalAxisTick(int yi, bool longTick);


    void drawHorizontalAxisNumber(int xi, double x);

    void drawVerticalAxisNumber(int yi, double y);


    /// Drawing stipped rectangle around scene.
    void drawSceneRectangle();
    /// Draws semitransparent rectangles for better view of numbers
    void drawSemitrasparentRects();
    /// Draws ticks and numbers
    void drawScales();
};


#endif // COORD_SYSTEM_2D_H
