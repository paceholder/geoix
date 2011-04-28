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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTreeWidget>
#include <QListWidget>

#include "mainwindow_actions.h"

namespace Ui {
    class MainWindow;
}


//class gxProjectTree;
class gxSubTree;
class gxProjectTreeModel;
class gxSubtreeModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// Returns Project Tree
    QTreeView* getProjectTree();
    /// Returns Sub Tree
    QTreeWidget* getSubTree();    
    /// Returns Main Panel
    QWidget* getMainPanel();
    /// Returns widget with log
    QListWidget* getListLog();

    /// Group Of Actions of Main Window
    gxMainWindowActions actions;

protected:
    /// Creates all GUI widgets
    void createGUIObjects();
    /// Creates actions of Main Window
    void createActions();
    /// Creates menus of Main Window
    void createMenus();
    /// Creates toolbars of Main Window
    void createToolBars();

    /// It seem to be necessary for changing of teh language
    void changeEvent(QEvent *event);
private:
    /// Project Tree (view)
    QTreeView* projectTree;

    /// Model of Project Tree
    gxProjectTreeModel *projectTreeModel;

    /// Subtree model
    gxSubtreeModel *subtreeModel;

    /// Subtree. It works as Additional Buffer
    QTreeView* subTree;

    /// Main Panel. Contains rendering widgets
    QWidget* mainPanel;

    Ui::MainWindow *ui;
private slots:
    void newProject();
    void new2DPanel();
    void new3DPanel();
    void closePanel();
    void buildMap();
    void createCube();
    void screenShot();
    void contextMenuProjectTree(const QPoint& position);
};

#endif // MAINWINDOW_H
