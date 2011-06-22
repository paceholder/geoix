/****************************************************************************
** Meta object code from reading C++ file 'drop_widget.h'
**
** Created: Fri 6. May 16:35:07 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../drop_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drop_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxDropWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x05,
      54,   14,   13,   13, 0x05,
      86,   14,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_gxDropWidget[] = {
    "gxDropWidget\0\0event\0"
    "dragEnterSignal(QDragEnterEvent*)\0"
    "dragMoveSignal(QDragMoveEvent*)\0"
    "dropEventSignal(QDropEvent*)\0"
};

const QMetaObject gxDropWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_gxDropWidget,
      qt_meta_data_gxDropWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxDropWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxDropWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxDropWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxDropWidget))
        return static_cast<void*>(const_cast< gxDropWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int gxDropWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dragEnterSignal((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 1: dragMoveSignal((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 2: dropEventSignal((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void gxDropWidget::dragEnterSignal(QDragEnterEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void gxDropWidget::dragMoveSignal(QDragMoveEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void gxDropWidget::dropEventSignal(QDropEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
