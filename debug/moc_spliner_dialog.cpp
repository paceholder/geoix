/****************************************************************************
** Meta object code from reading C++ file 'spliner_dialog.h'
**
** Created: Fri 6. May 16:35:00 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../spliner_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spliner_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxSplinerDialog[] = {

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
      17,   16,   16,   16, 0x0a,
      27,   16,   16,   16, 0x0a,
      47,   41,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gxSplinerDialog[] = {
    "gxSplinerDialog\0\0cleanup()\0onCalculate()\0"
    "index\0setupMapper(int)\0"
};

const QMetaObject gxSplinerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_gxSplinerDialog,
      qt_meta_data_gxSplinerDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxSplinerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxSplinerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxSplinerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxSplinerDialog))
        return static_cast<void*>(const_cast< gxSplinerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int gxSplinerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cleanup(); break;
        case 1: onCalculate(); break;
        case 2: setupMapper((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
