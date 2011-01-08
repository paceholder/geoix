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


#ifndef ENGINE_H
#define ENGINE_H


#include <QVector>
#include <QTreeWidgetItemIterator>
//#include <QStack>

#include "mainwindow.h"
#include "logger.h"
#include "project.h" // That would be good to delete it


class gxRenderPanel;


/// Central class. It's base of whole program
/*!
   Class contains main objects of class hierarhy
   such as render panels, main window etc.
*/
class gxEngine
{
public:
    /// Returns instance of singletone class
    static gxEngine* instance();

    /// Set pointer to the MainForm
    /// \return nothing
    void setMainWindow(MainWindow* w);

    /// Returns pointer to the main window
    /// \return MainWindow*
    MainWindow* getMainWindow() { return mainWindow; }

    /// returns list of projects
    gxProjectList* getProjectList() { return projects; }

    void createProject();
    void deleteProject(gxProject* project);

    void create2DPanel();
    void create3DPanel();
    void closePanel();

    /// Brings clicked panel to the front
    /// Moves pointer on it on the top of stack
    void raisePanel(gxRenderPanel* panel);

    /// Returns top panel from panels' stack
    /// if one exists
    gxRenderPanel* getTopLevelPanel();


    /// Function updates check states of all TreeWidgetItems
    /// \todo Bad solution. Think how to do it in better way
    /// \todo maybe i should megrge with test on data containing
    void recheckTreeItems();
private:
    /// Constructor
    gxEngine();
    /// Destructor
    ~gxEngine();


    static gxEngine* inst;
    MainWindow* mainWindow;

    /// List of projects
    /// \see gxProject
    gxProjectList* projects;

    /// Stack of panels
    /*!
        Vector containing all render panels
        both 2d and 3d.
    */
    QVector<gxRenderPanel*> panels;
};



#endif // ENGINE_H
