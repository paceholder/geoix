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


#ifndef MAINWINDOW_ACTIONS_H
#define MAINWINDOW_ACTIONS_H


#include <QAction>

/// Contains all actions for toolbars and menus of Main Window
struct gxMainWindowActions
{
    QAction* newProjectAct;
    QAction* saveProjectAct;

    QAction* new2DPanelAct;
    QAction* new3DPanelAct;
    QAction* closePanelAct;

    QAction* buildMapAct;

    QAction* screenShotAct;
};



#endif // MAINWINDOW_ACTIONS_H
