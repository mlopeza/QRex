/****************************************************************************
** Meta object code from reading C++ file 'stepdialog.h'
**
** Created: Sat Apr 28 15:12:39 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stepdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stepdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StepDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StepDialog[] = {
    "StepDialog\0\0on_stepText_textChanged()\0"
};

const QMetaObject StepDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_StepDialog,
      qt_meta_data_StepDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StepDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StepDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StepDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StepDialog))
        return static_cast<void*>(const_cast< StepDialog*>(this));
    if (!strcmp(_clname, "Ui::StepDialog"))
        return static_cast< Ui::StepDialog*>(const_cast< StepDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int StepDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_stepText_textChanged(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
