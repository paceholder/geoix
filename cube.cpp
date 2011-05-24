//------------------------------------------------------------------------
//    This file is part of Geoix.
//
//    Copyright (C) 2010 Dmitriy Pinaev
//
//    Geoix is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 4 of the License, or
//    (at your option) any later version.
//
//    Geoix is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------



#include "cube.h"


#include "logger.h"
#include "tree_menu_fabric.h"

#include "color_palette.h"

gxCube::gxCube(gxTreeFolderObject *paren, gxSurfaceData *topData, gxSurfaceData *bottomData)
    : gxVisualObject(parent),
      topSurfase(topData),
      bottomSurface(bottomData)
{
    name = tr("New 3D Cube");

    setRandomColor();


    if (topSurfase && bottomSurface)
    {
        this->recalcSize();
    }

    // Color pallete for gradient fill
    palette = new gxContinuesColorPalette();
    palette->setColorInterpolationMode(gxContinuesColorPalette::HSL);
    palette->addColor(0,  Qt::darkBlue);
    palette->addColor(1,  Qt::red);

    gxLogger::instance()->logEvent("3d cube '" + name + "' created");
}




gxCube::~gxCube()
{
    if (topSurfase) delete topSurfase;
    if (bottomSurface) delete bottomSurface;
}


//-------------------------------------------------------------------------------


void gxCube::setRestrictingSurfaces(gxSurface *top,
                                    gxSurface *bottom,
                                    gxCube::GridSurface gridDefiningSurface,
                                    gxCube::SedimentationModel sedimentationModel)
{
    Q_UNUSED(top);
    Q_UNUSED(bottom);
    Q_UNUSED(gridDefiningSurface);
    Q_UNUSED(sedimentationModel);
}

//-------------------------------------------------------------------------------

QIcon gxCube::getIcon()
{
    return QIcon(":/images/soil_layers.png");
}



//-------------------------------------------------------------------------------

QMenu *gxCube::getMenu()
{
    return gxTreeMenuFabric::instance()->getCubeMenu(this);
}


//-------------------------------------------------------------------------------


void gxCube::draw3D()
{
    glLineWidth(1);

//    if (!gl_list_3d)
//    {
//        gl_list_3d = glGenLists(1);
//        glNewList(gl_list_3d, GL_COMPILE);

            drawSurface3D(topSurfase);
            drawSurface3D(bottomSurface);
            drawLateralSurface();

            // contours
//            glColor3f(0.0, 0.0, 0.0);

//            QListIterator<gxFlatContour*> it(*contours);
//            while (it.hasNext())
//            {
//                gxFlatContour* c = it.next();

//                glBegin(GL_LINE_STRIP);
//                    for(int i = 0; i < c->count(); ++i)
//                    {
//                        glVertex3d(c->at(i).x, c->at(i).y, c->getZ());
//                    }
////                    if (c->isClosed())
////                        glVertex3d(c->at(0).x, c->at(0).y, c->getZ());
//                glEnd();
//            }

//        glEndList();
//    }
//
//    glCallList(gl_list_3d);
//
//    glEnable(GL_DEPTH_TEST);
}

//------------------------------------------------------------------------------

void gxCube::drawSurface3D(gxSurfaceData *data)
{
    double d1, d2, d3, d4;

    for (int i = 0; i < data->nX()-1; ++i)
    {
        for (int j = 0; j < data->nY()-1; ++j)
        {
            d1 = data->at(i,  j);
            d2 = data->at(i+1,j);
            d3 = data->at(i+1,j+1);
            d4 = data->at(i,  j+1);

            if ((d1 != Gx::BlankDouble) &&
                (d2 != Gx::BlankDouble) &&
                (d3 != Gx::BlankDouble) &&
                (d4 != Gx::BlankDouble))
            {
                glColor3f(color.redF(), color.greenF(), color.blueF());
                glBegin(GL_QUADS);
                    gxSurfaceData::setNormal(data->getX(i+1) - data->getX(i), 0, d2 - d1, 0, data->getY(j+1) - data->getY(j), d4 - d1);
                    glVertex3d(data->getX(i),   data->getY(j),   d1);

                    gxSurfaceData::setNormal(0, data->getY(j+1) - data->getY(j), d3 - d2, data->getX(i) - data->getX(i+1), 0, d1 - d2);
                    glVertex3d(data->getX(i+1), data->getY(j),   d2);

                    gxSurfaceData::setNormal(data->getX(i) - data->getX(i+1), 0, d4 - d3, 0, data->getY(j) - data->getY(j+1), d2 - d3);
                    glVertex3d(data->getX(i+1), data->getY(j+1), d3);

                    gxSurfaceData::setNormal(0, data->getY(j) - data->getY(j+1), d1 - d4, data->getX(i+1) - data->getX(i), 0, d3 - d4);
                    glVertex3d(data->getX(i),   data->getY(j+1), d4);
                glEnd();



                /// grid lines
                glColor3d(0.4, 0.4, 0.4);
                glBegin(GL_LINES);
                    glVertex3d(data->getX(i),   data->getY(j),   d1);
                    glVertex3d(data->getX(i+1), data->getY(j),   d2);

                    glVertex3d(data->getX(i),   data->getY(j),   d1);
                    glVertex3d(data->getX(i),   data->getY(j+1), d4);
                glEnd();

            }
        }
    }
}


//------------------------------------------------------------------------------


void gxCube::drawLateralSurface()
{
    glColor3f(color.redF(), color.greenF(), color.blueF());

    // y == 0

    gxSize3D size = topSurfase->getSize();

    for(int i = 0; i < this->topSurfase->nX() - 1; ++i)
    {
        glBegin(GL_QUADS);
            glNormal3d(0.0, -1.0, 0.0);
            glVertex3d(topSurfase->getX(i),   size.getMinY(),   topSurfase->at(i, 0));

            glNormal3d(0.0, -1.0, 0.0);
            glVertex3d(topSurfase->getX(i),   size.getMinY(),   bottomSurface->at(i, 0));

            glNormal3d(0.0, -1.0, 0.0);
            glVertex3d(topSurfase->getX(i+1),   size.getMinY(),   bottomSurface->at(i+1, 0));

            glNormal3d(0.0, -1.0, 0.0);
            glVertex3d(topSurfase->getX(i+1),   size.getMinY(),   topSurfase->at(i+1, 0));
        glEnd();
    }


    // y == maxy

    for(int i = 0; i < this->topSurfase->nX() - 1; ++i)
    {
        glBegin(GL_QUADS);
            glNormal3d(0.0, +1.0, 0.0);
            glVertex3d(topSurfase->getX(i),   size.getMaxY(),   topSurfase->at(i, topSurfase->nY() - 1));

            glNormal3d(0.0, +1.0, 0.0);
            glVertex3d(topSurfase->getX(i),   size.getMaxY(),   bottomSurface->at(i, bottomSurface->nY() - 1));

            glNormal3d(0.0, +1.0, 0.0);
            glVertex3d(topSurfase->getX(i+1),   size.getMaxY(),   bottomSurface->at(i+1, topSurfase->nY() - 1));

            glNormal3d(0.0, +1.0, 0.0);
            glVertex3d(topSurfase->getX(i+1),   size.getMaxY(),   topSurfase->at(i+1, bottomSurface->nY() - 1));
        glEnd();
    }


    // x == 0


    for(int i = 0; i < this->topSurfase->nY() - 1; ++i)
    {
        glBegin(GL_QUADS);
            glNormal3d(-1.0, 0.0, 0.0);
            glVertex3d(size.getMinX(), topSurfase->getY(i),   topSurfase->at(0, i));

            glNormal3d(-1.0, 0.0, 0.0);
            glVertex3d(size.getMinX(), topSurfase->getY(i),   bottomSurface->at(0, i));

            glNormal3d(-1.0, 0.0, 0.0);
            glVertex3d(size.getMinX(), topSurfase->getY(i+1),   bottomSurface->at(0, i+1));

            glNormal3d(-1.0, 0.0, 0.0);
            glVertex3d(size.getMinX(), topSurfase->getY(i+1),   topSurfase->at(0, i+1));
        glEnd();
    }


    // x == maxx

    for(int i = 0; i < this->topSurfase->nY() - 1; ++i)
    {
        glBegin(GL_QUADS);
            glNormal3d(+1.0, 0.0, 0.0);
            glVertex3d(size.getMaxX(), topSurfase->getY(i), topSurfase->at(topSurfase->nX() - 1, i));

            glNormal3d(+1.0, 0.0, 0.0);
            glVertex3d(size.getMaxX(), topSurfase->getY(i), bottomSurface->at(bottomSurface->nX() - 1, i));

            glNormal3d(+1.0, 0.0, 0.0);
            glVertex3d(size.getMaxX(), topSurfase->getY(i+1), bottomSurface->at(bottomSurface->nX() - 1, i + 1));

            glNormal3d(+1.0, 0.0, 0.0);
            glVertex3d(size.getMaxX(), topSurfase->getY(i+1), topSurfase->at(topSurfase->nX() - 1, i + 1));
        glEnd();
    }


}
//------------------------------------------------------------------------------

void gxCube::recalcSize()
{
    size3d = topSurfase->getSize();
}


