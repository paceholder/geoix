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


#include "data_loader.h"

#include "points.h"
#include "constants.h"
#include "surface_data.h"

#include "engine.h"

#include "mainwindow.h"

bool gxDataLoader::loadPointsData(gxPoint3DList* data)
{
    data->clear();

    QStringList list;
    openTextFile(list);
    if (list.count() <= 0) return false;

    QStringListIterator it(list);

    while (it.hasNext())
    {
        QString s = it.next();

        QRegExp re(" +"); // one or more spaces
        QStringList splitList = s.split(re, QString::SkipEmptyParts);

        if (splitList.count() != 3) continue;

        bool ok;

        double x = splitList[0].toDouble(&ok);
        if (!ok) continue;

        double y = splitList[1].toDouble(&ok);
        if (!ok) continue;

        double z = splitList[2].toDouble(&ok);
        if (!ok) continue;

        data->append(gxPoint3D(x, y, -z));
    }

    return true;
}



//------------------------------------------------------------------------------


bool gxDataLoader::loadSurfaceData(gxSurfaceData* data)
{
    data->values.clear();

    QRegExp re(", +");
    QStringList splitList;
    bool ok;

    QStringList list;
    openTextFile(list);
    if (list.count() <= 0) return false;

    QStringListIterator it(list);

    QString str;
    if (it.hasNext()) str = it.next();

    while ((str[0] != '@') && (it.hasNext()))
        str = it.next();

    // get blank value
    str = it.next();
    splitList = str.split(re, QString::SkipEmptyParts);

    double blank = splitList[1].toDouble(&ok);
    if (!ok) blank = Gx::BlankDouble;


    // get nx and ny
    str = it.next();

    splitList = str.split(re, QString::SkipEmptyParts);

    /// read NX and NY
    int nx = splitList[0].toInt(&ok);
    int ny = splitList[1].toInt(&ok);

    data->setnXY(ny, nx);

    QMutableVectorIterator<double> dit(data->values);
    while (dit.hasNext())
        dit.next() = Gx::BlankDouble;

    data->size3d = gxSize3D(splitList[2].toDouble(&ok),
                            splitList[4].toDouble(&ok),
                            0,
                            splitList[3].toDouble(&ok),
                            splitList[5].toDouble(&ok),
                            0);




    // read data

    str = it.next();

    while (it.hasNext() && (str[0] != '+'))
        str = it.next();


    re.setPattern(" +"); // one or more spaces

    int xi = 0, yi = data->nY()-1;
    bool stop = false;
    double d;

    str = it.next(); str = str.trimmed();
    while ( !str.isEmpty())
    {
        splitList = str.split(re, QString::SkipEmptyParts);

        for(int i = 0; i < splitList.count(); ++i)
        {
            d = splitList[i].toDouble(&ok);
            if (abs(d - Gx::BlankDouble) < Gx::Eps)
                d = Gx::BlankDouble;

            if (d != Gx::BlankDouble) d = -d;
            data->at(xi, yi) = d;
            --yi;

            if (yi == -1)
            {
                yi = data->nY()-1; ++xi; // nexr row of data grid
            }

            if (xi == data->nX())
            {
                stop = true;
                break;
            }

        }

        if (stop) break;


        if (!it.hasNext()) break;
        str = it.next(); str = str.trimmed();
    }

    return true;
}


//------------------------------------------------------------------------------



bool gxDataLoader::loadLinesData(gxContourList *data)
{
    foreach(gxContour* c, *data)
        delete c;


    data->clear();

    QRegExp re(" +");
    QStringList splitList;

    double x, y, z;
    bool ok;

    QStringList list;
    openTextFile(list);

    QStringListIterator it(list);
    QString str;

    gxContour* c = NULL;
    while(it.hasNext())
    {
        if (!c) c = new gxContour();
        str = it.next();

        splitList = str.split(re, QString::SkipEmptyParts);

        x = splitList[0].toDouble(&ok);
        if (!ok) continue;

        y = splitList[1].toDouble(&ok);
        if (!ok) continue;

        z = splitList[2].toDouble(&ok);
        if (!ok) continue;

        if ((qAbs(x - 999.0) < Gx::Eps) &&
            (qAbs(y - 999.0) < Gx::Eps) &&
            (qAbs(z - 999.0) < Gx::Eps))
        {
            data->append(c);
            c = NULL;
            continue;
        }        

        gxPoint3D p(x, y, -z);
        c->addPointBack(p);
    }

    return true;
}


//------------------------------------------------------------------------------

bool gxDataLoader::loadWellData(gxPoint3DList *data, QStringList list)
{
    data->clear();

    if (list.size() == 0)
    {
        openTextFile(list);
        if (list.count() <= 0) return false;
    }

    gxPoint3D origin;

    QStringListIterator it(list);

    /// get origin
    while (it.hasNext())
    {
        if (it.peekNext().contains("origin"))
        {
            QString s = it.next();

            int i = s.indexOf(':');
            s = s.remove(0, i + 1).trimmed(); // removes "origin :" then trim string

            QRegExp re("[\t ]+");

            QStringList originList = s.split(re, QString::SkipEmptyParts);

            if (originList.size() != 3) return false;

            bool okx, oky, okz;
            origin.x = originList[0].toDouble(&okx);
            origin.y = originList[1].toDouble(&oky);
            origin.z = originList[2].toDouble(&okz);

            if (!(okx && oky && okz)) return false;
            break;
        }

    }

    while (it.hasNext())
    {
        QString s = it.next();

        QRegExp re("[\t ]+"); // one or more tab or spaces
        QStringList splitList = s.split(re, QString::SkipEmptyParts);

        if (splitList.count() != 3) continue;

        bool okx, oky, okz;

        gxPoint3D p;
        p.x = splitList[0].toDouble(&okx);
        p.y = splitList[1].toDouble(&oky);
        p.z = splitList[2].toDouble(&okz);

        if (!(okx && oky && okz)) return false;

        p += origin;
        p.z = -p.z;

        data->append(p);
    }

    return true;
}

//------------------------------------------------------------------------------


bool gxDataLoader::loadWellsData(QList<gxPoint3DList> &wells, QStringList &names)
{
    wells.clear();
    names.clear();

    QStringList files = QFileDialog::getOpenFileNames(gxEngine::instance()->getMainWindow(),
                                                      QObject::tr("Open Several Files"),
                                                      QApplication::applicationDirPath(),
                                                      QObject::tr("Text Files (*)"));

    if (!files.size()) return false;

    foreach(QString fileName, files)
    {
        QStringList fileContant;
        openTextFile(fileContant, fileName);

        /// have some data
        if (fileContant.size())
        {
            gxPoint3DList points;
            loadWellData(&points, fileContant);
            wells.append(points);

            QFileInfo fileInfo(fileName);
            names.append(fileInfo.fileName());
        }
    }

    return true;
}

//------------------------------------------------------------------------------


void gxDataLoader::openTextFile(QStringList &list, QString fileName)
{
    list.clear();

    if (fileName.isEmpty())
        fileName = QFileDialog::getOpenFileName(gxEngine::instance()->getMainWindow(),
                                                QObject::tr("Open File"),
                                                QApplication::applicationDirPath(),
                                                QObject::tr("Text Files (*)"));

    if (QFile::exists(fileName))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        while (!in.atEnd())
        {
            list.append(in.readLine());
        }
    }
}


