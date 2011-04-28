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


#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <QtCore>




#include "point3D.h"
#include "contour.h"


class gxSurfaceData;


/// Class for importing data of surfaces and points from text files
class gxDataLoader : public QObject
{
    Q_OBJECT
public:
    /// This class is singletone0
    static gxDataLoader* instance()
    {
        if (!inst)
            inst = new gxDataLoader();

        return inst;
    }

    /// Loads points' data from txt file
    bool loadPointsData(gxPoint3DList* data);
    /// Loads surface's data from txt file
    bool  loadSurfaceData(gxSurfaceData* data);
    /// Loads lines' data from txt file
    bool loadLinesData(gxContourList* data);
private:
    /// Constructor
    gxDataLoader() {}

    /// Destructor
    ~gxDataLoader() {}

    /// Instance of this class (Singletone pattern)
    static gxDataLoader* inst;

    /// Opens text file and fill list. List must exist
    void openTextFile(QStringList* list);
};

#endif // DATA_LOADER_H
