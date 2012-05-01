/****************************************************************************
** Meta object code from reading C++ file 'functiondialog.h'
**
** Created: Mon Apr 30 22:12:24 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "functiondialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functiondialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FunctionDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      48,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   15,   15,   15, 0x08,
      95,   15,   15,   15, 0x08,
     133,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FunctionDialog[] = {
    "FunctionDialog\0\0changed_toMain(FunctionDialog*)\0"
    "changed_Object()\0on_functionName_textChanged()\0"
    "on_typeComboBox_currentIndexChanged()\0"
    "on_functionParameters_textChanged()\0"
};

const QMetaObject FunctionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FunctionDialog,
      qt_meta_data_FunctionDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FunctionDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FunctionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FunctionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionDialog))
        return static_cast<void*>(const_cast< FunctionDialog*>(this));
    if (!strcmp(_clname, "Ui::FunctionDialog"))
        return static_cast< Ui::FunctionDialog*>(const_cast< FunctionDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int FunctionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed_toMain((*reinterpret_cast< FunctionDialog*(*)>(_a[1]))); break;
        case 1: changed_Object(); break;
        case 2: on_functionName_textChanged(); break;
        case 3: on_typeComboBox_currentIndexChanged(); break;
        case 4: on_functionParameters_textChanged(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FunctionDialog::changed_toMain(FunctionDialog * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FunctionDialog::changed_Object()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
