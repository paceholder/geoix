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
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------


#include "surface.h"

#undef min
#undef max
#include <limits>
#include "data_loader.h"
#include "data_exporter.h"
#include "contourer_fast.h"
#include "color_palette.h"
#include "tree_folder_object.h"

#include "surf_prop_dialog.h"

#include "logger.h"

#include <QMessageBox>


gxSurface::gxSurface(gxTreeFolderObject *parent, gxSurfaceData *d)
    : gxVisualObject(parent),
    data(d),
    contours(new gxFlatContourList)
{
    name = tr("New Surface");

    setRandomColor();
    setTransparancy(1.0);


    // Here we create class containing surface data
    if (!data)
        data = new gxSurfaceData(size3d);
    else
    {
        this->recalcSize();
        gxContourer contourer(this->size3d.getD()/10.0);
        contourer.run(this->data, this->contours);
    }

    // Color pallete for gradient fill
    palette = new gxContinuesColorPalette();
    palette->setColorInterpolationMode(gxContinuesColorPalette::HSL);
    palette->addColor(0,  Qt::darkBlue);
    palette->addColor(1,  Qt::red);


    gxLogger::instance()->logEvent("Surface '" + name + "' created");
}

gxSurface::~gxSurface()
{
    // delete contours
    foreach(gxFlatContour* contour, *contours)
    {
        delete contour;
    }
    delete contours;

    delete data;    
    delete palette;
}


//------------------------------------------------------------------------------

void gxSurface::draw2D()
{
    glLineWidth(1.0);    

    double d1, d2, d3, d4;

    double height = this->size3d.getD();
    double d;

    QColor c;

    if (!gl_list_2d)
    {
        gl_list_2d = glGenLists(1);
        glNewList(gl_list_2d, GL_COMPILE);

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
                        glBegin(GL_QUADS);
                            d = (d1 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);
                            glVertex2d(data->getX(i),   data->getY(j));


                            d = (d2 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);
                            glVertex2d(data->getX(i+1), data->getY(j));


                            d = (d3 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);
                            glVertex2d(data->getX(i+1), data->getY(j+1));

                            d = (d4 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);
                            glVertex2d(data->getX(i),   data->getY(j+1));
                        glEnd();

                    }
                }
            }


            // contours
            glColor4f(0.0, 0.0, 0.0, transparency);

            QListIterator<gxFlatContour*> it(*contours);
            while (it.hasNext())
            {
                gxFlatContour* c = it.next();

                glBegin(GL_LINE_STRIP);
                    for(int i = 0; i < c->count(); ++i)
                    {
                        glVertex2d(c->at(i).x, c->at(i).y);
                    }
        //                    if (c->isClosed())
        //                        glVertex3d(c->at(0).x, c->at(0).y, c->getZ());
                glEnd();
            }
        glEndList();
    }    

    glCallList(gl_list_2d);
}


//------------------------------------------------------------------------------


void gxSurface::draw3D()
{
    glLineWidth(1);

    if (transparency < 1)
        glDisable(GL_DEPTH_TEST);
    glColor4f(color.redF(), color.greenF(), color.blueF(), transparency);
    if (!gl_list_3d)
    {
        gl_list_3d = glGenLists(1);
        glNewList(gl_list_3d, GL_COMPILE);

            double d1, d2, d3, d4;

            double height = this->size3d.getD();
            double d;

            QColor c;


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
                        glBegin(GL_QUADS);
                            d = (d1 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);


                            gxSurfaceData::setNormal(data->getX(i+1) - data->getX(i), 0, d2 - d1, 0, data->getY(j+1) - data->getY(j), d4 - d1);
                            glVertex3d(data->getX(i),   data->getY(j),   d1);


                            d = (d2 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);

                            gxSurfaceData::setNormal(0, data->getY(j+1) - data->getY(j), d3 - d2, data->getX(i) - data->getX(i+1), 0, d1 - d2);
                            glVertex3d(data->getX(i+1), data->getY(j),   d2);


                            d = (d3 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);

                            gxSurfaceData::setNormal(data->getX(i) - data->getX(i+1), 0, d4 - d3, 0, data->getY(j) - data->getY(j+1), d2 - d3);
                            glVertex3d(data->getX(i+1), data->getY(j+1), d3);

                            d = (d4 - data->size3d.getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor4d(c.redF(), c.greenF(), c.blueF(), transparency);

                            gxSurfaceData::setNormal(0, data->getY(j) - data->getY(j+1), d1 - d4, data->getX(i+1) - data->getX(i), 0, d3 - d4);
                            glVertex3d(data->getX(i),   data->getY(j+1), d4);
                        glEnd();



                        /// grid lines
//                        glColor3d(0.4, 0.4, 0.4);
//                        glBegin(GL_LINES);
//                            glVertex3d(data->getX(i),   data->getY(j),   d1);
//                            glVertex3d(data->getX(i+1), data->getY(j),   d2);

//                            glVertex3d(data->getX(i),   data->getY(j),   d1);
//                            glVertex3d(data->getX(i),   data->getY(j+1), d4);
//                        glEnd();

                    }
                }
            }
            // contours
            glColor3f(0.0, 0.0, 0.0);

            QListIterator<gxFlatContour*> it(*contours);
            while (it.hasNext())
            {
                gxFlatContour* c = it.next();

                glBegin(GL_LINE_STRIP);
                    for(int i = 0; i < c->count(); ++i)
                    {
                        glVertex3d(c->at(i).x, c->at(i).y, c->getZ());
                    }
//                    if (c->isClosed())
//                        glVertex3d(c->at(0).x, c->at(0).y, c->getZ());
                glEnd();
            }

        glEndList();
    }

    glCallList(gl_list_3d);

    glEnable(GL_DEPTH_TEST);
}


//------------------------------------------------------------------------------

void gxSurface::recalcSize()
{
    recreateDisplayList();

    double maxdouble = std::numeric_limits<double>::max();
    if (data->values.count() > 0)
    {
        double minz = +maxdouble;
        double maxz = -maxdouble;

        QVectorIterator<double> it (data->values);
        while (it.hasNext())
        {
            double z = it.next();
            if (z == Gx::BlankDouble) continue;

            if (z < minz) minz = z;
            if (z > maxz) maxz = z;
        }

        this->data->size3d.setMinZ(minz);
        this->data->size3d.setMaxZ(maxz);
//        this->size3d.setMinZ(minz);
//        this->size3d.setMaxZ(maxz);

        if (data) this->size3d = data->size3d;
    }
}


//------------------------------------------------------------------------------


void gxSurface::setData(gxSurfaceData *d)
{
    if (data) delete data;
    data = d;

    recalcSize();
    gxContourer contourer(this->size3d.getD()/10.0);
    contourer.run(this->data, this->contours);
}

//------------------------------------------------------------------------------


void gxSurface::importFromFile()
{
    this->clearData();
    if ( ! gxDataLoader::loadSurfaceData(this->data)) return;

    this->recalcSize();    
    gxContourer contourer(this->size3d.getD()/10.0);
    contourer.run(this->data, this->contours);
}


//------------------------------------------------------------------------------


void gxSurface::exportToFile()
{
    gxDataExporter::exportSurfaceData(this->data);
}



//------------------------------------------------------------------------------


void gxSurface::clearData()
{
    data->clear();

//    foreach(gxFlatContour* contour, *contours)
//    {
//       // delete contour; todo
//    }
}


//------------------------------------------------------------------------------

void gxSurface::options()
{
    gxSurfaceOptionsDialog dialog(NULL);
    dialog.setData(this);

    dialog.exec();
}


QMenu* gxSurface::getMenu()
{
    return gxTreeMenuFabric::instance()->getSurfaceMenu(this);
}

QIcon gxSurface::getIcon()
{
    return QIcon(":/images/surface.png");
}
