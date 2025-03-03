/****************************************************************************
** Meta object code from reading C++ file 'device.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../modbusNov12/OnlineMonitor/model/device.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'device.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Device_t {
    QByteArrayData data[17];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Device_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Device_t qt_meta_stringdata_Device = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Device"
QT_MOC_LITERAL(1, 7, 18), // "pProductionChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "pSystemChanged"
QT_MOC_LITERAL(4, 42, 18), // "pYieldTrendChanged"
QT_MOC_LITERAL(5, 61, 10), // "pIOChanged"
QT_MOC_LITERAL(6, 72, 13), // "pTrendChanged"
QT_MOC_LITERAL(7, 86, 18), // "pDeviceInformation"
QT_MOC_LITERAL(8, 105, 18), // "DeviceInformation*"
QT_MOC_LITERAL(9, 124, 7), // "pManual"
QT_MOC_LITERAL(10, 132, 7), // "Manual*"
QT_MOC_LITERAL(11, 140, 7), // "pSystem"
QT_MOC_LITERAL(12, 148, 7), // "System*"
QT_MOC_LITERAL(13, 156, 3), // "pIO"
QT_MOC_LITERAL(14, 160, 3), // "IO*"
QT_MOC_LITERAL(15, 164, 6), // "pTrend"
QT_MOC_LITERAL(16, 171, 6) // "Trend*"

    },
    "Device\0pProductionChanged\0\0pSystemChanged\0"
    "pYieldTrendChanged\0pIOChanged\0"
    "pTrendChanged\0pDeviceInformation\0"
    "DeviceInformation*\0pManual\0Manual*\0"
    "pSystem\0System*\0pIO\0IO*\0pTrend\0Trend*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Device[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       5,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   69,    2, 0x02 /* Public */,
       9,    0,   70,    2, 0x02 /* Public */,
      11,    0,   71,    2, 0x02 /* Public */,
      13,    0,   72,    2, 0x02 /* Public */,
      15,    0,   73,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 8,
    0x80000000 | 10,
    0x80000000 | 12,
    0x80000000 | 14,
    0x80000000 | 16,

 // properties: name, type, flags
       7, 0x80000000 | 8, 0x00095009,
      13, 0x80000000 | 14, 0x00095009,
       9, 0x80000000 | 10, 0x00095009,
      11, 0x80000000 | 12, 0x00095009,
      15, 0x80000000 | 16, 0x00095009,

       0        // eod
};

void Device::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Device *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pProductionChanged(); break;
        case 1: _t->pSystemChanged(); break;
        case 2: _t->pYieldTrendChanged(); break;
        case 3: _t->pIOChanged(); break;
        case 4: _t->pTrendChanged(); break;
        case 5: { DeviceInformation* _r = _t->pDeviceInformation();
            if (_a[0]) *reinterpret_cast< DeviceInformation**>(_a[0]) = std::move(_r); }  break;
        case 6: { Manual* _r = _t->pManual();
            if (_a[0]) *reinterpret_cast< Manual**>(_a[0]) = std::move(_r); }  break;
        case 7: { System* _r = _t->pSystem();
            if (_a[0]) *reinterpret_cast< System**>(_a[0]) = std::move(_r); }  break;
        case 8: { IO* _r = _t->pIO();
            if (_a[0]) *reinterpret_cast< IO**>(_a[0]) = std::move(_r); }  break;
        case 9: { Trend* _r = _t->pTrend();
            if (_a[0]) *reinterpret_cast< Trend**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Device::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::pProductionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Device::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::pSystemChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Device::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::pYieldTrendChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Device::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::pIOChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Device::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Device::pTrendChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Device *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< DeviceInformation**>(_v) = _t->pDeviceInformation(); break;
        case 1: *reinterpret_cast< IO**>(_v) = _t->pIO(); break;
        case 2: *reinterpret_cast< Manual**>(_v) = _t->pManual(); break;
        case 3: *reinterpret_cast< System**>(_v) = _t->pSystem(); break;
        case 4: *reinterpret_cast< Trend**>(_v) = _t->pTrend(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Device::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Device.data,
    qt_meta_data_Device,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Device::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Device::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Device.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Device::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Device::pProductionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Device::pSystemChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Device::pYieldTrendChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Device::pIOChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Device::pTrendChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
