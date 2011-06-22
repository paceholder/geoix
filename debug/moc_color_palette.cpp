/****************************************************************************
** Meta object code from reading C++ file 'color_palette.h'
**
** Created: Fri 6. May 16:34:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../color_palette.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'color_palette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxColorPalette[] = {

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

static const char qt_meta_stringdata_gxColorPalette[] = {
    "gxColorPalette\0"
};

const QMetaObject gxColorPalette::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_gxColorPalette,
      qt_meta_data_gxColorPalette, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxColorPalette::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxColorPalette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxColorPalette::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxColorPalette))
        return static_cast<void*>(const_cast< gxColorPalette*>(this));
    return QObject::qt_metacast(_clname);
}

int gxColorPalette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_gxContinuesColorPalette[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_gxContinuesColorPalette[] = {
    "gxContinuesColorPalette\0\0"
    "colorInterpolationModeChanged()\0"
};

const QMetaObject gxContinuesColorPalette::staticMetaObject = {
    { &gxColorPalette::staticMetaObject, qt_meta_stringdata_gxContinuesColorPalette,
      qt_meta_data_gxContinuesColorPalette, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxContinuesColorPalette::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxContinuesColorPalette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxContinuesColorPalette::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxContinuesColorPalette))
        return static_cast<void*>(const_cast< gxContinuesColorPalette*>(this));
    return gxColorPalette::qt_metacast(_clname);
}

int gxContinuesColorPalette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gxColorPalette::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: colorInterpolationModeChanged(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void gxContinuesColorPalette::colorInterpolationModeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
