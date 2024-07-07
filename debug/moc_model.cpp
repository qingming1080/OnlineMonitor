/****************************************************************************
** Meta object code from reading C++ file 'model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../model/model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Model_t {
    QByteArrayData data[17];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Model_t qt_meta_stringdata_Model = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Model"
QT_MOC_LITERAL(1, 6, 8), // "rowCount"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 28, 6), // "parent"
QT_MOC_LITERAL(5, 35, 4), // "data"
QT_MOC_LITERAL(6, 40, 5), // "index"
QT_MOC_LITERAL(7, 46, 4), // "role"
QT_MOC_LITERAL(8, 51, 9), // "roleNames"
QT_MOC_LITERAL(9, 61, 21), // "QHash<int,QByteArray>"
QT_MOC_LITERAL(10, 83, 22), // "getModelDataByWelderID"
QT_MOC_LITERAL(11, 106, 8), // "welderID"
QT_MOC_LITERAL(12, 115, 12), // "setModelData"
QT_MOC_LITERAL(13, 128, 2), // "id"
QT_MOC_LITERAL(14, 131, 13), // "_MODEL_COLUMN"
QT_MOC_LITERAL(15, 145, 6), // "column"
QT_MOC_LITERAL(16, 152, 4) // "save"

    },
    "Model\0rowCount\0\0QModelIndex\0parent\0"
    "data\0index\0role\0roleNames\0"
    "QHash<int,QByteArray>\0getModelDataByWelderID\0"
    "welderID\0setModelData\0id\0_MODEL_COLUMN\0"
    "column\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Model[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x02 /* Public */,
       5,    2,   47,    2, 0x02 /* Public */,
       8,    0,   52,    2, 0x02 /* Public */,
      10,    2,   53,    2, 0x02 /* Public */,
      12,    3,   58,    2, 0x02 /* Public */,
      16,    0,   65,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::QVariant, 0x80000000 | 3, QMetaType::Int,    6,    7,
    0x80000000 | 9,
    QMetaType::QVariant, QMetaType::Int, QMetaType::Int,   11,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, QMetaType::QVariant,   13,   15,    5,
    QMetaType::Void,

       0        // eod
};

void Model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 2: { QHash<int,QByteArray> _r = _t->roleNames();
            if (_a[0]) *reinterpret_cast< QHash<int,QByteArray>*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->getModelDataByWelderID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->setModelData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< _MODEL_COLUMN(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 5: _t->save(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Model::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_Model.data,
    qt_meta_data_Model,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Model::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Model.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int Model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
