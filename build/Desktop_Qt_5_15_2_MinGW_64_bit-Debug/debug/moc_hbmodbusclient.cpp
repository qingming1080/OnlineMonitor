/****************************************************************************
** Meta object code from reading C++ file 'hbmodbusclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../modbus/hbmodbusclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hbmodbusclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HBModbusClient_t {
    QByteArrayData data[31];
    char stringdata0[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HBModbusClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HBModbusClient_t qt_meta_stringdata_HBModbusClient = {
    {
QT_MOC_LITERAL(0, 0, 14), // "HBModbusClient"
QT_MOC_LITERAL(1, 15, 12), // "dataReceived"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QVector<int>"
QT_MOC_LITERAL(4, 42, 6), // "result"
QT_MOC_LITERAL(5, 49, 11), // "reconnected"
QT_MOC_LITERAL(6, 61, 13), // "onModbusError"
QT_MOC_LITERAL(7, 75, 20), // "QModbusDevice::Error"
QT_MOC_LITERAL(8, 96, 5), // "error"
QT_MOC_LITERAL(9, 102, 20), // "onModbusStateChanged"
QT_MOC_LITERAL(10, 123, 20), // "QModbusDevice::State"
QT_MOC_LITERAL(11, 144, 5), // "state"
QT_MOC_LITERAL(12, 150, 16), // "attemptReconnect"
QT_MOC_LITERAL(13, 167, 14), // "readModbusData"
QT_MOC_LITERAL(14, 182, 14), // "CoilsReadyRead"
QT_MOC_LITERAL(15, 197, 17), // "HoldingsReadyRead"
QT_MOC_LITERAL(16, 215, 15), // "InputsReadyRead"
QT_MOC_LITERAL(17, 231, 19), // "DiscretedsReadyRead"
QT_MOC_LITERAL(18, 251, 17), // "coilWriteFinished"
QT_MOC_LITERAL(19, 269, 18), // "onDeviceNumChanged"
QT_MOC_LITERAL(20, 288, 5), // "setIO"
QT_MOC_LITERAL(21, 294, 8), // "deviceID"
QT_MOC_LITERAL(22, 303, 14), // "DEV_WELD_ALARM"
QT_MOC_LITERAL(23, 318, 12), // "writeSetTime"
QT_MOC_LITERAL(24, 331, 4), // "year"
QT_MOC_LITERAL(25, 336, 5), // "month"
QT_MOC_LITERAL(26, 342, 3), // "day"
QT_MOC_LITERAL(27, 346, 4), // "hour"
QT_MOC_LITERAL(28, 351, 6), // "minute"
QT_MOC_LITERAL(29, 358, 6), // "second"
QT_MOC_LITERAL(30, 365, 6) // "setLED"

    },
    "HBModbusClient\0dataReceived\0\0QVector<int>\0"
    "result\0reconnected\0onModbusError\0"
    "QModbusDevice::Error\0error\0"
    "onModbusStateChanged\0QModbusDevice::State\0"
    "state\0attemptReconnect\0readModbusData\0"
    "CoilsReadyRead\0HoldingsReadyRead\0"
    "InputsReadyRead\0DiscretedsReadyRead\0"
    "coilWriteFinished\0onDeviceNumChanged\0"
    "setIO\0deviceID\0DEV_WELD_ALARM\0"
    "writeSetTime\0year\0month\0day\0hour\0"
    "minute\0second\0setLED"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HBModbusClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   93,    2, 0x0a /* Public */,
       9,    1,   96,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    0,  104,    2, 0x0a /* Public */,
      18,    0,  105,    2, 0x0a /* Public */,
      19,    0,  106,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      20,    2,  107,    2, 0x02 /* Public */,
      23,    6,  112,    2, 0x02 /* Public */,
      30,    1,  125,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   24,   25,   26,   27,   28,   29,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

void HBModbusClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HBModbusClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QVector<int>(*)>(_a[1]))); break;
        case 1: _t->reconnected(); break;
        case 2: _t->onModbusError((*reinterpret_cast< QModbusDevice::Error(*)>(_a[1]))); break;
        case 3: _t->onModbusStateChanged((*reinterpret_cast< QModbusDevice::State(*)>(_a[1]))); break;
        case 4: _t->attemptReconnect(); break;
        case 5: _t->readModbusData(); break;
        case 6: _t->CoilsReadyRead(); break;
        case 7: _t->HoldingsReadyRead(); break;
        case 8: _t->InputsReadyRead(); break;
        case 9: _t->DiscretedsReadyRead(); break;
        case 10: _t->coilWriteFinished(); break;
        case 11: _t->onDeviceNumChanged(); break;
        case 12: _t->setIO((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->writeSetTime((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 14: _t->setLED((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HBModbusClient::*)(const QVector<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HBModbusClient::dataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HBModbusClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HBModbusClient::reconnected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HBModbusClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HBModbusClient.data,
    qt_meta_data_HBModbusClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HBModbusClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HBModbusClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HBModbusClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HBModbusClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void HBModbusClient::dataReceived(const QVector<int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HBModbusClient::reconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
