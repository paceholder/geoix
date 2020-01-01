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


#include "render_panel_3D.h"

#include "gl_panel_3d.h"
#include "engine.h"

gxRenderPanel3D::gxRenderPanel3D(QWidget* parent)
    : gxRenderPanel(parent)
{
    border_active_color   = QColor(140,140,220);
    border_inactive_color = QColor(90,90,140);

//    move(40,40); // todo

    gxRenderPanel* topLevelPanel = gxEngine::instance()->getTopLevelPanel();
    QGLWidget* glw = 0;
    if (topLevelPanel) glw =  topLevelPanel->getGLPanel();



//    QGLFormat f;
//    f.setAlpha(true);
//    f.setStereo(true);
//    QGLFormat::setDefaultFormat(f);

    gl_panel = new gxGLPanel3D(this, glw, size3d);
    gl_panel->setMouseTracking(true);
    gl_panel->makeCurrent();
    gl_panel->setFocusPolicy(Qt::ClickFocus);

//    if ( !gl_panel->format().stereo() )
//        QMessageBox::critical(this, "hardware problem","hardware problem");

    coord_system = new gxCoordSystem3D(gl_panel, size3d);
}



void gxRenderPanel3D::gldraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ((gxGLPanel3D*)gl_panel)->getScene()->applyTransformations();

    coord_system->draw();

    QVectorIterator<gxVisualObject*> it(objects);
    while (it.hasNext())
    {
        gxVisualObject* obj = it.next();
        obj->draw3D();
    }


    glLoadIdentity();

    float ambient[4] = {0.3, 0.3, 0.3, 1.0};
    float diffuse[4] = {0.7, 0.7, 0.7, 1.0};
//    float specular[4] = {0.5, 0.5, 0.5, 1.0};


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    float pos[4] = { -500.0, -500.0, 500.0, 0 };

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
