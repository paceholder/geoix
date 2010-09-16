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


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QScreen>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileDialog>
// this is for actions for processing menu and toolbar events
#include <QActionGroup>
#include <QMessageBox>

#include "tree_object.h"
#include "tree_menu_fabric.h"
#include "render_panel.h"
#include "project_tree.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createGUIObjects();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createGUIObjects()
{
    // center window
//    QRect frect = frameGeometry();
//    frect.moveCenter(QDesktopWidget().availableGeometry().center());
//    move(frect.topLeft());

    projectTree = new gxProjectTree(ui->leftDock);
    projectTree->setContextMenuPolicy(Qt::CustomContextMenu);
    projectTree->header()->hide();

    ui->leftDock->setWidget(projectTree);
}


void MainWindow::createActions()
{
    actions.newProjectAct = new QAction(QIcon(":/images/Create.png"), tr("Create project"), this);
    actions.newProjectAct->setShortcuts(QKeySequence::New);
    //
    actions.new2DPanelAct = new QAction(QIcon(":/images/2D.png"), tr("New 2D Panel"), this);
    actions.new3DPanelAct = new QAction(QIcon(":/images/3D.png"), tr("New 3D Panel"), this);
    actions.closePanelAct = new QAction(QIcon(":/images/Delete_panel.png"), tr("Close Panel"), this);

    actions.screenShotAct = new QAction(QIcon(":/images/Screenshot.png"), tr("Make screenshot"), this);

    connect(actions.newProjectAct, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(actions.new2DPanelAct, SIGNAL(triggered()), this, SLOT(new2DPanel()));
    connect(actions.new3DPanelAct, SIGNAL(triggered()), this, SLOT(new3DPanel()));
    connect(actions.closePanelAct, SIGNAL(triggered()), this, SLOT(closePanel()));

    connect(actions.screenShotAct, SIGNAL(triggered()), this, SLOT(screenShot()));

    //
    // construct menu
    QMenu* menu;

    menu = this->menuBar()->addMenu(tr("&File"));
    menu->addAction(actions.newProjectAct);

    menu = this->menuBar()->addMenu(tr("&Objects"));

    menu = this->menuBar()->addMenu(tr("&Panels"));

    menu->addAction(actions.new2DPanelAct);
    menu->addAction(actions.new3DPanelAct);
    menu->addAction(actions.closePanelAct);

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


QTreeWidget* MainWindow::getProjectTree()
{
    return (QTreeWidget*)projectTree;
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


void MainWindow::screenShot()
{
    gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();
    if (panel)
    {
       //QPixmap p = panel->renderPixmap();

        QPixmap p = QPixmap::grabWindow(panel->getGLPanel()->winId());


        QString fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save Screenshot"), QDir::homePath(),
                                                tr("PGN files (*.png)"));

        p.save(fileName);
    }
}
