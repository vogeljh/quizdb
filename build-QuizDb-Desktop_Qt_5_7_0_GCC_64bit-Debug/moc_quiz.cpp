/****************************************************************************
** Meta object code from reading C++ file 'quiz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QuizDb/quiz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quiz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_quiz_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_quiz_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_quiz_t qt_meta_stringdata_quiz = {
    {
QT_MOC_LITERAL(0, 0, 4), // "quiz"
QT_MOC_LITERAL(1, 5, 16), // "OkButton_clicked"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "cancel_clicked"
QT_MOC_LITERAL(4, 38, 16), // "editQuiz_clicked"
QT_MOC_LITERAL(5, 55, 16), // "chapter2selected"
QT_MOC_LITERAL(6, 72, 13), // "book2selected"
QT_MOC_LITERAL(7, 86, 16), // "chapter1selected"
QT_MOC_LITERAL(8, 103, 13) // "book1selected"

    },
    "quiz\0OkButton_clicked\0\0cancel_clicked\0"
    "editQuiz_clicked\0chapter2selected\0"
    "book2selected\0chapter1selected\0"
    "book1selected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_quiz[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void quiz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        quiz *_t = static_cast<quiz *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OkButton_clicked(); break;
        case 1: _t->cancel_clicked(); break;
        case 2: _t->editQuiz_clicked(); break;
        case 3: _t->chapter2selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->book2selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->chapter1selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->book1selected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject quiz::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quiz.data,
      qt_meta_data_quiz,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *quiz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *quiz::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_quiz.stringdata0))
        return static_cast<void*>(const_cast< quiz*>(this));
    if (!strcmp(_clname, "Ui::quizdlg"))
        return static_cast< Ui::quizdlg*>(const_cast< quiz*>(this));
    return QWidget::qt_metacast(_clname);
}

int quiz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
