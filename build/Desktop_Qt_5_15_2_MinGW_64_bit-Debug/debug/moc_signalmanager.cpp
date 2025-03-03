/****************************************************************************
** Meta object code from reading C++ file 'signalmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../signalmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signalmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SignalManager_t {
    QByteArrayData data[7];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SignalManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SignalManager_t qt_meta_stringdata_SignalManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SignalManager"
QT_MOC_LITERAL(1, 14, 15), // "signalAddRecord"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "time"
QT_MOC_LITERAL(4, 36, 4), // "text"
QT_MOC_LITERAL(5, 41, 10), // "showLegend"
QT_MOC_LITERAL(6, 52, 20) // "changeYieldTrendData"

    },
    "SignalManager\0signalAddRecord\0\0time\0"
    "text\0showLegend\0changeYieldTrendData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SignalManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    0,   34,    2, 0x06 /* Public */,
       6,    0,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QDateTime, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SignalManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SignalManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalAddRecord((*reinterpret_cast< const QDateTime(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->showLegend(); break;
        case 2: _t->changeYieldTrendData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SignalManager::*)(const QDateTime & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SignalManager::signalAddRecord)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SignalManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SignalManager::showLegend)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SignalManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SignalManager::changeYieldTrendData)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SignalManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SignalManager.data,
    qt_meta_data_SignalManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SignalManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignalManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SignalManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SignalManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void SignalManager::signalAddRecord(const QDateTime & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SignalManager::showLegend()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SignalManager::changeYieldTrendData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
