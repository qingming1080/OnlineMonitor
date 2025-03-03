/****************************************************************************
** Meta object code from reading C++ file 'networkmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../modbusNov12/OnlineMonitor/model/networkmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkModel_t {
    QByteArrayData data[15];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkModel_t qt_meta_stringdata_NetworkModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NetworkModel"
QT_MOC_LITERAL(1, 13, 8), // "rowCount"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 35, 6), // "parent"
QT_MOC_LITERAL(5, 42, 4), // "data"
QT_MOC_LITERAL(6, 47, 5), // "index"
QT_MOC_LITERAL(7, 53, 4), // "role"
QT_MOC_LITERAL(8, 58, 9), // "roleNames"
QT_MOC_LITERAL(9, 68, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(10, 90, 17), // "getDataByWelderID"
QT_MOC_LITERAL(11, 108, 8), // "welderID"
QT_MOC_LITERAL(12, 117, 14), // "setNetworkData"
QT_MOC_LITERAL(13, 132, 2), // "id"
QT_MOC_LITERAL(14, 135, 6) // "column"

    },
    "NetworkModel\0rowCount\0\0QModelIndex\0"
    "parent\0data\0index\0role\0roleNames\0"
    "QHash<int,QByteArray>\0getDataByWelderID\0"
    "welderID\0setNetworkData\0id\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x02 /* Public */,
       5,    2,   42,    2, 0x02 /* Public */,
       8,    0,   47,    2, 0x02 /* Public */,
      10,    2,   48,    2, 0x02 /* Public */,
      12,    3,   53,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::QVariant, 0x80000000 | 3, QMetaType::Int,    6,    7,
    0x80000000 | 9,
    QMetaType::QVariant, QMetaType::Int, QMetaType::Int,   11,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QVariant,   13,   14,    5,

       0        // eod
};

void NetworkModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: { QHash<int,QByteArray> _r = _t->roleNames();
            if (_a[0]) *reinterpret_cast< QHash<int,QByteArray>*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->getDataByWelderID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setNetworkData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_NetworkModel.data,
    qt_meta_data_NetworkModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int NetworkModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
