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


#include "surface.h"

#include <limits>
#include "data_loader.h"
#include "contourer_fast.h"
#include "color_palette.h"
#include "tree_object_folder.h"

#include "surf_prop_dialog.h"

#include "logger.h"

#include <QMessageBox>


gxSurface::gxSurface(gxTreeObjectFolder* parent)
    : gxVisualObject(parent)
{
    name = tr("New Surface");

    parent->getTreeWidgetItem()->addChild(widgetItem);
    parent->getTreeWidgetItem()->setExpanded(true);

    widgetItem->setText(0, name);
    widgetItem->setIcon(0, QIcon(":/images/surface.png")); // todo

    setRandomColor();

    // Here we create class containing surface data
    data = new gxSurfaceData(&(this->size3d));
    // Contours filled after tracing
    contours = new gxFlatContours;

    // Color pallete for gradient fill
    palette = new gxContinuesColorPalette();
    palette->setColorInterpolationMode(gxContinuesColorPalette::HSL);
    palette->addColor(0,  Qt::darkBlue);
    palette->addColor(1,  Qt::red);

    updateWidgetItemState();

    Gx::Log("Surface '" + name + "' created");
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


//-------------------------------------------

void gxSurface::setNormal(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double x, y, z, l;

    x =   y1 * z2 - y2 * z1;
    y = - x1 * z2 + x2 * z1;
    z =   x1 * y2 - x2 * y1;

    l = sqrt(x*x + y*y + z*z);

    x /= l;
    y /= l;
    z /= l;

    glNormal3d(x, y, z);
}

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
                            d = (d1 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());
                            glVertex2d(data->getX(i),   data->getY(j));


                            d = (d2 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());
                            glVertex2d(data->getX(i+1), data->getY(j));


                            d = (d3 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());
                            glVertex2d(data->getX(i+1), data->getY(j+1));

                            d = (d4 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());
                            glVertex2d(data->getX(i),   data->getY(j+1));
                        glEnd();

                    }
                }
            }


            // contours
            glColor3f(0.0, 0.0, 0.0);

            QVectorIterator<gxFlatContour*> it(*contours);
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


void gxSurface::draw3D()
{
    glLineWidth(1);

    glColor3f(color.redF(), color.greenF(), color.blueF());
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


                            d = (d1 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());


                            setNormal(data->getX(i+1) - data->getX(i), 0, d2 - d1, 0, data->getY(j+1) - data->getY(j), d4 - d1);
                            glVertex3d(data->getX(i),   data->getY(j),   d1);


                            d = (d2 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());

                            setNormal(0, data->getY(j+1) - data->getY(j), d3 - d2, data->getX(i) - data->getX(i+1), 0, d1 - d2);
                            glVertex3d(data->getX(i+1), data->getY(j),   d2);


                            d = (d3 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());

                            setNormal(data->getX(i) - data->getX(i+1), 0, d4 - d3, 0, data->getY(j) - data->getY(j+1), d2 - d3);
                            glVertex3d(data->getX(i+1), data->getY(j+1), d3);

                            d = (d4 - data->size3d->getMinZ()) / height;
                            c = palette->getColor(d);
                            glColor3d(c.redF(), c.greenF(), c.blueF());

                            setNormal(0, data->getY(j) - data->getY(j+1), d1 - d4, data->getX(i+1) - data->getX(i), 0, d3 - d4);
                            glVertex3d(data->getX(i),   data->getY(j+1), d4);
                        glEnd();

                    }
                }
            }
            // contours
            glColor3f(0.0, 0.0, 0.0);

            QVectorIterator<gxFlatContour*> it(*contours);
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
}


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

        this->size3d.setMinZ(minz);
        this->size3d.setMaxZ(maxz);
    }
}


//--------------------------------


void gxSurface::importFromFile()
{
    this->clearData();
    gxDataLoader::instance()->loadSurfaceData(this->data);
    this->recalcSize();    

    gxContourer contourer(2);
    contourer.run(this->data, this->contours);

    updateWidgetItemState();
}


void gxSurface::clearData()
{
    data->clear();

    foreach(gxFlatContour* contour, *contours)
    {
       // delete contour; todo
    }

    updateWidgetItemState();
}

void gxSurface::options()
{
    gxSurfaceOptionsDialog dialog(NULL);

    dialog.exec();
}
