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


#include <QtGui/QApplication>


#include "mainwindow.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    gxEngine::instance()->setMainWindow(&w);

    w.setWindowState(w.windowState() ^ Qt::WindowMaximized);
    w.show();
    return a.exec();
}
