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


#ifndef RENDER_PANEL_3D_H
#define RENDER_PANEL_3D_H

#include "render_panel.h"
#include "coord_system_3d.h"


/// Class represents render panel for 3d graphic rendering
/*!
    Class can register by itself different 3d objects (gxVisualObject)
    and make them rendered.

    3d graphics is rendered in special panel gxGLPanel (QGLWidget)
*/
class gxRenderPanel3D : public gxRenderPanel
{
    Q_OBJECT
public:
    gxRenderPanel3D(QWidget* parent);

    /// \todo Merge 2d and 3d coordinate system,
    /// move followin code to the ~gxRenderPanel
    virtual ~gxRenderPanel3D()
    {
        delete coord_system;
    }

    /// Function draws all 3d objects registered in this panel
    /*!
        Functions clears OpenGL color and depth buffers
        Applies transformations to the scene (offset, rotation, scaling)
        Draws coordinate system and all objects
    */
    void gldraw();
private:
    /// Member which drawd box of 3d coordinate system
    gxCoordSystem3D* coord_system;
};


#endif // RENDER_PANEL_3D_H
