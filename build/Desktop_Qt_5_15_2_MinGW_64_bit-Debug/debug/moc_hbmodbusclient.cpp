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
    QByteArrayData data[28];
    char stringdata0[318];
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
QT_MOC_LITERAL(5, 49, 13), // "onModbusError"
QT_MOC_LITERAL(6, 63, 20), // "QModbusDevice::Error"
QT_MOC_LITERAL(7, 84, 5), // "error"
QT_MOC_LITERAL(8, 90, 16), // "attemptReconnect"
QT_MOC_LITERAL(9, 107, 14), // "readModbusData"
QT_MOC_LITERAL(10, 122, 14), // "CoilsReadyRead"
QT_MOC_LITERAL(11, 137, 17), // "HoldingsReadyRead"
QT_MOC_LITERAL(12, 155, 15), // "InputsReadyRead"
QT_MOC_LITERAL(13, 171, 19), // "DiscretedsReadyRead"
QT_MOC_LITERAL(14, 191, 17), // "coilWriteFinished"
QT_MOC_LITERAL(15, 209, 18), // "onDeviceNumChanged"
QT_MOC_LITERAL(16, 228, 5), // "setIO"
QT_MOC_LITERAL(17, 234, 8), // "deviceID"
QT_MOC_LITERAL(18, 243, 14), // "DEV_WELD_ALARM"
QT_MOC_LITERAL(19, 258, 12), // "writeSetTime"
QT_MOC_LITERAL(20, 271, 4), // "year"
QT_MOC_LITERAL(21, 276, 5), // "month"
QT_MOC_LITERAL(22, 282, 3), // "day"
QT_MOC_LITERAL(23, 286, 4), // "hour"
QT_MOC_LITERAL(24, 291, 6), // "minute"
QT_MOC_LITERAL(25, 298, 6), // "second"
QT_MOC_LITERAL(26, 305, 6), // "setLED"
QT_MOC_LITERAL(27, 312, 5) // "state"

    },
    "HBModbusClient\0dataReceived\0\0QVector<int>\0"
    "result\0onModbusError\0QModbusDevice::Error\0"
    "error\0attemptReconnect\0readModbusData\0"
    "CoilsReadyRead\0HoldingsReadyRead\0"
    "InputsReadyRead\0DiscretedsReadyRead\0"
    "coilWriteFinished\0onDeviceNumChanged\0"
    "setIO\0deviceID\0DEV_WELD_ALARM\0"
    "writeSetTime\0year\0month\0day\0hour\0"
    "minute\0second\0setLED\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HBModbusClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   82,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      16,    2,   93,    2, 0x02 /* Public */,
      19,    6,   98,    2, 0x02 /* Public */,
      26,    1,  111,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   20,   21,   22,   23,   24,   25,
    QMetaType::Void, QMetaType::Bool,   27,

       0        // eod
};

void HBModbusClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HBModbusClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QVector<int>(*)>(_a[1]))); break;
        case 1: _t->onModbusError((*reinterpret_cast< QModbusDevice::Error(*)>(_a[1]))); break;
        case 2: _t->attemptReconnect(); break;
        case 3: _t->readModbusData(); break;
        case 4: _t->CoilsReadyRead(); break;
        case 5: _t->HoldingsReadyRead(); break;
        case 6: _t->InputsReadyRead(); break;
        case 7: _t->DiscretedsReadyRead(); break;
        case 8: _t->coilWriteFinished(); break;
        case 9: _t->onDeviceNumChanged(); break;
        case 10: _t->setIO((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->writeSetTime((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 12: _t->setLED((*reinterpret_cast< bool(*)>(_a[1]))); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void HBModbusClient::dataReceived(const QVector<int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
