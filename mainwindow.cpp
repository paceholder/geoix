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


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QScreen>
#include <QDesktopWidget>

// this is for actions for processing menu and toolbar events
#include <QActionGroup>


#include <QMessageBox>

#include "tree_object.h"
#include "tree_menu_fabric.h"
#include "render_panel.h"

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
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    ui->projectTree->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->projectTree->header()->hide();

    ui->leftDock->setLayout(ui->verticalLayout);

    connect(ui->projectTree, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(treeContextMenu(const QPoint&)));

    connect(ui->projectTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
        this, SLOT(treeItemDoubleClicked(QTreeWidgetItem*,int)));

    connect(ui->projectTree, SIGNAL(itemChanged(QTreeWidgetItem*,int)),
        this, SLOT(treeItemChanged(QTreeWidgetItem*,int)));


}


void MainWindow::createActions()
{
    actions.newProjectAct = new QAction(QIcon(":/images/Create.png"), tr("Create project"), this);
    actions.newProjectAct->setShortcuts(QKeySequence::New);
    //
    actions.new2DPanelAct = new QAction(QIcon(":/images/2D.png"), tr("New 2D Panel"), this);
    actions.new3DPanelAct = new QAction(QIcon(":/images/3D.png"), tr("New 3D Panel"), this);
    actions.closePanelAct = new QAction(QIcon(":/images/Delete_panel.png"), tr("Close Panel"), this);


    connect(actions.newProjectAct, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(actions.new2DPanelAct, SIGNAL(triggered()), this, SLOT(new2DPanel()));
    connect(actions.new3DPanelAct, SIGNAL(triggered()), this, SLOT(new3DPanel()));
    connect(actions.closePanelAct, SIGNAL(triggered()), this, SLOT(closePanel()));

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
    return ui->projectTree;
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


void MainWindow::treeContextMenu(const QPoint& point)
{
    QTreeWidgetItem* item =  ui->projectTree->itemAt(point);

    QPoint p = ui->projectTree->mapToGlobal(point);

    // little offset to prevent clickin' menu by right mouse button
    p.setX( p.x()+ 5); p.setY( p.y() + 5);

    if (item)
    {
        QVariant data = item->data(0, Qt::UserRole);


        gxTreeObject* object = data.value<gxTreeObject*>();

        QMenu* menu = object->getMenu();
        if (menu)
            menu->popup(p);
    }
    else
    {
        gxTreeMenuFabric::instance()->getTreeGeneralMenu()->popup(p);
    }
}



void MainWindow::treeItemChanged(QTreeWidgetItem *item, int column)
{
    if (!item) return;

    // change name of object

    QVariant data = item->data(column, Qt::UserRole);
    gxTreeObject* object = data.value<gxTreeObject*>();

    if (!object) return;

    QString s = item->text(0);
    object->setName(s);



    // set visibility/invisibility

    if (!object->isFolder())
    {
        gxVisualObject* vo = (gxVisualObject*)object;

        gxRenderPanel* panel = gxEngine::instance()->getTopLevelPanel();

        if (!panel) return;

        switch (item->checkState(0))
        {
        case Qt::Checked:
            panel->registerObject(vo);
            break;
        case Qt::Unchecked:
            panel->unregisterObject(vo);
            break;
        case Qt::PartiallyChecked: break;
        }
    }
}






