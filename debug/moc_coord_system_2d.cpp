/****************************************************************************
** Meta object code from reading C++ file 'coord_system_2d.h'
**
** Created: Fri 6. May 16:34:53 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../coord_system_2d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coord_system_2d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxCoordSystem2D[] = {

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

static const char qt_meta_stringdata_gxCoordSystem2D[] = {
    "gxCoordSystem2D\0"
};

const QMetaObject gxCoordSystem2D::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_gxCoordSystem2D,
      qt_meta_data_gxCoordSystem2D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxCoordSystem2D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxCoordSystem2D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxCoordSystem2D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxCoordSystem2D))
        return static_cast<void*>(const_cast< gxCoordSystem2D*>(this));
    return QObject::qt_metacast(_clname);
}

int gxCoordSystem2D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
