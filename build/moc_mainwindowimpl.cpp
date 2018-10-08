/****************************************************************************
** Meta object code from reading C++ file 'mainwindowimpl.h'
**
** Created: Sun Jul 8 22:01:33 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindowimpl.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowimpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindowImpl[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      31,   15,   15,   15, 0x08,
      48,   15,   15,   15, 0x08,
      62,   15,   15,   15, 0x08,
      76,   15,   15,   15, 0x08,
      95,   15,   15,   15, 0x08,
     106,   15,   15,   15, 0x08,
     123,   15,   15,   15, 0x08,
     131,   15,   15,   15, 0x08,
     144,   15,   15,   15, 0x08,
     157,   15,   15,   15, 0x08,
     171,   15,   15,   15, 0x08,
     183,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindowImpl[] = {
    "MainWindowImpl\0\0openDatabase()\0"
    "printQuestions()\0selectRange()\0"
    "selectTypes()\0setQuestionOrder()\0"
    "loadQuiz()\0prepareQuizzes()\0about()\0"
    "searchText()\0insertCopy()\0insertBlank()\0"
    "deleteRow()\0showKey()\0"
};

void MainWindowImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindowImpl *_t = static_cast<MainWindowImpl *>(_o);
        switch (_id) {
        case 0: _t->openDatabase(); break;
        case 1: _t->printQuestions(); break;
        case 2: _t->selectRange(); break;
        case 3: _t->selectTypes(); break;
        case 4: _t->setQuestionOrder(); break;
        case 5: _t->loadQuiz(); break;
        case 6: _t->prepareQuizzes(); break;
        case 7: _t->about(); break;
        case 8: _t->searchText(); break;
        case 9: _t->insertCopy(); break;
        case 10: _t->insertBlank(); break;
        case 11: _t->deleteRow(); break;
        case 12: _t->showKey(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindowImpl::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindowImpl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindowImpl,
      qt_meta_data_MainWindowImpl, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindowImpl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindowImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindowImpl))
        return static_cast<void*>(const_cast< MainWindowImpl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
