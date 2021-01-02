/****************************************************************************
** Meta object code from reading C++ file 'quizedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QuizDb/quizedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quizedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_quizedit_t {
    QByteArrayData data[12];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_quizedit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_quizedit_t qt_meta_stringdata_quizedit = {
    {
QT_MOC_LITERAL(0, 0, 8), // "quizedit"
QT_MOC_LITERAL(1, 9, 10), // "OK_clicked"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 18), // "AddSection_clicked"
QT_MOC_LITERAL(4, 40, 15), // "AddRow0_clicked"
QT_MOC_LITERAL(5, 56, 15), // "AddRow1_clicked"
QT_MOC_LITERAL(6, 72, 15), // "AddRow2_clicked"
QT_MOC_LITERAL(7, 88, 15), // "AddRow3_clicked"
QT_MOC_LITERAL(8, 104, 22), // "DeleteSection0_clicked"
QT_MOC_LITERAL(9, 127, 22), // "DeleteSection1_clicked"
QT_MOC_LITERAL(10, 150, 22), // "DeleteSection2_clicked"
QT_MOC_LITERAL(11, 173, 22) // "DeleteSection3_clicked"

    },
    "quizedit\0OK_clicked\0\0AddSection_clicked\0"
    "AddRow0_clicked\0AddRow1_clicked\0"
    "AddRow2_clicked\0AddRow3_clicked\0"
    "DeleteSection0_clicked\0DeleteSection1_clicked\0"
    "DeleteSection2_clicked\0DeleteSection3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_quizedit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void quizedit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        quizedit *_t = static_cast<quizedit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OK_clicked(); break;
        case 1: _t->AddSection_clicked(); break;
        case 2: _t->AddRow0_clicked(); break;
        case 3: _t->AddRow1_clicked(); break;
        case 4: _t->AddRow2_clicked(); break;
        case 5: _t->AddRow3_clicked(); break;
        case 6: _t->DeleteSection0_clicked(); break;
        case 7: _t->DeleteSection1_clicked(); break;
        case 8: _t->DeleteSection2_clicked(); break;
        case 9: _t->DeleteSection3_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject quizedit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quizedit.data,
      qt_meta_data_quizedit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *quizedit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *quizedit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_quizedit.stringdata0))
        return static_cast<void*>(const_cast< quizedit*>(this));
    return QWidget::qt_metacast(_clname);
}

int quizedit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
