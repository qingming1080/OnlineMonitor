/****************************************************************************
** Meta object code from reading C++ file 'weldtrend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../model/weldtrend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weldtrend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WeldTrend_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WeldTrend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WeldTrend_t qt_meta_stringdata_WeldTrend = {
    {
QT_MOC_LITERAL(0, 0, 9), // "WeldTrend"
QT_MOC_LITERAL(1, 10, 12), // "pBeforeModel"
QT_MOC_LITERAL(2, 23, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(3, 43, 0), // ""
QT_MOC_LITERAL(4, 44, 11), // "pAfterModel"
QT_MOC_LITERAL(5, 56, 10), // "pTimeModel"
QT_MOC_LITERAL(6, 67, 11) // "pPowerModel"

    },
    "WeldTrend\0pBeforeModel\0QStandardItemModel*\0"
    "\0pAfterModel\0pTimeModel\0pPowerModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WeldTrend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   34,    3, 0x02 /* Public */,
       4,    0,   35,    3, 0x02 /* Public */,
       5,    0,   36,    3, 0x02 /* Public */,
       6,    0,   37,    3, 0x02 /* Public */,

 // methods: parameters
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00095009,
       4, 0x80000000 | 2, 0x00095009,
       5, 0x80000000 | 2, 0x00095009,
       6, 0x80000000 | 2, 0x00095009,

       0        // eod
};

void WeldTrend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WeldTrend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QStandardItemModel* _r = _t->pBeforeModel();
            if (_a[0]) *reinterpret_cast< QStandardItemModel**>(_a[0]) = std::move(_r); }  break;
        case 1: { QStandardItemModel* _r = _t->pAfterModel();
            if (_a[0]) *reinterpret_cast< QStandardItemModel**>(_a[0]) = std::move(_r); }  break;
        case 2: { QStandardItemModel* _r = _t->pTimeModel();
            if (_a[0]) *reinterpret_cast< QStandardItemModel**>(_a[0]) = std::move(_r); }  break;
        case 3: { QStandardItemModel* _r = _t->pPowerModel();
            if (_a[0]) *reinterpret_cast< QStandardItemModel**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WeldTrend *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pBeforeModel(); break;
        case 1: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pAfterModel(); break;
        case 2: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pTimeModel(); break;
        case 3: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pPowerModel(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject WeldTrend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WeldTrend.data,
    qt_meta_data_WeldTrend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WeldTrend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WeldTrend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WeldTrend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WeldTrend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
