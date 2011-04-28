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


#include "engine.h"
#include "lines.h"
#include "project.h"
#include "points.h"
#include "surface.h"

#include "mainwindow.h"

#include "render_panel_2D.h"
#include "render_panel_3D.h"

gxEngine* gxEngine::inst = NULL;



gxEngine::gxEngine()
{
    projectsRoot = new gxTreeFolderObject();
    projectsRoot->setName("Projects Root");
}

gxEngine::~gxEngine()
{
    delete projectsRoot;
}

//------------------------------------------------------------------------------

gxEngine* gxEngine::instance()
{
    if (!inst)
        inst = new gxEngine();

    return inst;
}

void gxEngine::setMainWindow(MainWindow* w)
{
    mainWindow = w;

    gxLogger::instance()->setOutputListWidget(w->getListLog());
}

//------------------------------------------------------------------------------

void gxEngine::createProject()
{
    // create shared poinder with project inside
    gxProject *project = new gxProject(projectsRoot);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(project);
    projectsRoot->addChild(sharedPointer);

    // some stuff for adding to tree
    project->setup();
}

//------------------------------------------------------------------------------

void gxEngine::deleteProject(gxProject* project)
{
    projectsRoot->deleteChild(project);
}


//------------------------------------------------------------------------------

void gxEngine::deleteProject(int i)
{
    projectsRoot->deleteChild(i);
}

//------------------------------------------------------------------------------


QSharedPointer<gxTreeAbstractObject> gxEngine::createFolder(gxTreeFolderObject* parent)
{
    // creation of new object
    gxTreeFolderObject* folder = new gxTreeFolderObject(parent);

    // creation of sharedPointer from gxTreeFolderObject*
    QSharedPointer<gxTreeAbstractObject> sharedPointer(folder);

    // adding new folder to children
    folder->addChild(sharedPointer);

    // append new item to the model
    folder->setup();

    return sharedPointer;
}

QSharedPointer<gxTreeAbstractObject> gxEngine::createPoints(gxTreeFolderObject* parent)
{
    gxPoints* points = new gxPoints(parent);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(points);
    parent->addChild(sharedPointer);

    points->update();

    return sharedPointer;
}

QSharedPointer<gxTreeAbstractObject> gxEngine::createLines(gxTreeFolderObject* parent)
{
    gxLines* lines = new gxLines(parent);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(lines);
    parent->addChild(sharedPointer);

    lines->update();

    return sharedPointer;
}

QSharedPointer<gxTreeAbstractObject> gxEngine::createSurface(gxTreeFolderObject* parent)
{
    gxSurface* surface = new gxSurface(parent);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(surface);
    parent->addChild(sharedPointer);

    surface->update();

    return sharedPointer;
}

//------------------------------------------------------------------------------

void gxEngine::create2DPanel()
{
    gxRenderPanel* panel = new gxRenderPanel2D(mainWindow->getMainPanel());
    panel->setVisible(true);

    this->panels.push_back(panel);

//    recheckTreeItems();
}

//------------------------------------------------------------------------------

void gxEngine::create3DPanel()
{
    gxRenderPanel* panel = new gxRenderPanel3D(mainWindow->getMainPanel());
    panel->setVisible(true);

    this->panels.push_back(panel);

//    recheckTreeItems();
}

//------------------------------------------------------------------------------


void gxEngine::closePanel()
{
    if (!panels.isEmpty())
    {
        gxRenderPanel* panel = panels.last();
        delete panel;
        panels.pop_back();
    }

//    recheckTreeItems();
}


void gxEngine::raisePanel(gxRenderPanel* panel)
{
    int i = panels.indexOf(panel);

    if (i >= 0)
    {
        gxRenderPanel* panel = panels[i];
        panels.remove(i);
        panels.push_back(panel);
    }
}


//------------------------------------------------------------------------------

gxRenderPanel* gxEngine::getTopLevelPanel()
{
    if (panels.count() > 0)
        return panels.last();
    else
        return NULL;
}
