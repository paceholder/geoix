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


#include <math.h>

#include "gl_panel_2d.h"

#include "render_panel_2D.h"
#include "engine.h"


gxGLPanel2D::gxGLPanel2D(gxRenderPanel2D* parent, gxSize3D* size3d)
    : QGLWidget(parent)
{
    this->size3d = size3d;
    scene = new gx2dScene(size3d);

    // todo:
    int b = parent->getBorderWidth();
    QSize sz = parent->size();

    this->setGeometry(b, b*2, sz.width() - b*2, sz.height() - b*3);
}


gxGLPanel2D::~gxGLPanel2D()
{
    delete scene;
}

//-------------------------------------------

void gxGLPanel2D::resetPosition()
{
    scene->dx = 0.0;
    scene->dy = 0.0;

    double maxObjSize = qMax(size3d->getW(), size3d->getH()); // max size of object
    double minPanelSize = qMin(width(), height());

    scene->scale = minPanelSize / maxObjSize;
}


gx2dScene* gxGLPanel2D::getScene() const
{
    return this->scene;
}

void gxGLPanel2D::initializeGL()
{
    qglClearColor(Qt::white);
    glShadeModel(GL_SMOOTH);
}

void gxGLPanel2D::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-width/2, width/2, -height/2, height/2, +1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void gxGLPanel2D::paintGL()
{
    ((gxRenderPanel*)(this->parent()))->gldraw();
}



//-------------------------------------
// events

void gxGLPanel2D::mouseMoveEvent(QMouseEvent* event)
{
    float dx = (float)(event->x() - lastPos.x()) ;// / width();
    float dy = (float)(event->y() - lastPos.y()) ;// / height();

    if (event->buttons() & Qt::LeftButton)
    {
        double d = dx / width();
        scene->rotZ += d * 180;

        updateGL();
    }


    if (event->buttons() & Qt::RightButton)
    {
        scene->dx += dx;
        scene->dy -= dy;

        updateGL();
    }
    lastPos = event->pos();


    QCursor q;
    q.setShape(Qt::ArrowCursor);
    this->setCursor(q);

    event->accept();
}


void gxGLPanel2D::wheelEvent(QWheelEvent* event)
{
    double d = event->delta()/120.0/20.0;

    // coordinates of mouse
    double x = event->x() - width()/2;
    double y = height()/2 - event->y();

    // coordinates of center of scene
    double x0 = scene->dx;
    double y0 = scene->dy;

    // ofset between mouse and center of scene
    x = x - x0;
    y = y - y0;

    double coeff = (d < 0) ? 1.25 : 1.0/1.25;

    scene->scale *= coeff;
    scene->dx += x - x * coeff;
    scene->dy += y - y * coeff;

    updateGL();

    event->accept();
}


void gxGLPanel2D::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Up: scene->scaleZUp(); break;
    case Qt::Key_Down: scene->scaleZDown(); break;
    }

    updateGL();

    event->accept();
}
