/****************************************************************************
** Meta object code from reading C++ file 'range.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QuizDb/range.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'range.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_range_t {
    QByteArrayData data[7];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_range_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_range_t qt_meta_stringdata_range = {
    {
QT_MOC_LITERAL(0, 0, 5), // "range"
QT_MOC_LITERAL(1, 6, 16), // "chapter2selected"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "book2selected"
QT_MOC_LITERAL(4, 38, 16), // "chapter1selected"
QT_MOC_LITERAL(5, 55, 13), // "book1selected"
QT_MOC_LITERAL(6, 69, 11) // "rangedlg_ok"

    },
    "range\0chapter2selected\0\0book2selected\0"
    "chapter1selected\0book1selected\0"
    "rangedlg_ok"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_range[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       3,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void range::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        range *_t = static_cast<range *>(_o);
        Q_UNUSED(_t)
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

const QMetaObject range::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_range.data,
      qt_meta_data_range,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *range::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *range::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_range.stringdata0))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
