/****************************************************************************
** Meta object code from reading C++ file 'manual.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../modbusNov12/OnlineMonitor/model/manual.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'manual.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Manual_t {
    QByteArrayData data[14];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Manual_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Manual_t qt_meta_stringdata_Manual = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Manual"
QT_MOC_LITERAL(1, 7, 8), // "rowCount"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 29, 6), // "parent"
QT_MOC_LITERAL(5, 36, 4), // "data"
QT_MOC_LITERAL(6, 41, 5), // "index"
QT_MOC_LITERAL(7, 47, 4), // "role"
QT_MOC_LITERAL(8, 52, 9), // "roleNames"
QT_MOC_LITERAL(9, 62, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(10, 84, 7), // "setData"
QT_MOC_LITERAL(11, 92, 5), // "value"
QT_MOC_LITERAL(12, 98, 4), // "save"
QT_MOC_LITERAL(13, 103, 9) // "clearData"

    },
    "Manual\0rowCount\0\0QModelIndex\0parent\0"
    "data\0index\0role\0roleNames\0"
    "QHash<int,QByteArray>\0setData\0value\0"
    "save\0clearData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Manual[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x02 /* Public */,
       5,    2,   52,    2, 0x02 /* Public */,
       8,    0,   57,    2, 0x02 /* Public */,
      10,    3,   58,    2, 0x02 /* Public */,
      10,    2,   65,    2, 0x22 /* Public | MethodCloned */,
      12,    0,   70,    2, 0x02 /* Public */,
      13,    0,   71,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::QVariant, 0x80000000 | 3, QMetaType::Int,    6,    7,
    0x80000000 | 9,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QVariant, QMetaType::Int,    6,   11,    7,
    QMetaType::Bool, 0x80000000 | 3, QMetaType::QVariant,    6,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Manual::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Manual *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: { QHash<int,QByteArray> _r = _t->roleNames();
            if (_a[0]) *reinterpret_cast< QHash<int,QByteArray>*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->setData((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->setData((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->save(); break;
        case 6: _t->clearData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Manual::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_Manual.data,
    qt_meta_data_Manual,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Manual::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Manual::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Manual.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int Manual::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
