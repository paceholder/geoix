/****************************************************************************
** Meta object code from reading C++ file 'tree_abstract_object.h'
**
** Created: Fri 6. May 16:35:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tree_abstract_object.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tree_abstract_object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxTreeAbstractObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gxTreeAbstractObject[] = {
    "gxTreeAbstractObject\0\0deleteThis()\0"
};

const QMetaObject gxTreeAbstractObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_gxTreeAbstractObject,
      qt_meta_data_gxTreeAbstractObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxTreeAbstractObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxTreeAbstractObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxTreeAbstractObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxTreeAbstractObject))
        return static_cast<void*>(const_cast< gxTreeAbstractObject*>(this));
    return QObject::qt_metacast(_clname);
}

int gxTreeAbstractObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deleteThis(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
