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


#ifndef DROP_WIDGET_H
#define DROP_WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPainter>

class gxDropWidget : public QFrame
{
    Q_OBJECT
public:
    gxDropWidget(QWidget* parent)
        : QFrame(parent)
    {
        // code here
    }
    virtual ~gxDropWidget()
    {
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event)
    {
        emit dragEnterSignal(event);
    }

    void dragMoveEvent(QDragMoveEvent *event)
    {
        emit dragMoveSignal(event);
    }
    void dropEvent(QDropEvent *event)
    {
        emit dropEventSignal(event);
    }


    /// Draws rectangle - drop spot
    void paintEvent(QPaintEvent *)
    {
        QPainter p(this);

        p.setBrush(Qt::black);
        p.drawRoundedRect(3, 3, this->width() - 3, this->height() - 3, 3, 3);
    }

signals:
    void dragEnterSignal(QDragEnterEvent* event);
    void dragMoveSignal(QDragMoveEvent *event);
    void dropEventSignal(QDropEvent *event);
};

#endif // DROP_WIDGET_H
