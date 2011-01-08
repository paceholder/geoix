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


#include "data_loader.h"

#include "points.h"
#include "constants.h"

gxDataLoader* gxDataLoader::inst = NULL;

bool gxDataLoader::loadPointsData(gxPointsData* data)
{
    data->clear();

    QStringList list;
    openTextFile(&list);
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
    openTextFile(&list);
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

    int nx = splitList[0].toInt(&ok);
    int ny = splitList[1].toInt(&ok);

    data->setnXY(ny, nx);

    QMutableVectorIterator<double> dit(data->values);
    while (dit.hasNext())
        dit.next() = Gx::BlankDouble;

    data->size3d->setSize(splitList[2].toDouble(&ok),
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



bool gxDataLoader::loadLinesData(gxContours *data)
{
    foreach(gxContour* c, *data)
        delete c;


    data->clear();

    QRegExp re(" +");
    QStringList splitList;

    double x, y, z;
    bool ok;

    QStringList list;
    openTextFile(&list);

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


void gxDataLoader::openTextFile(QStringList* list)
{
    if (!list) return;

    list->clear();

    QString fileName = QFileDialog::getOpenFileName(gxEngine::instance()->getMainWindow(),
                                            tr("Open File"), QDir::homePath(),
                                            tr("Text Files (*)"));

    if (QFile::exists(fileName))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        while (!in.atEnd())
        {
            list->append(in.readLine());
        }
    }
}
