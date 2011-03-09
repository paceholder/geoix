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

#include "project.h"
#include "mainwindow.h"

#include "render_panel_2D.h"
#include "render_panel_3D.h"

gxEngine* gxEngine::inst = NULL;



gxEngine::gxEngine()
{
    projectsRoot = new gxTreeFolderObject();
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

void gxEngine::createProject()
{
    // create shared poinder with project inside
    gxProject *project = new gxProject(projectsRoot);
    QSharedPointer<gxTreeAbstractObject> sharedPointer(project);
    projectsRoot->addChild(sharedPointer);

    // some stuff for adding to tree
    project->setup();
}



void gxEngine::deleteProject(gxProject* project)
{
    projectsRoot->deleteChild(project);
}

void gxEngine::deleteProject(int i)
{
    projectsRoot->deleteChild(i);
}



void gxEngine::create2DPanel()
{
    gxRenderPanel* panel = new gxRenderPanel2D(mainWindow->getMainPanel());
    panel->setVisible(true);

    this->panels.push_back(panel);

//    recheckTreeItems();
}

void gxEngine::create3DPanel()
{
    gxRenderPanel* panel = new gxRenderPanel3D(mainWindow->getMainPanel());
    panel->setVisible(true);

    this->panels.push_back(panel);

//    recheckTreeItems();
}


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

//    recheckTreeItems();

 //   if (i != panels.count()-1)
     //   panel->recreateDisplayLists();
}

gxRenderPanel* gxEngine::getTopLevelPanel()
{
    if (panels.count() > 0)
        return panels.last();
    else
        return NULL;
}

//
//void gxEngine::recheckTreeItems()
//{
//    QVariant data;
//    gxTreeObject* object;
//    QTreeWidgetItem *item;
//    gxVisualObject* vo;
//
//
//    gxRenderPanel* panel = this->getTopLevelPanel();
//    if (!panel) return;
//
//    QTreeWidgetItemIterator it(mainWindow->getProjectTree());
//
//    while (*it)
//    {
//        item = (*it);
//        ++it;
//
//        data = item->data(0, Qt::UserRole);
//        object = data.value<gxTreeObject*>();
//
//        if (object->isFolder()) continue;
//
//        vo = (gxVisualObject*)object;
//
//        if (panel->isObjectRegistered(vo))
//            item->setCheckState(0,Qt::Checked);
//        else
//            item->setCheckState(0,Qt::Unchecked);
//
//
//    }
//}
