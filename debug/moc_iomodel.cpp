/****************************************************************************
** Meta object code from reading C++ file 'iomodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../model/iomodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iomodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IOModel_t {
    QByteArrayData data[16];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IOModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IOModel_t qt_meta_stringdata_IOModel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "IOModel"
QT_MOC_LITERAL(1, 8, 8), // "rowCount"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 30, 6), // "parent"
QT_MOC_LITERAL(5, 37, 4), // "data"
QT_MOC_LITERAL(6, 42, 5), // "index"
QT_MOC_LITERAL(7, 48, 4), // "role"
QT_MOC_LITERAL(8, 53, 9), // "roleNames"
QT_MOC_LITERAL(9, 63, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(10, 85, 17), // "getDataByWelderID"
QT_MOC_LITERAL(11, 103, 8), // "welderID"
QT_MOC_LITERAL(12, 112, 9), // "setIOData"
QT_MOC_LITERAL(13, 122, 2), // "id"
QT_MOC_LITERAL(14, 125, 10), // "_IO_COLUMN"
QT_MOC_LITERAL(15, 136, 6) // "column"

    },
    "IOModel\0rowCount\0\0QModelIndex\0parent\0"
    "data\0index\0role\0roleNames\0"
    "QHash<int,QByteArray>\0getDataByWelderID\0"
    "welderID\0setIOData\0id\0_IO_COLUMN\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IOModel[] = {

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
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, QMetaType::QVariant,   13,   15,    5,

       0        // eod
};

void IOModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IOModel *>(_o);
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
        case 4: _t->setIOData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< _IO_COLUMN(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IOModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_IOModel.data,
    qt_meta_data_IOModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IOModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IOModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IOModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int IOModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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