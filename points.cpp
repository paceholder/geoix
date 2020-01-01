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


#include "points.h"

#include <GL/glu.h>
#undef min
#undef max
#include <limits>
#include "data_loader.h"
#include "tree_folder_object.h"
#include "tree_menu_fabric.h"




gxPoints::gxPoints(gxTreeFolderObject* parent)
    : gxVisualObject(parent)
{
    name = tr("New Points");

    setRandomColor();
}


void gxPoints::recalcSize()
{
    recreateDisplayList();

    // default size
    this->size3d.setSize(-50, -50, -50, 50, 50, 50);

    if (data.count() > 0)
    {
        double maxdouble = std::numeric_limits<double>::max();

        gxSize3D size( maxdouble,  maxdouble,  maxdouble,
                      -maxdouble, -maxdouble, -maxdouble);

        QListIterator<gxPoint3D> it (data);
        while (it.hasNext())
        {
            gxPoint3D const & p = it.next();

            if (p.x() < size.getMinX()) size.setMinX(p.x());
            if (p.x() > size.getMaxX()) size.setMaxX(p.x());

            if (p.y() < size.getMinY()) size.setMinY(p.y());
            if (p.y() > size.getMaxY()) size.setMaxY(p.y());

            if (p.z() < size.getMinZ()) size.setMinZ(p.z());
            if (p.z() > size.getMaxZ()) size.setMaxZ(p.z());
        }

        this->size3d.setSize(size);
    }
}


//------------------------------------------------------------------------------


void gxPoints::draw2D()
{
    int d = (qMin(size3d.getW(), size3d.getH())/150);

    glColor3f(color.redF(), color.greenF(), color.blueF());
    if (!gl_list_2d)
    {
        GLUquadricObj* quadObj;
        quadObj = gluNewQuadric();
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluQuadricDrawStyle(quadObj, GLU_FILL);

        gl_list_2d = glGenLists(1);
        glNewList(gl_list_2d, GL_COMPILE);

            QListIterator<gxPoint3D> it(this->data);

            while(it.hasNext())
            {
                gxPoint3D const & p = it.next();
                glPushMatrix();
                    glTranslatef(p.x(), p.y(), 0);
                    gluDisk(quadObj, 0, d, 10, 3);
                glPopMatrix();
            }

        glEndList();

        gluDeleteQuadric(quadObj);
    }

    glCallList(gl_list_2d);
}


//------------------------------------------------------------------------------


void gxPoints::draw3D()
{
    int d = (qMin(size3d.getW(), size3d.getH())/100);

    if (!gl_list_3d)
    {
        GLUquadricObj* quadObj;
        quadObj = gluNewQuadric();
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluQuadricDrawStyle(quadObj, GLU_FILL);

        gl_list_3d = glGenLists(1);
        glNewList(gl_list_3d, GL_COMPILE);

            QListIterator<gxPoint3D> it(this->data);

            while(it.hasNext())
            {
                gxPoint3D const & p = it.next();
                glPushMatrix();
                    glTranslatef(p.x(), p.y(), p.z());

                    glColor3f(color.redF(), color.greenF(), color.blueF());
                    gluDisk(quadObj, 0, d, 10, 3);

                    glColor3f(1.0, 1.0, 1.0);
                    gluDisk(quadObj, d * 1.1, d * 1.2, 10, 3);

//                    glColor3f(0.0, 0.0, 0.0);
//                    gluDisk(quadObj, d+11, d+15, 10, 3);


                glPopMatrix();
            }

        glEndList();

        gluDeleteQuadric(quadObj);
    }

    glCallList(gl_list_3d);
}


//-----------

void gxPoints::importFromFile()
{
    gxDataLoader::loadPointsData(&(this->data));
    this->recalcSize();

//    updateWidgetItemState();
}

void gxPoints::clearData()
{
    data.clear();

//    updateWidgetItemState();
}


QMenu* gxPoints::getMenu()
{
    return gxTreeMenuFabric::instance()->getPointsMenu(this);
}

QIcon gxPoints::getIcon()
{
    return QIcon(":/images/points.png");
}
