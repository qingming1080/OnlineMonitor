/****************************************************************************
** Meta object code from reading C++ file 'qmlenum.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qmlenum.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmlenum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QmlEnum_t {
    QByteArrayData data[11];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QmlEnum_t qt_meta_stringdata_QmlEnum = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QmlEnum"
QT_MOC_LITERAL(1, 8, 13), // "_PRODUCTSTATE"
QT_MOC_LITERAL(2, 22, 22), // "PRODUCTSTATE_Excelleng"
QT_MOC_LITERAL(3, 45, 23), // "PRODUCTSTATE_Difference"
QT_MOC_LITERAL(4, 69, 12), // "_CONNECTTYPE"
QT_MOC_LITERAL(5, 82, 20), // "_CONNECTTYPE_Network"
QT_MOC_LITERAL(6, 103, 18), // "_CONNECTTYPE_RS232"
QT_MOC_LITERAL(7, 122, 7), // "_SIGNAL"
QT_MOC_LITERAL(8, 130, 13), // "_SIGNAL_alarm"
QT_MOC_LITERAL(9, 144, 13), // "_SIGNAL_reset"
QT_MOC_LITERAL(10, 158, 18) // "_SIGNAL_noDefinite"

    },
    "QmlEnum\0_PRODUCTSTATE\0PRODUCTSTATE_Excelleng\0"
    "PRODUCTSTATE_Difference\0_CONNECTTYPE\0"
    "_CONNECTTYPE_Network\0_CONNECTTYPE_RS232\0"
    "_SIGNAL\0_SIGNAL_alarm\0_SIGNAL_reset\0"
    "_SIGNAL_noDefinite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlEnum[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   29,
       4,    4, 0x0,    2,   33,
       7,    7, 0x0,    3,   37,

 // enum data: key, value
       2, uint(QmlEnum::PRODUCTSTATE_Excelleng),
       3, uint(QmlEnum::PRODUCTSTATE_Difference),
       5, uint(QmlEnum::_CONNECTTYPE_Network),
       6, uint(QmlEnum::_CONNECTTYPE_RS232),
       8, uint(QmlEnum::_SIGNAL_alarm),
       9, uint(QmlEnum::_SIGNAL_reset),
      10, uint(QmlEnum::_SIGNAL_noDefinite),

       0        // eod
};

void QmlEnum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject QmlEnum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QmlEnum.data,
    qt_meta_data_QmlEnum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QmlEnum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QmlEnum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QmlEnum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QmlEnum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
