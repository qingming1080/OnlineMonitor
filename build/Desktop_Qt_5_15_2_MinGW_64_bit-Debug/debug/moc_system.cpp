/****************************************************************************
** Meta object code from reading C++ file 'system.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../model/system.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'system.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_System_t {
    QByteArrayData data[22];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_System_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_System_t qt_meta_stringdata_System = {
    {
QT_MOC_LITERAL(0, 0, 6), // "System"
QT_MOC_LITERAL(1, 7, 9), // "idChanged"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 17), // "singleFactChanged"
QT_MOC_LITERAL(4, 36, 18), // "generalFactChanged"
QT_MOC_LITERAL(5, 55, 16), // "otherFaceChanged"
QT_MOC_LITERAL(6, 72, 16), // "autoModelChanged"
QT_MOC_LITERAL(7, 89, 2), // "id"
QT_MOC_LITERAL(8, 92, 5), // "setId"
QT_MOC_LITERAL(9, 98, 5), // "newId"
QT_MOC_LITERAL(10, 104, 10), // "singleFact"
QT_MOC_LITERAL(11, 115, 13), // "setSingleFact"
QT_MOC_LITERAL(12, 129, 13), // "newSingleFact"
QT_MOC_LITERAL(13, 143, 11), // "generalFact"
QT_MOC_LITERAL(14, 155, 14), // "setGeneralFact"
QT_MOC_LITERAL(15, 170, 14), // "newGeneralFact"
QT_MOC_LITERAL(16, 185, 9), // "otherFace"
QT_MOC_LITERAL(17, 195, 12), // "setOtherFace"
QT_MOC_LITERAL(18, 208, 12), // "newOtherFace"
QT_MOC_LITERAL(19, 221, 9), // "autoModel"
QT_MOC_LITERAL(20, 231, 12), // "setAutoModel"
QT_MOC_LITERAL(21, 244, 12) // "newAutoModel"

    },
    "System\0idChanged\0\0singleFactChanged\0"
    "generalFactChanged\0otherFaceChanged\0"
    "autoModelChanged\0id\0setId\0newId\0"
    "singleFact\0setSingleFact\0newSingleFact\0"
    "generalFact\0setGeneralFact\0newGeneralFact\0"
    "otherFace\0setOtherFace\0newOtherFace\0"
    "autoModel\0setAutoModel\0newAutoModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_System[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       5,  114, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,
       4,    0,   91,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   94,    2, 0x02 /* Public */,
       8,    1,   95,    2, 0x02 /* Public */,
      10,    0,   98,    2, 0x02 /* Public */,
      11,    1,   99,    2, 0x02 /* Public */,
      13,    0,  102,    2, 0x02 /* Public */,
      14,    1,  103,    2, 0x02 /* Public */,
      16,    0,  106,    2, 0x02 /* Public */,
      17,    1,  107,    2, 0x02 /* Public */,
      19,    0,  110,    2, 0x02 /* Public */,
      20,    1,  111,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   21,

 // properties: name, type, flags
       7, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00495103,
      13, QMetaType::Int, 0x00495103,
      16, QMetaType::Int, 0x00495103,
      19, QMetaType::Int, 0x00495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,

       0        // eod
};

void System::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<System *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->idChanged(); break;
        case 1: _t->singleFactChanged(); break;
        case 2: _t->generalFactChanged(); break;
        case 3: _t->otherFaceChanged(); break;
        case 4: _t->autoModelChanged(); break;
        case 5: { int _r = _t->id();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->setId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: { int _r = _t->singleFact();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->setSingleFact((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: { int _r = _t->generalFact();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setGeneralFact((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { int _r = _t->otherFace();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setOtherFace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { int _r = _t->autoModel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setAutoModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (System::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&System::idChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (System::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&System::singleFactChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (System::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&System::generalFactChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (System::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&System::otherFaceChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (System::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&System::autoModelChanged)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<System *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->singleFact(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->generalFact(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->otherFace(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->autoModel(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<System *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setSingleFact(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setGeneralFact(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setOtherFace(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setAutoModel(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject System::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_System.data,
    qt_meta_data_System,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *System::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *System::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_System.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int System::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
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

// SIGNAL 0
void System::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void System::singleFactChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void System::generalFactChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void System::otherFaceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void System::autoModelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
