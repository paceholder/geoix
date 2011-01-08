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


#include "project.h"

#include "tree_menu_fabric.h"
#include "project_tree_model.h"
#include "engine.h"

gxProject::gxProject()
    : gxTreeFolderObject()
{
   name = tr("New Project");
}


gxProject::~gxProject()
{
    gxEngine::instance()->deleteProject(this);
}

void gxProject::setup()
{
    gxProjectList* projectList = gxEngine::instance()->getProjectList();
    QAbstractItemModel* model = gxEngine::instance()->getMainWindow()->getProjectTreeModel();

    model->insertRow(projectList->size() - 1, QModelIndex());

    Gx::Log("Project '" + name + "' created");
}


QMenu* gxProject::getMenu()
{
    return gxTreeMenuFabric::instance()->getProjectMenu(this);
}

QIcon gxProject::getIcon()
{
    return QIcon(":/images/Hierarchy.png");
}

