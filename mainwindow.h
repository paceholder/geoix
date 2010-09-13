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


class gxProjectTree;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTreeWidget* getProjectTree();
    QWidget* getMainPanel();
    QListWidget* getListLog();

    gxMainWindowActions actions;

protected:
    void createGUIObjects();
    void createActions();

    void changeEvent(QEvent *event);
private:
    gxProjectTree* projectTree;
    QWidget* mainPanel;

    Ui::MainWindow *ui;
private slots:
    void newProject();
    void new2DPanel();
    void new3DPanel();
    void closePanel();
};

#endif // MAINWINDOW_H
