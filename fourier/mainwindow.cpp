#include "mainwindow.h"

#include "ui_mainwindow.h"
#include <QtGui>

#include "../point3D.h"

MainWindow::MainWindow()
    : ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mapWidget->installEventFilter(this);
    ui->wellsWidget->installEventFilter(this);
    ui->resultWellWidget->installEventFilter(this);
    ui->mapWidget->installEventFilter(this);
    ui->mapWidget->setMouseTracking(true);


    generateWells();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------------------------------------------------------------------------


void MainWindow::generateWells()
{
    values.clear();
    wells.clear();
    for(int i = 0; i < 2; ++i)
    {
        wells.append(WellData());
    }
    FI.interpolate(wells);

    this->ui->wellsWidget->repaint();
    this->ui->mapWidget->repaint();
}

//------------------------------------------------------------------------------


void MainWindow::saveSection()
{
    // only 2 poins are considered
    if (wells.size() != 2 ) return;

    if (!values.size()) return;

    double dist = gxPoint3D(wells[0].X, wells[0].Y).distance2D(wells[1].X, wells[1].Y);
    double k = (wells[1].Y - wells[0].Y)/(wells[1].X - wells[0].X);
    double stepx = (wells[1].X - wells[0].X)/(values.size() - 1);
    double stepy = (wells[1].Y - wells[0].Y)/(values.size() - 1);

    QVector<double> data(values.size() * (values.size() + 1));

    // horizontal
    for(int i = 0; i <= values.size(); ++i)
    {
        QVector<double> v = FI.getInterpolatedValue(wells,
                                                    wells[0].X + stepx * i,
                                                    wells[0].Y + stepy * i);
        // vertical
        for(int j = 0; j < values.size(); ++j)
        {
            data[j * (values.size() + 1) + i] = v[values.size() - 1 - j];
        }
    }

    exportSurfaceData(data);
}


void MainWindow::saveToTextFile(QStringList &list)
{
    QString fileName = QFileDialog::getSaveFileName(0,
                                                    QObject::tr("Save File"),
                                                    QApplication::applicationDirPath(),
                                                    QObject::tr("Text Files (*)"));

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    foreach(QString line, list)
        in << line;
}

//------------------------------------------------------------------------------

void MainWindow::exportSurfaceData(QVector<double> data)
{
    QStringList list;

    list << "!  GEOIX" << "\n";
    list << "!  SURFACE FILE" << "\n";
    list << "@Surf_Zmap HEADER                     ,      GRID,       5" << "\n";
    list << "      15," + QString::number(-999) + ", , 4, 1" << "\n";
    list << QString("%1, %2, %3, %4, %5, %6").arg(QString::number(values.size()),
                                                  QString::number(values.size() + 1),
                                                  QString::number(0),
                                                  QString::number(1),
                                                  QString::number(0),
                                                  QString::number(1))  << "\n";

    list << "         0.0000,         0.0000,         0.0000" << "\n";
    list << "@" << "\n";
    list << "+ Grid data starts after this line" << "\n";

    int n = 0;
    QString s;
    for(int i = 0; i < values.size() + 1; ++i)
        for(int j = values.size() - 1; j >= 0; --j)
        {
            s += " " + QString::number(data[j * (values.size() + 1) + i]);
            ++n;
            if (n > 5)
            {
                list << s << "\n";
                s.clear();
                n = 0;
            }
        }

    list << s << "\n";

    saveToTextFile(list);
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->mapWidget)
    {
        if (event->type() == QEvent::Paint)
        {
            event->accept();
            drawMap(event);
            return true;
        }
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
            double x = mevent->x() / double(ui->mapWidget->width());
            double y = mevent->y() / double(ui->mapWidget->height());
            values = FI.getInterpolatedValue(wells, x, y);
            ui->wellsWidget->repaint();
            ui->resultWellWidget->repaint();
            event->accept();
            return true;
        }
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
            if (mevent->buttons() & Qt::LeftButton)
            {
                double x = mevent->x() / double(ui->mapWidget->width());
                double y = mevent->y() / double(ui->mapWidget->height());

                mousepos.setX(mevent->x()); mousepos.setY(mevent->y());
                values = FI.getInterpolatedValue(wells, x, y);
                ui->mapWidget->repaint();
                ui->wellsWidget->repaint();
                ui->resultWellWidget->repaint();
            }
            event->accept();
            return true;
        }
    }
    else if (obj == ui->wellsWidget)
    {
        if (event->type() == QEvent::Paint)
        {
            event->accept();
            drawWells();
            return true;
        }
    }
    else if (obj == ui->resultWellWidget)
    {
        if (event->type() == QEvent::Paint)
        {
            event->accept();
            drawResultWell();
            return true;
        }
    }


    return false;
}




//------------------------------------------------------------------------------


void MainWindow::drawMap(QEvent *event)
{
//    QPaintEvent *e = static_cast<QPaintEvent*>(event);


    QPainter painter(ui->mapWidget);
    painter.setBrush(Qt::white);

    painter.drawRect(ui->mapWidget->rect());

    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);



    for(int j = 0; j < wells.size(); ++j)
    {
        double x = wells[j].X * ui->mapWidget->width();
        double y = wells[j].Y * ui->mapWidget->height();
        painter.drawEllipse(x, y, 8, 8);
        painter.drawText(QPointF(x, y), "   " + QString::number(j));
    }

    QPoint p = mousepos; //ui->mapWidget->mapFromGlobal(mousepos);
    painter.drawEllipse(p.x(), p.y(), 10, 10);

    this->ui->resultWellWidget->repaint();
}



//------------------------------------------------------------------------------



void MainWindow::drawWells()
{
    const int wellWidth = 100; // px
    const int numSample = 50;

    QPainter painter(ui->wellsWidget);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::blue);

    painter.drawRect(ui->wellsWidget->rect());


    for(int j = 0; j < wells.size(); ++j)
    {
        QPainterPath path;
        double offset = wellWidth * (j+1);

        path.moveTo(offset, 0);

        for(int i = 0; i < numSample; ++i)
        {
            double x = offset + wells[j].getValue((double)i/numSample) * wellWidth / 2.0;
            double y = (double)i/numSample * ui->wellsWidget->rect().height();
            path.lineTo(x, y);
        }

        painter.drawPath(path);
    }
}



//------------------------------------------------------------------------------


void MainWindow::drawResultWell()
{

    QPainter painter(ui->resultWellWidget);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(ui->resultWellWidget->rect());

    int cx = ui->resultWellWidget->width() / 2;
    QPainterPath path;
    path.moveTo(cx, 0); // horioztal center
    for(int i = 0; i < values.size(); ++i)
    {
        path.lineTo(cx + values[i], (double)(/*values.size()-*/i)/values.size() * ui->resultWellWidget->height());
    }

    painter.drawPath(path);
}
