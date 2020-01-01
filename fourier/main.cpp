#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    srand(time(0));
    MainWindow mainwindow;
    mainwindow.show();

    return a.exec();
}
