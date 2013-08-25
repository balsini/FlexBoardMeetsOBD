/****************************************************************************
** Meta object code from reading C++ file 'serialconfiguration.h'
**
** Created: Sun Aug 25 20:11:31 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/serialconfiguration.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialconfiguration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialConfiguration[] = {

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
      21,   20,   20,   20, 0x08,
      42,   20,   20,   20, 0x08,
      51,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SerialConfiguration[] = {
    "SerialConfiguration\0\0refreshDevicesSlot()\0"
    "okSlot()\0cancelSlot()\0"
};

void SerialConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialConfiguration *_t = static_cast<SerialConfiguration *>(_o);
        switch (_id) {
        case 0: _t->refreshDevicesSlot(); break;
        case 1: _t->okSlot(); break;
        case 2: _t->cancelSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SerialConfiguration::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialConfiguration::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SerialConfiguration,
      qt_meta_data_SerialConfiguration, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialConfiguration::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialConfiguration))
        return static_cast<void*>(const_cast< SerialConfiguration*>(this));
    return QWidget::qt_metacast(_clname);
}

int SerialConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
