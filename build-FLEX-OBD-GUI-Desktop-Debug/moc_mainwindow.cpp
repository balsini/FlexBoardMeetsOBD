/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Aug 25 20:12:27 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      35,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     125,   11,   11,   11, 0x0a,
     146,   11,   11,   11, 0x0a,
     172,  163,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0exitSlot()\0aboutSlot()\0"
    "plotsSlot()\0selectMonitorSlot()\0"
    "serialConfigSlot()\0serialConnectSlot()\0"
    "alignMonitorSlot()\0updateMonitorsSlot()\0"
    "flexOnlineSlot()\0data,num\0"
    "bluetoothInquiryCompleted(inquiry_result_t*,uint)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->exitSlot(); break;
        case 1: _t->aboutSlot(); break;
        case 2: _t->plotsSlot(); break;
        case 3: _t->selectMonitorSlot(); break;
        case 4: _t->serialConfigSlot(); break;
        case 5: _t->serialConnectSlot(); break;
        case 6: _t->alignMonitorSlot(); break;
        case 7: _t->updateMonitorsSlot(); break;
        case 8: _t->flexOnlineSlot(); break;
        case 9: _t->bluetoothInquiryCompleted((*reinterpret_cast< inquiry_result_t*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
