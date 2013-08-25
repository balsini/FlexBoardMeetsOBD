/****************************************************************************
** Meta object code from reading C++ file 'bluetoothdevices.h'
**
** Created: Sun Aug 25 20:11:37 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/bluetoothdevices.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bluetoothdevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BluetoothDevices[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      27,   17,   17,   17, 0x08,
      52,   40,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BluetoothDevices[] = {
    "BluetoothDevices\0\0okSlot()\0cancelSlot()\0"
    "devices,num\0"
    "showBluetoothInquirySlot(inquiry_result_t*,uint)\0"
};

void BluetoothDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BluetoothDevices *_t = static_cast<BluetoothDevices *>(_o);
        switch (_id) {
        case 0: _t->okSlot(); break;
        case 1: _t->cancelSlot(); break;
        case 2: _t->showBluetoothInquirySlot((*reinterpret_cast< inquiry_result_t*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BluetoothDevices::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BluetoothDevices::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BluetoothDevices,
      qt_meta_data_BluetoothDevices, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BluetoothDevices::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BluetoothDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BluetoothDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BluetoothDevices))
        return static_cast<void*>(const_cast< BluetoothDevices*>(this));
    return QWidget::qt_metacast(_clname);
}

int BluetoothDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
