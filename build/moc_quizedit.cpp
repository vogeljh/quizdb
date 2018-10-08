/****************************************************************************
** Meta object code from reading C++ file 'quizedit.h'
**
** Created: Sun Jul 8 22:01:40 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/quizedit.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_quizedit[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      23,    9,    9,    9, 0x0a,
      44,    9,    9,    9, 0x0a,
      62,    9,    9,    9, 0x0a,
      80,    9,    9,    9, 0x0a,
      98,    9,    9,    9, 0x0a,
     116,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_quizedit[] = {
    "quizedit\0\0OK_clicked()\0AddSection_clicked()\0"
    "AddRow0_clicked()\0AddRow1_clicked()\0"
    "AddRow2_clicked()\0AddRow3_clicked()\0"
    "DeleteSection_clicked()\0"
};

void quizedit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        quizedit *_t = static_cast<quizedit *>(_o);
        switch (_id) {
        case 0: _t->OK_clicked(); break;
        case 1: _t->AddSection_clicked(); break;
        case 2: _t->AddRow0_clicked(); break;
        case 3: _t->AddRow1_clicked(); break;
        case 4: _t->AddRow2_clicked(); break;
        case 5: _t->AddRow3_clicked(); break;
        case 6: _t->DeleteSection_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData quizedit::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject quizedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quizedit,
      qt_meta_data_quizedit, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &quizedit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *quizedit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *quizedit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_quizedit))
        return static_cast<void*>(const_cast< quizedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int quizedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
