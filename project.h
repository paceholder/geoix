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


#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>

#include "tree_folder_object.h"
#include "logger.h"


/// Represents project in project tree in Main Window
class gxProject : public gxTreeFolderObject
{
    Q_OBJECT
public:
    gxProject();
    virtual ~gxProject();

    /// This function adds item to the project list
    void setup();

    virtual QMenu* getMenu();
    virtual QIcon getIcon();
};

typedef QList<gxProject*> gxProjectList;

#endif // PROJECT_H
