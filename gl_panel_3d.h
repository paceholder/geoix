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


#ifndef GL_PANEL_3D_H
#define GL_PANEL_3D_H

#include <QGLWidget>
#include <QMouseEvent>

#include "scene_3d.h"

class gxRenderPanel3D;


/// gxGLPanel is tool for openGL drawing
/*!
    This panel is placed inside the gxRenderPanel
*/
class gxGLPanel3D : public QGLWidget
{
    Q_OBJECT
public:
    /// Constructor
    gxGLPanel3D(gxRenderPanel3D* parent, gxSize3D* size3d);
    ~gxGLPanel3D();

    gx3dScene* getScene() const;
protected:
    /// initialize OpenGL
    void initializeGL();

    /// Is called after widget resizing
    void resizeGL(int width, int height);

    /// All rendering functions are here
    void paintGL();

    // events handlers

    inline void mousePressEvent(QMouseEvent* event)
    {
        lastRotX = 0;
        lastRotZ = 0;
        event->ignore();
    }
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    inline void mouseDoubleClickEvent(QMouseEvent *event) { event->ignore(); }
    void keyPressEvent(QKeyEvent* event);
    void timerEvent ( QTimerEvent * event );
private:
    /// Contains all variables for moving, rotating and scaling
    gx3dScene* scene;

    /// Contains size of scene
    gxSize3D* size3d;

    QPoint lastPos;

    double lastRotX;
    double lastRotZ;
};

#endif // GL_PANEL_3D_H
