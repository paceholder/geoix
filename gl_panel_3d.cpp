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

#include "gl_panel_3d.h"

#include "render_panel_3D.h"
#include "engine.h"


gxGLPanel3D::gxGLPanel3D(gxRenderPanel3D* parent, gxSize3D* size3d)
    : QGLWidget(parent/*, ((gxRenderPanel3D*)(gxEngine::instance()->getTopLevelPanel()))->getglPanel3d()*/)
{
    this->size3d = size3d;
    scene = new gx3dScene(size3d);

    // todo:
    int b = parent->getBorderWidth();
    QSize sz = parent->size();

    this->setGeometry(b, b*2, sz.width() - b*2, sz.height() - b*3);

    startTimer(20);

    lastRotX = 0;
    lastRotZ = 0;
}


gxGLPanel3D::~gxGLPanel3D()
{
    delete scene;
}

//-------------------------------------------


gx3dScene* gxGLPanel3D::getScene() const
{
    return this->scene;
}

void gxGLPanel3D::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    //glEnable(GL_RESCALE_NORMAL);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


//    float spec[4] = {0.2, 0.2, 0.2, 1.0};
//    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
//    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

    float ambient[4] = {0.5, 0.5, 0.5, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);

    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
   // glEnable(GL_LINE_SMOOTH);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void gxGLPanel3D::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = (GLfloat)width/ (GLfloat)height ;
    gluPerspective(35, x, 1, 100000000);
    glMatrixMode(GL_MODELVIEW);
}


void gxGLPanel3D::paintGL()
{
    ((gxRenderPanel*)(this->parent()))->gldraw();
}



//-------------------------------------
// events

void gxGLPanel3D::mouseMoveEvent(QMouseEvent* event)
{
    float dx = (float)(event->x() - lastPos.x()) / width();
    float dy = (float)(event->y() - lastPos.y()) / height();

    if (event->buttons() & Qt::LeftButton)
    {
        scene->rotX += dy * 180;
        lastRotX = dy * 180;


        while (scene->rotX < 0) scene->rotX += 360;

        if ((fmod(scene->rotX, 360.0) >=  0) &&
            (fmod(scene->rotX, 360.0) < 180))
        {
            scene->rotZ -= dx * 180;
            lastRotZ = -dx * 180;
        }
        else
        {
            scene->rotZ += dx * 180;
            lastRotZ = +dx * 180;
        }

        updateGL();
    }


    if (event->buttons() & Qt::RightButton)
    {
        scene->dx += dx * size3d->getDiameter();
        scene->dy -= dy * size3d->getDiameter();

        updateGL();
    }
    lastPos = event->pos();


    QCursor q;
    q.setShape(Qt::ArrowCursor);
    this->setCursor(q);

    event->accept();
}


void gxGLPanel3D::wheelEvent(QWheelEvent* event)
{
    double d = event->delta()/120.0/20.0;
    scene->dz -= d * size3d->getDiameter();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double x = (double)this->width()/ (double)this->height();
    double znear, zfar;


    // todo: make function of it
    d = size3d->getDiameter();
    if (scene->dz + 2 * d > 0)
    {
        znear = 10;
        zfar  = 4 * d;
    }
    else
    {
        znear = qAbs(scene->dz + 2 * d);
        zfar  = qAbs(scene->dz - 2 * d);
    }

    gluPerspective(35, x,
                   znear,
                   zfar);

    glMatrixMode(GL_MODELVIEW);

    //------------------

    updateGL();

    event->accept();
}


void gxGLPanel3D::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Up: scene->scaleZUp(); break;
    case Qt::Key_Down: scene->scaleZDown(); break;
    }

    updateGL();

    event->accept();
}

void gxGLPanel3D::timerEvent(QTimerEvent *event)
{
    if (qAbs(lastRotX) < 0.05)
        lastRotX = 0;
    else
    {
        lastRotX /= 1.05;
        scene->rotX += lastRotX;
    }

    if (qAbs(lastRotZ) < 0.05)
        lastRotZ = 0;
    else
    {
        lastRotZ /= 1.05;
        scene->rotZ += lastRotZ;
    }

    updateGL();

    event->accept();
}
