/****************************************************************************
** Meta object code from reading C++ file 'types.h'
**
** Created: Sun Jul 8 22:01:36 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/types.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'types.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_types[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      20,    6,    6,    6, 0x0a,
      40,    6,    6,    6, 0x0a,
      54,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_types[] = {
    "types\0\0OK_clicked()\0EditCodes_clicked()\0"
    "All_clicked()\0None_clicked()\0"
};

void types::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        types *_t = static_cast<types *>(_o);
        switch (_id) {
        case 0: _t->OK_clicked(); break;
        case 1: _t->EditCodes_clicked(); break;
        case 2: _t->All_clicked(); break;
        case 3: _t->None_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData types::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject types::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_types,
      qt_meta_data_types, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &types::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *types::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *types::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_types))
        return static_cast<void*>(const_cast< types*>(this));
    return QWidget::qt_metacast(_clname);
}

int types::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
