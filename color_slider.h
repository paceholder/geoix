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


#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include <QFrame>
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>

#include "color_palette.h"


class gxColorSlider : public QFrame
{
    Q_OBJECT
public:
    gxColorSlider(QWidget* parent)
        : QFrame(parent)
    {
        moving = false;
    }
    ~gxColorSlider()
    {
        delete palette;
    }

protected:

//    void mouseDoubleClickEvent(QMouseEvent *)
//    {
//        QPoint p = event->pos();
//
//        int hit = testHit(p);
//
//
//        if (hit >= 0)
//        {
//            moving = false;
//            QColorDialog dialog;
//            dialog.exec();
//
//            colorTicks[hit].color = dialog.getColor();
//        }
//    }

    void mousePressEvent(QMouseEvent *event)
    {
        QPoint p = event->pos();

        int hit = testHit(p);

        if (hit >= 0)
        {
            activeColorPosition = hit;
            moving = true;            
        }

        draw();

    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if ((moving) &&
            (event->buttons() & Qt::LeftButton))
        {
            if (activeColorPosition >= 0)
            {
                palette->colors[activeColorPosition].first = event->pos().x()/(double)width();
            }
        }

        draw();

    }

    void mouseReleaseEvent(QMouseEvent *event)
    {
        moving = false;
    }



private:
    gxContinuesColorPalette* palette;
    bool moving;

    int activeColorPosition;

    int testHit(QPoint p)
    {
        int val;
        for(int i = 0; i < this->palette->colors.count(); ++i)
        {
            val = int(width() * palette->colors[i].first);

            if (qAbs(val - p.x()) <= 3)
            {
                return i;
            }
        }

        return -1; // no such tick
    }


    void draw()
    {
        QPainter painter(this);

        // black background
        painter.fillRect(this->rect(), Qt::black);

        double d;
        for(int i = 0; i < this->width(); ++i)
        {
            d = i/(double)width();
            painter.setPen(palette->getColor(d));
            painter.drawLine(i, 0, i, height());
        }


        int x;
        for(int i = 0; i < palette->colors.count(); ++i)
        {
            x = int (palette->colors[i].first * width());
            painter.drawEllipse(QPoint(x, height()/2), 2, 2);
        }
    }
};

#endif // COLOR_SLIDER_H
