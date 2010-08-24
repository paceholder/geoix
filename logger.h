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


#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QStringList>
#include <QVector>
#include <QTime>
#include <QListWidget>


enum gxLogEventType
{
    Event,
    Warning,
    Error
};

struct gxLogEntry
{
    gxLogEventType type;
    QString time;
    QString text;
};

class gxLogger : public QObject
{
    Q_OBJECT
public:
    static gxLogger* instance()
    {
        if (!inst)
        {
            inst = new gxLogger();
        }
        return inst;
    }

    void setOutputListWidget(QListWidget* listWidget);

    void logEvent(QString& s);
    void logWarning(QString& s) { s = "";}
    void logError(QString& s) { s = "";}

    void writeLogEntryToList(gxLogEntry& en);

private:
    gxLogger();
    ~gxLogger() {}

    static gxLogger* inst;

    QVector<gxLogEntry> list;
    QListWidget* listWidget;
};


namespace Gx
{
    static void Log(QString s)
    {
        gxLogger::instance()->logEvent(s);
    }
}

#endif // LOGGER_H
