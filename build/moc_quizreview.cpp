/****************************************************************************
** Meta object code from reading C++ file 'quizreview.h'
**
** Created: Sun Jul 8 22:01:48 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/quizreview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizreview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_quizreview[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   11,   11,   11, 0x0a,
      42,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_quizreview[] = {
    "quizreview\0\0done_clicked()\0save_clicked()\0"
    "review_clicked()\0"
};

void quizreview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        quizreview *_t = static_cast<quizreview *>(_o);
        switch (_id) {
        case 0: _t->done_clicked(); break;
        case 1: _t->save_clicked(); break;
        case 2: _t->review_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData quizreview::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject quizreview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quizreview,
      qt_meta_data_quizreview, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &quizreview::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *quizreview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *quizreview::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_quizreview))
        return static_cast<void*>(const_cast< quizreview*>(this));
    return QWidget::qt_metacast(_clname);
}

int quizreview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
