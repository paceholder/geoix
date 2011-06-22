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


#ifndef RENDER_PANEL_H
#define RENDER_PANEL_H

#include <QWidget>
#include <QColor>
#include <QPaintEvent>
#include <QPainter>


#include "visual_object.h"


/*! \file render_panel.h
    \brief Contains declaration of gxRenderPanel class
*/

/// Base class of all types of render panels.
/*!
Render panel provides following operations:
resize, moving, clicking,
drawing (pure virtual).
*/
class gxRenderPanel : public QWidget
{
    Q_OBJECT
public:
    gxRenderPanel(QWidget* parent); ///< constructor
    virtual ~gxRenderPanel(); ///< destructor

    /// register object in panel
    /*!
       Let the panel know which object is rendered in by it
       \return Nothing
    */
    void registerObject(gxVisualObject* object);

    /// unregister object in panel
    /*!
       Remove link to the object from panel's vector of rendering objects
       \return Nothing
    */
    void unregisterObject(gxVisualObject* object);

    bool isObjectRegistered(gxVisualObject* object);


    /// Returns gl_panel.
    /// todo: Function MUST BE removed
    QGLWidget* getGLPanel()
    {
        return gl_panel;
    }


    /// In some situations it's necessary to recreate display lists
    /// if any changes were made;
    void recreateDisplayLists();

    /// Reruns width of the panel's border
    inline int getBorderWidth() { return this->border_width; }


    /// Function draws border and OpenGL graphics
    /*!
        Function is called when Render panel need to be
        repainted. First, it calls function which
        draws border of panel and then calls function for
        OpenGL graphics rendering
    */
    inline virtual void draw()
    {
        drawBorder();
        gl_panel->updateGL();
    }
    virtual void gldraw() = 0;


    QPixmap renderPixmap();


public slots:
    /// Executes when some of object is deleted
    /*!
        Gets the pointer to the deleted object using sender()
        and removes it from objects array

        \see objects
    */
    void objectDeleted();

protected:
    QColor border_active_color; ///< Color of border of active panel
    QColor border_inactive_color; ///< Color of border of inactive panel

    QPoint oldMousePos; ///< Previous mouse position (Global)

    QVector<gxVisualObject*> objects; ///< Vector of objects rendered by this panel

    // todo: set here gxGLPanel instead of QGLWidget
    ///  gl_panel provide rendering of 3D graphics
    /*!
        Also reimplements functions of QGLWidget for initialization, resizing and drawing
    */
    QGLWidget* gl_panel;

    /// Bind resize spots to the resize direction
    /*!
        Bring in correspondence constants describing resize direction
        with QRects of every resize spot
            - Gx::LeftTop
            - Gx::RightTop
            - Gx::LeftBottom
            - Gx::RightBottom

        \see Gx
    */
    QMap<Qt::Corner, QRect> resizeSpots;

    /// 3D Size of scene in current Render Panel
    gxSize3D* size3d;

    /// Width of panel's border
    int border_width;

    /// Determine direction of resizing
    Qt::Corner resizeDirection;

    bool resizing; ///< State of current operation with panel
    bool moving; ///< State of current operation with panel


    void movingHandler(int x, int y);
    void resizingHandler(int x, int y, QPoint& p);

    virtual void drawBorder();
    void updateResizeSpots();

    /// Recalculates size of 3d scene after registering of new object
    void recalcSize(); // after adding new objects

    //--------------------------------
    // override default event handlers

    // dragging
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    /// Paint event handler
    inline virtual void paintEvent(QPaintEvent* event) { draw(); event->accept(); }
    /// Mouse move event handler
    virtual void mouseMoveEvent(QMouseEvent* event);
    /// Mouse press event handler
    virtual void mousePressEvent(QMouseEvent* event);
    /// Mouse release event handler
    virtual void mouseReleaseEvent(QMouseEvent * event);
    /// Resize event handler
    virtual void resizeEvent ( QResizeEvent * event );
};

#endif // RENDER_PANEL_H
