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


#include "logger.h"

gxLogger* gxLogger::inst = NULL;


gxLogger::gxLogger()
{
    listWidget = NULL;
}


void gxLogger::logEvent(QString& s)
{
    gxLogEntry entry;
    entry.time = QTime::currentTime().toString(Qt::TextDate);
    entry.text = s;
    entry.type = Event;

    list.append(entry);
    writeLogEntryToList(entry);
}

void gxLogger::setOutputListWidget(QListWidget* listWidget)
{
    this->listWidget = listWidget;
}


void gxLogger::writeLogEntryToList(gxLogEntry& en)
{
    if (listWidget)
    {
        QListWidgetItem* item = new QListWidgetItem;

        switch (en.type)
        {
        case Event: item->setTextColor(QColor(50, 150, 50, 255)); break;
        case Warning: item->setTextColor(Qt::yellow); break;
        case Error: item->setTextColor(Qt::red); break;
        }

        item->setText(en.time + '\t' + en.text);
        listWidget->addItem(item);
    }
}
