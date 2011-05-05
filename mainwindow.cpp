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


#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtGui>
#include <QtCore>

#include "tree_object.h"
#include "tree_menu_fabric.h"
#include "render_panel.h"

#include "project_tree_model.h"
#include "subtree_model.h"

#include "tree_abstract_object.h"

#include "spliner_dialog.h"
#include "cubedialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    splinerDialog(0),
    cubeDialog(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createGUIObjects();
    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow()
{
    if (splinerDialog) delete splinerDialog;
    delete ui;
}


void MainWindow::createGUIObjects()
{
    // center window
//    QRect frect = frameGeometry();
//    frect.moveCenter(QDesktopWidget().availableGeometry().center());
//    move(frect.topLeft());

    projectTreeModel = new gxProjectTreeModel(gxEngine::instance()->getProjectsRoot()/*, this*/);
    subtreeModel = new gxSubtreeModel();


    projectTree = new QTreeView(ui->leftDock);
    projectTree->header()->hide();
    projectTree->setContextMenuPolicy(Qt::CustomContextMenu);
    projectTree->setSelectionMode(QAbstractItemView::SingleSelection);
    projectTree->setDragEnabled(true);
    projectTree->setAcceptDrops(true);
    projectTree->setDropIndicatorShown(true);
    projectTree->setDragDropMode(QAbstractItemView::DragDrop);


    projectTree->setModel((QAbstractItemModel*)projectTreeModel);

    connect(projectTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuProjectTree(QPoint)));

    subTree = new QTreeView(ui->leftDock);
    subTree->header()->hide();
    subTree->setContextMenuPolicy(Qt::CustomContextMenu);
    subTree->setSelectionMode(QAbstractItemView::SingleSelection);
    subTree->setDragEnabled(true);
    subTree->setAcceptDrops(true);
    subTree->setDropIndicatorShown(true);
    subTree->setDragDropMode(QAbstractItemView::DragDrop);


    subTree->setModel((QAbstractItemModel*)subtreeModel);

    QWidget* dockWidget = new QWidget(ui->leftDock);
    QVBoxLayout* dockWidgetLayout = new QVBoxLayout(dockWidget);
    dockWidgetLayout->addWidget(projectTree);
    dockWidgetLayout->addWidget(subTree);
    dockWidgetLayout->setStretchFactor(projectTree, 3);
    dockWidgetLayout->setStretchFactor(subTree, 1);
    dockWidget->setLayout(dockWidgetLayout);

    ui->leftDock->setWidget(dockWidget);
}



//------------------------------------------------------------------------------


void MainWindow::createActions()
{
    actions.newProjectAct = new QAction(QIcon(":/images/Create.png"), tr("Create project"), this);
    actions.newProjectAct->setShortcuts(QKeySequence::New);
    actions.newProjectAct->setIconVisibleInMenu(true);
    //
    actions.new2DPanelAct = new QAction(QIcon(":/images/2D.png"), tr("New 2D Panel"), this);
    actions.new3DPanelAct = new QAction(QIcon(":/images/3D.png"), tr("New 3D Panel"), this);
    actions.closePanelAct = new QAction(QIcon(":/images/Delete_panel.png"), tr("Close Panel"), this);

    actions.buildMapAct = new QAction(QIcon(":/images/Create.png"), tr("Build Map"), this);

    actions.screenShotAct = new QAction(QIcon(":/images/Screenshot.png"), tr("Make screenshot"), this);

    actions.createCube = new QAction(QIcon(":/images/Box.png"), tr("Create Cube"), this);

    connect(actions.newProjectAct, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(actions.new2DPanelAct, SIGNAL(triggered()), this, SLOT(new2DPanel()));
    connect(actions.new3DPanelAct, SIGNAL(triggered()), this, SLOT(new3DPanel()));
    connect(actions.buildMapAct,   SIGNAL(triggered()), this, SLOT(buildMap()));
    connect(actions.closePanelAct, SIGNAL(triggered()), this, SLOT(closePanel()));

    connect(actions.screenShotAct, SIGNAL(triggered()), this, SLOT(screenShot()));
    connect(actions.createCube,    SIGNAL(triggered()), this, SLOT(createCube()));
}



//------------------------------------------------------------------------------



void MainWindow::createMenus()
{
    // construct menu
    QMenu* menu;

    menu = this->menuBar()->addMenu(tr("&File"));
    menu->addAction(actions.newProjectAct);

    menu = this->menuBar()->addMenu(tr("&Objects"));

    menu = this->menuBar()->addMenu(tr("&Panels"));
    menu->addAction(actions.new2DPanelAct);
    menu->addAction(actions.new3DPanelAct);
    menu->addAction(actions.closePanelAct);

    menu = this->menuBar()->addMenu(tr("&Tools"));
    menu->addAction(actions.buildMapAct);
    menu->addAction(actions.createCube);
}



//------------------------------------------------------------------------------



void MainWindow::createToolBars()
{
    ui->mainToolBar->addAction(actions.newProjectAct);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actions.new2DPanelAct);
    ui->mainToolBar->addAction(actions.new3DPanelAct);
    ui->mainToolBar->addAction(actions.closePanelAct);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(actions.screenShotAct);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


QTreeView* MainWindow::getProjectTree()
{
    return projectTree;
}

QTreeWidget* MainWindow::getSubTree()
{
    return (QTreeWidget*)subTree;
}

QWidget* MainWindow::getMainPanel()
{
    return ui->mainPanel;
}

QListWidget* MainWindow::getListLog()
{
    return ui->listLog;
}


//----------------------------------------------------------
// slots


void MainWindow::newProject()
{
    gxEngine::instance()->createProject();
}


void MainWindow::new2DPanel()
{
    gxEngine::instance()->create2DPanel();
}


void MainWindow::new3DPanel()
{
    gxEngine::instance()->create3DPanel();
}

void MainWindow::closePanel()
{
    gxEngine::instance()->closePanel();
}


//------------------------------------------------------------------------------



void MainWindow::screenShot()
{
    gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();
    if (panel)
    {
        // QPixmap p = panel->renderPixmap();

        QPixmap p = QPixmap::grabWindow(panel->getGLPanel()->winId());


        QString fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save Screenshot"), QDir::homePath(),
                                                tr("PGN files (*.png)"));

        p.save(fileName);
    }
}


//------------------------------------------------------------------------------



void MainWindow::buildMap()
{
    if (!splinerDialog) splinerDialog = new gxSplinerDialog(this);

    splinerDialog->show();
}


//------------------------------------------------------------------------------


void MainWindow::createCube()
{
    if (!cubeDialog) cubeDialog = new gxCubeDialog(this);

    cubeDialog->show();
}


//------------------------------------------------------------------------------



void MainWindow::contextMenuProjectTree(const QPoint& position)
{
    QPoint p = projectTree->mapToGlobal(position);
    // little offset to prevent clickin' menu by right mouse button
    p.setX( p.x()+ 5); p.setY( p.y() + 5);

    QModelIndex index = projectTree->indexAt(position);
    if (index.isValid())
    {
        gxTreeAbstractObject* object = static_cast<gxTreeAbstractObject*>(index.internalPointer());
        QMenu* menu = object->getMenu();
        if (menu) menu->popup(p);
    }
    else
    {
        gxTreeMenuFabric::instance()->getTreeGeneralMenu()->popup(p);
    }
}

