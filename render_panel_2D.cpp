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


#include "render_panel_2D.h"

#include "gl_panel_2d.h"
#include "engine.h"

gxRenderPanel2D::gxRenderPanel2D(QWidget* parent)
    : gxRenderPanel(parent)
{
    border_active_color   = QColor(140,220,140);
    border_inactive_color = QColor(90,140,90);

    // size is passed to gl_panel and to coord_system

    gxRenderPanel* topLevelPanel = gxEngine::instance()->getTopLevelPanel();
    QGLWidget* glw = 0;
    if (topLevelPanel) glw =  topLevelPanel->getGLPanel();

    gl_panel = new gxGLPanel2D(this, glw, size3d);
    gl_panel->setMouseTracking(true);
    gl_panel->makeCurrent();
    gl_panel->setFocusPolicy(Qt::ClickFocus);

    coord_system = new gxCoordSystem2D(static_cast<gxGLPanel2D*>(gl_panel), size3d);
}



//------------------------------------------------------------------------------



void gxRenderPanel2D::gldraw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ((gxGLPanel2D*)gl_panel)->getScene()->applyTransformations();

    QVectorIterator<gxVisualObject*> it(objects);
    while (it.hasNext())
    {
        gxVisualObject* obj = it.next();
        obj->draw2D();
    }

    // border afterall
    coord_system->draw();

}



