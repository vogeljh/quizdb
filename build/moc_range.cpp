/****************************************************************************
** Meta object code from reading C++ file 'range.h'
**
** Created: Sun Jul 8 22:01:35 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/range.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'range.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_range[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      29,    6,    6,    6, 0x0a,
      48,    6,    6,    6, 0x0a,
      70,    6,    6,    6, 0x0a,
      89,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_range[] = {
    "range\0\0chapter2selected(int)\0"
    "book2selected(int)\0chapter1selected(int)\0"
    "book1selected(int)\0rangedlg_ok()\0"
};

void range::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        range *_t = static_cast<range *>(_o);
        switch (_id) {
        case 0: _t->chapter2selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->book2selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->chapter1selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->book1selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->rangedlg_ok(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData range::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject range::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_range,
      qt_meta_data_range, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &range::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *range::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *range::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_range))
        return static_cast<void*>(const_cast< range*>(this));
    if (!strcmp(_clname, "Ui::rangedlg"))
        return static_cast< Ui::rangedlg*>(const_cast< range*>(this));
    return QWidget::qt_metacast(_clname);
}

int range::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
