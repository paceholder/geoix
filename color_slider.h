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

#include "color_palette.h"

struct gxColorTick
{
    int position;

};

class gxColorSlider : public QFrame
{
public:
    gxColorSlider(QWidget* parent)
        : QFrame(parent)
    {
        palette = new gxColorPalette();
        moving = false;
    }
    ~gxColorSlider()
    {
        delete palette;
    }

protected:
    void mousePressEvent(QMouseEvent *event)
    {

    }

    void mouseMoveEvent(QMouseEvent *)
    {

    }

    void mouseReleaseEvent(QMouseEvent *)
    {

    }

private:
    gxColorPalette* palette;
    bool moving;


    void draw()
    {
        QPainter painter(this);

        // black background
        painter.fillRect(this->receivers(), Qt::black);

        double d;
        for(int i = 0; i < this->width(); +i)
        {
            d = i/(double)width();
            painter.setPen(palette->getColor(d));
            painter.drawLine(i, 0, i, height());
        }
    }
}

#endif // COLOR_SLIDER_H
