#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "welldata.h"
#include "fourierinterpolator.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    Ui::MainWindow *ui;
    QList<WellData> wells;

    FourierInterpolator FI;

    QVector<double> values;

    QPoint mousepos;

    void drawMap(QEvent *event);
    void drawWells();
    void drawResultWell();

    void exportSurfaceData(QVector<double> data);
    void saveToTextFile(QStringList &list);

public slots:
    void generateWells();
    void saveSection();
};

#endif // MAINWINDOW_H
