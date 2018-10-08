/****************************************************************************
** Meta object code from reading C++ file 'codemodel.h'
**
** Created: Wed May 6 22:57:00 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/codemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'codemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_codeModel[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_codeModel[] = {
    "codeModel\0"
};

const QMetaObject codeModel::staticMetaObject = {
    { &QSqlQueryModel::staticMetaObject, qt_meta_stringdata_codeModel,
      qt_meta_data_codeModel, 0 }
};

const QMetaObject *codeModel::metaObject() const
{
    return &staticMetaObject;
}

void *codeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_codeModel))
	return static_cast<void*>(const_cast< codeModel*>(this));
    return QSqlQueryModel::qt_metacast(_clname);
}

int codeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlQueryModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
