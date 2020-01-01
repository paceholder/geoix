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


#include "color_palette.h"



gxContinuesColorPalette::gxContinuesColorPalette()
    : gxColorPalette()
{
    colorInterpolationMode = RGB;
}


//------------------------------------------------------------------------------


void gxContinuesColorPalette::setColorInterpolationMode(gxColorInterpolationMode mode)
{
    if (colorInterpolationMode != mode)
    {
        colorInterpolationMode = mode;
        emit colorInterpolationModeChanged();
    }
}


//------------------------------------------------------------------------------


void gxContinuesColorPalette::addColor(double d, QColor color)
{
    if ((d < 0) ||
        (d > 1))
    return;

    colors.append(QPair<double, QColor>(d, color));
    sortColors();
}


//------------------------------------------------------------------------------


QColor gxContinuesColorPalette::getColor(double d)
{
    if (colors.count() == 0 ) return Qt::black;
    if (colors.count() == 1 ) return colors[0].second;

    if (d < colors.first().first) return colors.first().second;
    if (d > colors.last().first) return colors.last().second;

    int i = 0;
    while (d > colors[i+1].first)
        ++i;

    double delta = (d - colors[i].first)/(colors[i+1].first - colors[i].first);

    QColor c1 = colors[i].second;
    QColor c2 = colors[i+1].second;
    QColor c;

    double a1, a2;

    switch(colorInterpolationMode)
    {
    case RGB:
        double r1, g1, b1, r2, g2, b2;
        c1.getRgbF(&r1, &g1, &b1, &a1);
        c2.getRgbF(&r2, &g2, &b2, &a2);

        c.setRgbF(r1 + (r2 - r1)   * delta,
                  g1 + (g2 - g1)   * delta,
                  b1 + (b2 - b1)   * delta,
                  0);
        break;
    case HSL:
        double h1, s1, l1, h2, s2, l2;
        c1.getHslF(&h1, &s1, &l1, &a1);
        c2.getHslF(&h2, &s2, &l2, &a2);

        c.setHslF(h1 + (h2 - h1)   * delta,
                  s1 + (s2 - s1)   * delta,
                  l1 + (l2 - l1)   * delta,
                  0);
        break;
    }
    return c;
}
