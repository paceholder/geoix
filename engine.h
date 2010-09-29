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


#ifndef ENGINE_H
#define ENGINE_H


#include <QVector>
#include <QTreeWidgetItemIterator>
//#include <QStack>

#include "mainwindow.h"
#include "logger.h"

class gxProject;
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
    static gxEngine* instance()
    {
        if (!inst)
        {
            inst = new gxEngine();
        }
        return inst;
    }

    /// Set pointer to the MainForm
    /// \return nothing
    void setMainWindow(MainWindow* w)
    {
        mainWindow = w;

        gxLogger::instance()->setOutputListWidget(w->getListLog());

    }

    /// Returns pointer to the main window
    /// \return MainWindow*
    inline MainWindow* getMainWindow() { return mainWindow; }

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
private:
    /// Constructor
    gxEngine() {}
    /// Destructor

    // ??????
    ~gxEngine()
    {
//        foreach(gxRenderPanel* panel, panels)
//        {
//            delete panel;
//        }

    }

    static gxEngine* inst;
    MainWindow* mainWindow;

    /// Vector of projects
    /// \see gxProject
    QVector<gxProject*> projects;

    /// Stack of panels
    /*!
        Vector containing all render panels
        both 2d and 3d.
    */
    QVector<gxRenderPanel*> panels;


    /// Function updates check states of all TreeWidgetItems
    /// \todo Bad solytion. Think how to do it in better way
    void recheckTreeItems();
};



#endif // ENGINE_H
