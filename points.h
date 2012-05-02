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


#ifndef POINTS_H
#define POINTS_H

#include <QVector>


#include "visual_object.h"
#include "point_nd.h"

class gx3dScene;
class gxTreeFolderObject;

/// Class represents visual object points in 3d space
class gxPoints : public gxVisualObject
{
    Q_OBJECT
public:
    /// Constructor
    gxPoints(gxTreeFolderObject* parent);

    /// Destructor
    virtual ~gxPoints()    {}

    /// Recalculates 3d size of containing object
    virtual void recalcSize();

    /// Returns context menu for current object
    QMenu* getMenu();

    /// Returns icon for the points
    QIcon getIcon();

    /// 2d rendering
    virtual void draw2D();

    /// 3d rendering
    virtual void draw3D();

    /// mime type
    virtual QString getMimeType() { return QString("geoix/points"); }

    /// Checks whether object has data
    bool hasData() { return data.count() > 0; }

    gxPoint3DList getPoint3DList()
    {
        return this->data;
    }

public slots:
    /// Calls appropriate functions from gxDataLoader to import data from txt file
    virtual void importFromFile();
    /// Clears data container
    virtual void clearData();
    /// Will call options form
    virtual void options() {}

private:
    gxPoint3DList data; // todo: pointer of reference?

};

#endif // POINTS_H
