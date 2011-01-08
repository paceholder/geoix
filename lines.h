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


#ifndef LINES_H
#define LINES_H

#include "visual_object.h"
#include "contour.h"
#include "tree_folder_object.h"


/// Class represents lines in 3d space
/*!
    In fact its wrapper over gxContours.
*/
class gxLines : public gxVisualObject
{
    Q_OBJECT
public:
    /// Constructor
    gxLines(gxTreeFolderObject* parent);

    /// Destructor
    virtual ~gxLines();

    /// Returns menu for project tree
    QMenu* getMenu();

    QIcon getIcon();

    /// 2d rendering
    virtual void draw2D();

    /// 3d rendering
    virtual void draw3D();

    /// No comments
    virtual void recalcSize();

public slots:
/// Calls appropriate functions from gxDataLoader to import data from txt file
    virtual void importFromFile();
    virtual void clearData();
    virtual void options() {}

protected:
    bool hasData() { return contours->count() > 0; }
private:
    /// Vector of contours containing data of current gxLines
    gxContours* contours;

};

#endif // LINES_H
