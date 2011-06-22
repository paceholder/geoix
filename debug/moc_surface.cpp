/****************************************************************************
** Meta object code from reading C++ file 'surface.h'
**
** Created: Fri 6. May 18:54:43 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../surface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'surface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxSurface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      28,   10,   10,   10, 0x0a,
      40,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gxSurface[] = {
    "gxSurface\0\0importFromFile()\0clearData()\0"
    "options()\0"
};

const QMetaObject gxSurface::staticMetaObject = {
    { &gxVisualObject::staticMetaObject, qt_meta_stringdata_gxSurface,
      qt_meta_data_gxSurface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxSurface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxSurface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxSurface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxSurface))
        return static_cast<void*>(const_cast< gxSurface*>(this));
    return gxVisualObject::qt_metacast(_clname);
}

int gxSurface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gxVisualObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: importFromFile(); break;
        case 1: clearData(); break;
        case 2: options(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
