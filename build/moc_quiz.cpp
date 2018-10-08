/****************************************************************************
** Meta object code from reading C++ file 'quiz.h'
**
** Created: Sun Jul 8 22:01:39 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/quiz.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quiz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_quiz[] = {

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
       6,    5,    5,    5, 0x0a,
      25,    5,    5,    5, 0x0a,
      42,    5,    5,    5, 0x0a,
      61,    5,    5,    5, 0x0a,
      83,    5,    5,    5, 0x0a,
     102,    5,    5,    5, 0x0a,
     124,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_quiz[] = {
    "quiz\0\0OkButton_clicked()\0cancel_clicked()\0"
    "editQuiz_clicked()\0chapter2selected(int)\0"
    "book2selected(int)\0chapter1selected(int)\0"
    "book1selected(int)\0"
};

void quiz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        quiz *_t = static_cast<quiz *>(_o);
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

const QMetaObjectExtraData quiz::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject quiz::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_quiz,
      qt_meta_data_quiz, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &quiz::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *quiz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *quiz::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_quiz))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
