/****************************************************************************
** Meta object code from reading C++ file 'kriging_mapper.h'
**
** Created: Fri 6. May 16:35:39 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../kriging_mapper.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kriging_mapper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxKrigingMapper[] = {

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
      22,   17,   16,   16, 0x0a,
      63,   53,   16,   16, 0x0a,
      91,   84,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gxKrigingMapper[] = {
    "gxKrigingMapper\0\0type\0"
    "onVariogramModelActivated(int)\0threshold\0"
    "onThreshold(QString)\0radius\0"
    "onRadius(QString)\0"
};

const QMetaObject gxKrigingMapper::staticMetaObject = {
    { &gxAbstractMapper::staticMetaObject, qt_meta_stringdata_gxKrigingMapper,
      qt_meta_data_gxKrigingMapper, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxKrigingMapper::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxKrigingMapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxKrigingMapper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxKrigingMapper))
        return static_cast<void*>(const_cast< gxKrigingMapper*>(this));
    return gxAbstractMapper::qt_metacast(_clname);
}

int gxKrigingMapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gxAbstractMapper::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: onVariogramModelActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onThreshold((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: onRadius((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
