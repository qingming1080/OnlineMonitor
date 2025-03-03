/****************************************************************************
** Meta object code from reading C++ file 'history.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../modbusNov12/OnlineMonitor/model/history.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'history.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_History_t {
    QByteArrayData data[20];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_History_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_History_t qt_meta_stringdata_History = {
    {
QT_MOC_LITERAL(0, 0, 7), // "History"
QT_MOC_LITERAL(1, 8, 15), // "deviceIDChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 18), // "finalResultChanged"
QT_MOC_LITERAL(4, 44, 8), // "rowCount"
QT_MOC_LITERAL(5, 53, 11), // "QModelIndex"
QT_MOC_LITERAL(6, 65, 6), // "parent"
QT_MOC_LITERAL(7, 72, 4), // "data"
QT_MOC_LITERAL(8, 77, 5), // "index"
QT_MOC_LITERAL(9, 83, 4), // "role"
QT_MOC_LITERAL(10, 88, 9), // "roleNames"
QT_MOC_LITERAL(11, 98, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(12, 120, 11), // "setWelderID"
QT_MOC_LITERAL(13, 132, 8), // "welderID"
QT_MOC_LITERAL(14, 141, 8), // "deviceID"
QT_MOC_LITERAL(15, 150, 11), // "setDeviceID"
QT_MOC_LITERAL(16, 162, 11), // "newDeviceID"
QT_MOC_LITERAL(17, 174, 11), // "finalResult"
QT_MOC_LITERAL(18, 186, 14), // "setFinalResult"
QT_MOC_LITERAL(19, 201, 14) // "newFinalResult"

    },
    "History\0deviceIDChanged\0\0finalResultChanged\0"
    "rowCount\0QModelIndex\0parent\0data\0index\0"
    "role\0roleNames\0QHash<int,QByteArray>\0"
    "setWelderID\0welderID\0deviceID\0setDeviceID\0"
    "newDeviceID\0finalResult\0setFinalResult\0"
    "newFinalResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_History[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       2,   92, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    1,   71,    2, 0x02 /* Public */,
       7,    2,   74,    2, 0x02 /* Public */,
      10,    0,   79,    2, 0x02 /* Public */,
      12,    1,   80,    2, 0x02 /* Public */,
      12,    0,   83,    2, 0x22 /* Public | MethodCloned */,
      14,    0,   84,    2, 0x02 /* Public */,
      15,    1,   85,    2, 0x02 /* Public */,
      17,    0,   88,    2, 0x02 /* Public */,
      18,    1,   89,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 5,    6,
    QMetaType::QVariant, 0x80000000 | 5, QMetaType::Int,    8,    9,
    0x80000000 | 11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   19,

 // properties: name, type, flags
      14, QMetaType::Int, 0x00495103,
      17, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void History::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<History *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceIDChanged(); break;
        case 1: _t->finalResultChanged(); break;
        case 2: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: { QHash<int,QByteArray> _r = _t->roleNames();
            if (_a[0]) *reinterpret_cast< QHash<int,QByteArray>*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setWelderID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setWelderID(); break;
        case 7: { int _r = _t->deviceID();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setDeviceID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: { int _r = _t->finalResult();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setFinalResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (History::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&History::deviceIDChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (History::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&History::finalResultChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<History *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->deviceID(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->finalResult(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<History *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDeviceID(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setFinalResult(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject History::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_History.data,
    qt_meta_data_History,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *History::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *History::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_History.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int History::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
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
void History::deviceIDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void History::finalResultChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
