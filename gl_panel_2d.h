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


#ifndef GL_PANEL_2D_H
#define GL_PANEL_2D_H

#include <QGLWidget>
#include <QMouseEvent>

#include "scene_2d.h"

class gxRenderPanel2D;


/// gxGLPanel is tool for openGL drawing
/*!
    This panel is placed inside the gxRenderPanel
*/
class gxGLPanel2D : public QGLWidget
{
    Q_OBJECT
public:
    /// Constructor
    gxGLPanel2D(gxRenderPanel2D* parent, gxSize3D* size3d);
    ~gxGLPanel2D();

    gx2dScene* getScene() const;

public slots:
    void resetPosition();
protected:
    /// initialize OpenGL
    void initializeGL();

    /// Is called after widget resizing
    void resizeGL(int width, int height);

    /// All rendering functions are here
    void paintGL();

    // events handlers

    inline void mousePressEvent(QMouseEvent* event) { event->ignore(); }
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    inline void mouseDoubleClickEvent(QMouseEvent *event) { event->ignore(); }
    void keyPressEvent(QKeyEvent* event);
private:
    /// Contains all variables for moving, rotating and scaling
    gx2dScene* scene;

    /// Contains size of scene
    gxSize3D* size3d;

    QPoint lastPos;
};

#endif // GL_PANEL_2D_H
