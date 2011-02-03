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


#ifndef SURFACE_H
#define SURFACE_H

#include <QVector>

#include "visual_object.h"
#include "size.h"
#include "tree_menu_fabric.h"
#include "surface_data.h"
#include "flat_contour.h"
#include "constants.h"

// Predeclarations

class gxContinuesColorPalette;


/// 3D object which contains surface data and provide its rendering
/*!
    Suface data is contained in member data.
    gxContours is vector of gxContour*
*/
class gxSurface : public gxVisualObject
{
    Q_OBJECT
public:
    /// Constructor
    gxSurface(gxTreeFolderObject* parent);

    /// Destructor
    virtual ~gxSurface();

    /// Returns menu for project tree
    QMenu* getMenu();

    QIcon getIcon();

    virtual void draw2D();

    virtual void draw3D();

    virtual void recalcSize();


    /// Set normal for the given plane
    /*!
        Plane is represented by two vectors.
        Procedure calculates vector product of them,
        then normalizes obtained normal and set
        it usin' opengl function gxNormal3d()
    */
    void setNormal(double x1, double y1, double z1,
                   double x2, double y2, double z2);

    double getTransparency()
    {
        return this->transparency;
    }

    void setTransparancy(double value)
    {
        if ((value >=0) && (value <= 1))
            this->transparency = value;
    }

    inline bool hasData() { return (data->values.count() > 0); }


public slots:
    /// Calls appropriate functions from gxDataLoader to import data from txt file
    virtual void importFromFile();
    virtual void clearData();
    virtual void options();

private:
    gxSurfaceData* data;
    gxContinuesColorPalette* palette;

    gxFlatContours* contours;

    double transparency;
};


#endif // SURFACE_H
