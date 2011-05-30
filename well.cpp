#include "well.h"

#undef max
#undef min
#include <limits>

#include "tree_menu_fabric.h"
#include "data_loader.h"


gxWell::gxWell(gxTreeFolderObject *parent)
    : gxVisualObject(parent)
{
    name = tr("Well");

    setRandomColor();
}

gxWell::~gxWell() {}

//------------------------------------------------------------------------------

QIcon gxWell::getIcon()
{
    return QIcon(":/images/well.png");
}

QMenu *gxWell::getMenu()
{
    return gxTreeMenuFabric::instance()->getWellMenu(this);
}


//------------------------------------------------------------------------------


void gxWell::draw2D()
{
    glLineWidth(2);
    glColor3f(color.redF(), color.greenF(), color.blueF());

    GLUquadricObj* quadObj;
    quadObj = gluNewQuadric();
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricDrawStyle(quadObj, GLU_FILL);

    QListIterator<gxPoint3D> it(this->data);

    while(it.hasNext())
    {
        gxPoint3D p = it.next();
        glPushMatrix();
            glTranslatef(p.x, p.y, 0);
            gluDisk(quadObj, 0, 5, 20, 20);
        glPopMatrix();
    }

    it.toFront();
    glBegin(GL_LINE_STRIP);
        while(it.hasNext())
        {
            gxPoint3D p = it.next();
            glVertex3d(p.x, p.y, 0);
        }
    glEnd();

    glEndList();

    gluDeleteQuadric(quadObj);
    glLineWidth(1);
}

//------------------------------------------------------------------------------

void gxWell::draw3D()
{
    glLineWidth(2);

    glColor3f(color.redF(), color.greenF(), color.blueF());

    GLUquadricObj* quadObj;
    quadObj = gluNewQuadric();
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricDrawStyle(quadObj, GLU_FILL);

    QListIterator<gxPoint3D> it(this->data);

    while(it.hasNext())
    {
        gxPoint3D p = it.next();
        glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            gluSphere(quadObj, 5, 10, 10);
        glPopMatrix();
    }

    it.toFront();
    glBegin(GL_LINE_STRIP);
        while(it.hasNext())
        {
            gxPoint3D p = it.next();
            glVertex3d(p.x, p.y, p.z);
        }
    glEnd();

    glEndList();

    gluDeleteQuadric(quadObj);
    glLineWidth(1);
}


//------------------------------------------------------------------------------

void gxWell::recalcSize()
{
//    recreateDisplayList();

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
            gxPoint3D p = it.next();

            if (p.x < size.getMinX()) size.setMinX(p.x);
            if (p.x > size.getMaxX()) size.setMaxX(p.x);

            if (p.y < size.getMinY()) size.setMinY(p.y);
            if (p.y > size.getMaxY()) size.setMaxY(p.y);

            if (p.z < size.getMinZ()) size.setMinZ(p.z);
            if (p.z > size.getMaxZ()) size.setMaxZ(p.z);
        }

        this->size3d.setSize(size);
    }
}



//------------------------------------------------------------------------------



void gxWell::addCurve(gxCurve curve)
{
    curves.append(curve);
}


//                              slots
//------------------------------------------------------------------------------

void gxWell::importFromFile()
{
    QString name;
    gxDataLoader::loadWellData(&data);
    this->setName(name);
    this->recalcSize();

}
