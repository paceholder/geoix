/****************************************************************************
** Meta object code from reading C++ file 'visual_object.h'
**
** Created: Fri 6. May 16:34:27 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../visual_object.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visual_object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxVisualObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   15,   15,   15, 0x0a,
      48,   15,   15,   15, 0x0a,
      60,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gxVisualObject[] = {
    "gxVisualObject\0\0objectDelete()\0"
    "importFromFile()\0clearData()\0options()\0"
};

const QMetaObject gxVisualObject::staticMetaObject = {
    { &gxTreeObject::staticMetaObject, qt_meta_stringdata_gxVisualObject,
      qt_meta_data_gxVisualObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxVisualObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxVisualObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxVisualObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxVisualObject))
        return static_cast<void*>(const_cast< gxVisualObject*>(this));
    return gxTreeObject::qt_metacast(_clname);
}

int gxVisualObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gxTreeObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: objectDelete(); break;
        case 1: importFromFile(); break;
        case 2: clearData(); break;
        case 3: options(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void gxVisualObject::objectDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
