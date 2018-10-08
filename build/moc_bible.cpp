/****************************************************************************
** Meta object code from reading C++ file 'bible.h'
**
** Created: Sun Jul 8 22:01:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/bible.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bible.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_bible[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x0a,
      30,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_bible[] = {
    "bible\0\0verseCopy(QModelIndex)\0copyVerse()\0"
};

void bible::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        bible *_t = static_cast<bible *>(_o);
        switch (_id) {
        case 0: _t->verseCopy((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->copyVerse(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData bible::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject bible::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_bible,
      qt_meta_data_bible, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &bible::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *bible::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *bible::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_bible))
        return static_cast<void*>(const_cast< bible*>(this));
    return QWidget::qt_metacast(_clname);
}

int bible::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
