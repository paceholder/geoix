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





#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "datamanager_global.h"

#include <Qt/QtCore>
#include <Qt/QtSql>

class DATAMANAGERSHARED_EXPORT gxDataManager {
public:
    gxDataManager();

    bool openBase();
    bool closeBase();

    bool isValid();
};


#define FILE_NOT_EXISTS -1



class gxGroup;
class gxDBObject;

//---------------------------------------------------------------------------------------


class gxDataBase
{
public:
    gxDataBase(QString& filename = "");

    int openFile(QString& filename);
    int createFile(QString& filename);
    int closeFile();

    /// Checks whether file containts all necessary tables;
    bool isValid();


    int groupCount();
    void addGroup(gxGroup* group);
    int deleteGroup(gxGroup* group);
    int deleteGroup(int i);




private:
    QList<gxGroup*> groups;


//    {
//        if (!QFile::exists(filename))
//            return FILE_NOT_EXISTS;
//    }

};


//---------------------------------------------------------------------------------------

/// Contains different objects
class gxGroup
{
public:
    /// could be created in memory
    gxGroup();
    ~gxGroup();


    /// checks if group is owned by some DB or not
    bool isLinkedwWithDB();

private:
    QList<gxDBObject*> dbobjects;

    gxDataBase* database;
};


class gxField
{
public:
    gxField();

    void operator<<(int value);
    void operator<<(double value);
    void operator<<(QString& value);

    int    getInt();
    double getDouble();
    QString& getString();

    QString& getName();
    QString& getUOM();

private:
    QString name;
    QString uom; //< units of measure


    int intValue;
    double dblValue;
    QString strValue;

};


#endif // DATAMANAGER_H
