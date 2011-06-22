/****************************************************************************
** Meta object code from reading C++ file 'gl_panel_3d.h'
**
** Created: Fri 6. May 16:34:47 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gl_panel_3d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gl_panel_3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxGLPanel3D[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_gxGLPanel3D[] = {
    "gxGLPanel3D\0"
};

const QMetaObject gxGLPanel3D::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_gxGLPanel3D,
      qt_meta_data_gxGLPanel3D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxGLPanel3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxGLPanel3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxGLPanel3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxGLPanel3D))
        return static_cast<void*>(const_cast< gxGLPanel3D*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int gxGLPanel3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
