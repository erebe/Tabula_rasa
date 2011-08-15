/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.hpp'
**
** Created: Mon Aug 15 03:45:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Interface/mainwindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      49,   41,   11,   11, 0x08,
      87,   41,   11,   11, 0x08,
     127,   11,   11,   11, 0x08,
     160,   41,   11,   11, 0x08,
     192,   41,   11,   11, 0x08,
     227,   41,   11,   11, 0x08,
     262,   41,   11,   11, 0x08,
     297,   41,   11,   11, 0x08,
     340,   41,   11,   11, 0x08,
     377,  372,   11,   11, 0x0a,
     413,  408,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_action_Ouvrir_triggered()\0"
    "checked\0on_actionMode_Edition_triggered(bool)\0"
    "on_actionMode_Insertion_triggered(bool)\0"
    "on_actionEnregistrer_triggered()\0"
    "on_actionAction_triggered(bool)\0"
    "on_actionIteration_triggered(bool)\0"
    "on_actionProcedure_triggered(bool)\0"
    "on_actionCondition_triggered(bool)\0"
    "on_actionConditionMultiple_triggered(bool)\0"
    "on_actionSortie_triggered(bool)\0mode\0"
    "setMode(AlgorithmeScene::Mode)\0item\0"
    "changeLabel(LabelItem*)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_action_Ouvrir_triggered(); break;
        case 1: on_actionMode_Edition_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_actionMode_Insertion_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: on_actionEnregistrer_triggered(); break;
        case 4: on_actionAction_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_actionIteration_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_actionProcedure_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: on_actionCondition_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_actionConditionMultiple_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: on_actionSortie_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: setMode((*reinterpret_cast< AlgorithmeScene::Mode(*)>(_a[1]))); break;
        case 11: changeLabel((*reinterpret_cast< LabelItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
