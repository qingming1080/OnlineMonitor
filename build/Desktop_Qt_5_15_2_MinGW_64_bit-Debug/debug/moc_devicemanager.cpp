/****************************************************************************
** Meta object code from reading C++ file 'devicemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../devicemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devicemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceManager_t {
    QByteArrayData data[27];
    char stringdata0[286];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceManager_t qt_meta_stringdata_DeviceManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DeviceManager"
QT_MOC_LITERAL(1, 14, 16), // "deviceNumChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "deviceListChanged"
QT_MOC_LITERAL(4, 50, 10), // "upDateBtns"
QT_MOC_LITERAL(5, 61, 10), // "deviceList"
QT_MOC_LITERAL(6, 72, 14), // "QList<Device*>"
QT_MOC_LITERAL(7, 87, 9), // "addDevice"
QT_MOC_LITERAL(8, 97, 8), // "maxBacth"
QT_MOC_LITERAL(9, 106, 6), // "sample"
QT_MOC_LITERAL(10, 113, 10), // "lowerLimit"
QT_MOC_LITERAL(11, 124, 4), // "port"
QT_MOC_LITERAL(12, 129, 8), // "targetIp"
QT_MOC_LITERAL(13, 138, 7), // "localIp"
QT_MOC_LITERAL(14, 146, 12), // "heightOption"
QT_MOC_LITERAL(15, 159, 4), // "name"
QT_MOC_LITERAL(16, 164, 5), // "model"
QT_MOC_LITERAL(17, 170, 11), // "connectType"
QT_MOC_LITERAL(18, 182, 2), // "id"
QT_MOC_LITERAL(19, 185, 12), // "removeDevice"
QT_MOC_LITERAL(20, 198, 8), // "welderID"
QT_MOC_LITERAL(21, 207, 9), // "deviceNum"
QT_MOC_LITERAL(22, 217, 16), // "getPasswordLevel"
QT_MOC_LITERAL(23, 234, 8), // "password"
QT_MOC_LITERAL(24, 243, 15), // "setUserPassword"
QT_MOC_LITERAL(25, 259, 11), // "newPassword"
QT_MOC_LITERAL(26, 271, 14) // "getHistoryName"

    },
    "DeviceManager\0deviceNumChanged\0\0"
    "deviceListChanged\0upDateBtns\0deviceList\0"
    "QList<Device*>\0addDevice\0maxBacth\0"
    "sample\0lowerLimit\0port\0targetIp\0localIp\0"
    "heightOption\0name\0model\0connectType\0"
    "id\0removeDevice\0welderID\0deviceNum\0"
    "getPasswordLevel\0password\0setUserPassword\0"
    "newPassword\0getHistoryName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       2,  104, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    0,   67,    2, 0x02 /* Public */,
       7,   11,   68,    2, 0x02 /* Public */,
      19,    1,   91,    2, 0x02 /* Public */,
      21,    0,   94,    2, 0x02 /* Public */,
      22,    1,   95,    2, 0x02 /* Public */,
      24,    1,   98,    2, 0x02 /* Public */,
      26,    1,  101,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,    8,    9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::QString, QMetaType::Int,   20,

 // properties: name, type, flags
       5, 0x80000000 | 6, 0x00495009,
      21, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       1,
       0,

       0        // eod
};

void DeviceManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceNumChanged(); break;
        case 1: _t->deviceListChanged(); break;
        case 2: _t->upDateBtns(); break;
        case 3: { QList<Device*> _r = _t->deviceList();
            if (_a[0]) *reinterpret_cast< QList<Device*>*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->addDevice((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3])),(*reinterpret_cast< const int(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< const int(*)>(_a[7])),(*reinterpret_cast< const QString(*)>(_a[8])),(*reinterpret_cast< const QString(*)>(_a[9])),(*reinterpret_cast< const int(*)>(_a[10])),(*reinterpret_cast< const int(*)>(_a[11]))); break;
        case 5: _t->removeDevice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { int _r = _t->deviceNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->getPasswordLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setUserPassword((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->getHistoryName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::deviceNumChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::deviceListChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceManager::upDateBtns)) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<Device*> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceManager *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<Device*>*>(_v) = _t->deviceList(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->deviceNum(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject DeviceManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceManager.data,
    qt_meta_data_DeviceManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeviceManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceManager::deviceNumChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceManager::deviceListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceManager::upDateBtns()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
