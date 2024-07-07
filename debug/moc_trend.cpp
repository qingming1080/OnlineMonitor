/****************************************************************************
** Meta object code from reading C++ file 'trend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../model/trend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Trend_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Trend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Trend_t qt_meta_stringdata_Trend = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Trend"
QT_MOC_LITERAL(1, 6, 12), // "pBeforeModel"
QT_MOC_LITERAL(2, 19, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(3, 39, 0), // ""
QT_MOC_LITERAL(4, 40, 11), // "pAfterModel"
QT_MOC_LITERAL(5, 52, 10), // "pTimeModel"
QT_MOC_LITERAL(6, 63, 11), // "pPowerModel"
QT_MOC_LITERAL(7, 75, 11) // "pYieldTrend"

    },
    "Trend\0pBeforeModel\0QStandardItemModel*\0"
    "\0pAfterModel\0pTimeModel\0pPowerModel\0"
    "pYieldTrend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Trend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   39,    3, 0x02 /* Public */,
       4,    0,   40,    3, 0x02 /* Public */,
       5,    0,   41,    3, 0x02 /* Public */,
       6,    0,   42,    3, 0x02 /* Public */,
       7,    0,   43,    3, 0x02 /* Public */,

 // methods: parameters
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00095009,
       4, 0x80000000 | 2, 0x00095009,
       5, 0x80000000 | 2, 0x00095009,
       6, 0x80000000 | 2, 0x00095009,
       7, 0x80000000 | 2, 0x00095009,

       0        // eod
};

void Trend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Trend *>(_o);
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
        case 4: { QStandardItemModel* _r = _t->pYieldTrend();
            if (_a[0]) *reinterpret_cast< QStandardItemModel**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Trend *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pBeforeModel(); break;
        case 1: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pAfterModel(); break;
        case 2: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pTimeModel(); break;
        case 3: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pPowerModel(); break;
        case 4: *reinterpret_cast< QStandardItemModel**>(_v) = _t->pYieldTrend(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Trend::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Trend.data,
    qt_meta_data_Trend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Trend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Trend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Trend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Trend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
