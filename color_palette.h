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
//    along with Geoix. If not, see <http://www.gnu.org/licenses/>.
//
//    e-mail: prof-x@inbox.ru
//------------------------------------------------------------------------

#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <QObject>
#include <QColor>
#include <QVector>
#include <QPair>

#include <QtAlgorithms>



/// Functions which is used in sorting
static bool colorPairLessThan(const QPair<double, QColor>& c1, const QPair<double, QColor>& c2)
{
    return (c1.first < c2.first);
}

class gxColorSlider;


/// Class for flexible work with color interpolation
/*! Class can contain several QColor objects and
  return interpolated color on demand.
*/
class gxColorPalette : public QObject
{
    Q_OBJECT
    friend class gxColorSlider;
public:
    /// Constructor
    gxColorPalette()
        : QObject()
    { }

    /// Destructor
    virtual ~gxColorPalette() { }

    /// Returns interpolated color.
    /// \param d must be in range 0..1
    virtual QColor getColor(double d) = 0;
    void changeColorPosition(int colNum, double newValue)
    {
        if ((colors.count() < colNum) ||
            (colNum < 0) ||
            (newValue < 0) ||
            (newValue > 1))
        return;

        colors[colNum].first = newValue;

        sortColors();
    }
protected:
    /// Sorted by _double_ argument vector of QColor's
    QVector<QPair<double, QColor> > colors;

    /// Method sorts colors in set by their double tag
    void sortColors() { qSort(colors.begin(), colors.end(), colorPairLessThan); }
};



/// Class implement continues color interpolation for gradient fill
class gxContinuesColorPalette : public gxColorPalette
{
    Q_OBJECT
public:
    /// Constructor
    gxContinuesColorPalette();
    /// Destructor
    virtual ~gxContinuesColorPalette() {}

    /// Type of interpolation
    enum gxColorInterpolationMode
    {
        RGB,
        HSL
    };

    /// Sets type of interpolations
    void setColorInterpolationMode(gxColorInterpolationMode mode);

    /// Adds new color to the set of colors.
    /// This method each time calls sorting of vector.
    void addColor(double d, QColor color);

    /// Removes all colors from set
    void clearColors() { colors.clear(); }

    /// Returns interpolated color which corresponds to the double value.
    virtual QColor getColor(double d);

signals:
    /// I can't remember what it the fuck is.
    void colorInterpolationModeChanged();

private:
    /// Contains type of color interpolation
    gxColorInterpolationMode colorInterpolationMode;
};

#endif // COLOR_PALETTE_H
