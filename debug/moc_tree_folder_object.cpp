/****************************************************************************
** Meta object code from reading C++ file 'tree_folder_object.h'
**
** Created: Fri 6. May 17:38:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tree_folder_object.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tree_folder_object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gxTreeFolderObject[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      35,   19,   19,   19, 0x0a,
      50,   19,   19,   19, 0x0a,
      64,   19,   19,   19, 0x0a,
      85,   80,   19,   19, 0x0a,
     115,   19,   19,   19, 0x0a,
     147,  128,   19,   19, 0x0a,
     189,   19,   19,   19, 0x0a,
     202,   19,   19,   19, 0x0a,
     225,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gxTreeFolderObject[] = {
    "gxTreeFolderObject\0\0createFolder()\0"
    "createPoints()\0createLines()\0"
    "createSurface()\0data\0createSurface(gxSurfaceData*)\0"
    "createWell()\0topData,bottomData\0"
    "createCube(gxSurfaceData*,gxSurfaceData*)\0"
    "createCube()\0importAndCreateWells()\0"
    "importAndCreatePoints()\0"
};

const QMetaObject gxTreeFolderObject::staticMetaObject = {
    { &gxTreeAbstractObject::staticMetaObject, qt_meta_stringdata_gxTreeFolderObject,
      qt_meta_data_gxTreeFolderObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gxTreeFolderObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gxTreeFolderObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gxTreeFolderObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gxTreeFolderObject))
        return static_cast<void*>(const_cast< gxTreeFolderObject*>(this));
    return gxTreeAbstractObject::qt_metacast(_clname);
}

int gxTreeFolderObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = gxTreeAbstractObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createFolder(); break;
        case 1: createPoints(); break;
        case 2: createLines(); break;
        case 3: createSurface(); break;
        case 4: createSurface((*reinterpret_cast< gxSurfaceData*(*)>(_a[1]))); break;
        case 5: createWell(); break;
        case 6: createCube((*reinterpret_cast< gxSurfaceData*(*)>(_a[1])),(*reinterpret_cast< gxSurfaceData*(*)>(_a[2]))); break;
        case 7: createCube(); break;
        case 8: importAndCreateWells(); break;
        case 9: importAndCreatePoints(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
