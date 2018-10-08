/****************************************************************************
** Meta object code from reading C++ file 'quizview.h'
**
** Created: Sun Jul 8 22:01:42 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/quizview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_quizview[] = {

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
      10,    9,    9,    9, 0x0a,
      23,    9,    9,    9, 0x08,
      33,    9,    9,    9, 0x08,
      42,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_quizview[] = {
    "quizview\0\0OK_clicked()\0replace()\0"
    "moveUp()\0moveDown()\0"
};

void quizview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        quizview *_t = static_cast<quizview *>(_o);
        switch (_id) {
        case 0: _t->OK_clicked(); break;
        case 1: _t->replace(); break;
        case 2: _t->moveUp(); break;
        case 3: _t->moveDown(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData quizview::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject quizview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quizview,
      qt_meta_data_quizview, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &quizview::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *quizview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *quizview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_quizview))
        return static_cast<void*>(const_cast< quizview*>(this));
    return QWidget::qt_metacast(_clname);
}

int quizview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
