/****************************************************************************
** Meta object code from reading C++ file 'deviceinformation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../model/deviceinformation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deviceinformation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeviceInformation_t {
    QByteArrayData data[83];
    char stringdata0[1010];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeviceInformation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeviceInformation_t qt_meta_stringdata_DeviceInformation = {
    {
QT_MOC_LITERAL(0, 0, 17), // "DeviceInformation"
QT_MOC_LITERAL(1, 18, 11), // "nameChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "modelChanged"
QT_MOC_LITERAL(4, 44, 18), // "connectTypeChanged"
QT_MOC_LITERAL(5, 63, 12), // "stateChanged"
QT_MOC_LITERAL(6, 76, 9), // "idChanged"
QT_MOC_LITERAL(7, 86, 15), // "maxBacthChanged"
QT_MOC_LITERAL(8, 102, 13), // "sampleChanged"
QT_MOC_LITERAL(9, 116, 19), // "heightOptionChanged"
QT_MOC_LITERAL(10, 136, 17), // "lowerLimitChanged"
QT_MOC_LITERAL(11, 154, 16), // "connectIDChanged"
QT_MOC_LITERAL(12, 171, 15), // "goodRateChanged"
QT_MOC_LITERAL(13, 187, 17), // "goodCyclesChanged"
QT_MOC_LITERAL(14, 205, 20), // "suspectCyclesChanged"
QT_MOC_LITERAL(15, 226, 18), // "notDefiniteChanged"
QT_MOC_LITERAL(16, 245, 12), // "powerChanged"
QT_MOC_LITERAL(17, 258, 11), // "timeChanged"
QT_MOC_LITERAL(18, 270, 13), // "energyChanged"
QT_MOC_LITERAL(19, 284, 16), // "heightPreChanged"
QT_MOC_LITERAL(20, 301, 17), // "heightPostChanged"
QT_MOC_LITERAL(21, 319, 12), // "mesIPChanged"
QT_MOC_LITERAL(22, 332, 15), // "deviceIPChanged"
QT_MOC_LITERAL(23, 348, 14), // "mesPortChanged"
QT_MOC_LITERAL(24, 363, 4), // "name"
QT_MOC_LITERAL(25, 368, 7), // "setName"
QT_MOC_LITERAL(26, 376, 7), // "newName"
QT_MOC_LITERAL(27, 384, 5), // "model"
QT_MOC_LITERAL(28, 390, 8), // "setModel"
QT_MOC_LITERAL(29, 399, 8), // "newModel"
QT_MOC_LITERAL(30, 408, 11), // "connectType"
QT_MOC_LITERAL(31, 420, 20), // "QmlEnum::CONNECTTYPE"
QT_MOC_LITERAL(32, 441, 14), // "setConnectType"
QT_MOC_LITERAL(33, 456, 14), // "newconnectType"
QT_MOC_LITERAL(34, 471, 2), // "id"
QT_MOC_LITERAL(35, 474, 8), // "maxBacth"
QT_MOC_LITERAL(36, 483, 11), // "setMaxBacth"
QT_MOC_LITERAL(37, 495, 11), // "newMaxBacth"
QT_MOC_LITERAL(38, 507, 6), // "sample"
QT_MOC_LITERAL(39, 514, 9), // "setSample"
QT_MOC_LITERAL(40, 524, 9), // "newSample"
QT_MOC_LITERAL(41, 534, 12), // "heightOption"
QT_MOC_LITERAL(42, 547, 15), // "setHeightOption"
QT_MOC_LITERAL(43, 563, 15), // "newHeightOption"
QT_MOC_LITERAL(44, 579, 10), // "lowerLimit"
QT_MOC_LITERAL(45, 590, 13), // "setLowerLimit"
QT_MOC_LITERAL(46, 604, 13), // "newLowerLimit"
QT_MOC_LITERAL(47, 618, 9), // "connectID"
QT_MOC_LITERAL(48, 628, 12), // "setConnectID"
QT_MOC_LITERAL(49, 641, 12), // "newConnectID"
QT_MOC_LITERAL(50, 654, 5), // "state"
QT_MOC_LITERAL(51, 660, 8), // "setState"
QT_MOC_LITERAL(52, 669, 8), // "newState"
QT_MOC_LITERAL(53, 678, 8), // "goodRate"
QT_MOC_LITERAL(54, 687, 11), // "setGoodRate"
QT_MOC_LITERAL(55, 699, 11), // "newGoodRate"
QT_MOC_LITERAL(56, 711, 10), // "goodCycles"
QT_MOC_LITERAL(57, 722, 13), // "setGoodCycles"
QT_MOC_LITERAL(58, 736, 13), // "newGoodCycles"
QT_MOC_LITERAL(59, 750, 13), // "suspectCycles"
QT_MOC_LITERAL(60, 764, 16), // "setSuspectCycles"
QT_MOC_LITERAL(61, 781, 16), // "newSuspectCycles"
QT_MOC_LITERAL(62, 798, 11), // "notDefinite"
QT_MOC_LITERAL(63, 810, 14), // "setNotDefinite"
QT_MOC_LITERAL(64, 825, 14), // "newNotDefinite"
QT_MOC_LITERAL(65, 840, 5), // "power"
QT_MOC_LITERAL(66, 846, 8), // "setPower"
QT_MOC_LITERAL(67, 855, 8), // "newPower"
QT_MOC_LITERAL(68, 864, 4), // "time"
QT_MOC_LITERAL(69, 869, 7), // "setTime"
QT_MOC_LITERAL(70, 877, 7), // "newTime"
QT_MOC_LITERAL(71, 885, 6), // "energy"
QT_MOC_LITERAL(72, 892, 9), // "setEnergy"
QT_MOC_LITERAL(73, 902, 9), // "newEnergy"
QT_MOC_LITERAL(74, 912, 9), // "heightPre"
QT_MOC_LITERAL(75, 922, 12), // "setHeightPre"
QT_MOC_LITERAL(76, 935, 12), // "newHeightPre"
QT_MOC_LITERAL(77, 948, 10), // "heightPost"
QT_MOC_LITERAL(78, 959, 13), // "setHeightPost"
QT_MOC_LITERAL(79, 973, 13), // "newHeightPost"
QT_MOC_LITERAL(80, 987, 5), // "mesIP"
QT_MOC_LITERAL(81, 993, 8), // "deviceIP"
QT_MOC_LITERAL(82, 1002, 7) // "mesPort"

    },
    "DeviceInformation\0nameChanged\0\0"
    "modelChanged\0connectTypeChanged\0"
    "stateChanged\0idChanged\0maxBacthChanged\0"
    "sampleChanged\0heightOptionChanged\0"
    "lowerLimitChanged\0connectIDChanged\0"
    "goodRateChanged\0goodCyclesChanged\0"
    "suspectCyclesChanged\0notDefiniteChanged\0"
    "powerChanged\0timeChanged\0energyChanged\0"
    "heightPreChanged\0heightPostChanged\0"
    "mesIPChanged\0deviceIPChanged\0"
    "mesPortChanged\0name\0setName\0newName\0"
    "model\0setModel\0newModel\0connectType\0"
    "QmlEnum::CONNECTTYPE\0setConnectType\0"
    "newconnectType\0id\0maxBacth\0setMaxBacth\0"
    "newMaxBacth\0sample\0setSample\0newSample\0"
    "heightOption\0setHeightOption\0"
    "newHeightOption\0lowerLimit\0setLowerLimit\0"
    "newLowerLimit\0connectID\0setConnectID\0"
    "newConnectID\0state\0setState\0newState\0"
    "goodRate\0setGoodRate\0newGoodRate\0"
    "goodCycles\0setGoodCycles\0newGoodCycles\0"
    "suspectCycles\0setSuspectCycles\0"
    "newSuspectCycles\0notDefinite\0"
    "setNotDefinite\0newNotDefinite\0power\0"
    "setPower\0newPower\0time\0setTime\0newTime\0"
    "energy\0setEnergy\0newEnergy\0heightPre\0"
    "setHeightPre\0newHeightPre\0heightPost\0"
    "setHeightPost\0newHeightPost\0mesIP\0"
    "deviceIP\0mesPort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeviceInformation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      59,   14, // methods
      22,  404, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      22,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  309,    2, 0x06 /* Public */,
       3,    0,  310,    2, 0x06 /* Public */,
       4,    0,  311,    2, 0x06 /* Public */,
       5,    0,  312,    2, 0x06 /* Public */,
       6,    0,  313,    2, 0x06 /* Public */,
       7,    0,  314,    2, 0x06 /* Public */,
       8,    0,  315,    2, 0x06 /* Public */,
       9,    0,  316,    2, 0x06 /* Public */,
      10,    0,  317,    2, 0x06 /* Public */,
      11,    0,  318,    2, 0x06 /* Public */,
      12,    0,  319,    2, 0x06 /* Public */,
      13,    0,  320,    2, 0x06 /* Public */,
      14,    0,  321,    2, 0x06 /* Public */,
      15,    0,  322,    2, 0x06 /* Public */,
      16,    0,  323,    2, 0x06 /* Public */,
      17,    0,  324,    2, 0x06 /* Public */,
      18,    0,  325,    2, 0x06 /* Public */,
      19,    0,  326,    2, 0x06 /* Public */,
      20,    0,  327,    2, 0x06 /* Public */,
      21,    0,  328,    2, 0x06 /* Public */,
      22,    0,  329,    2, 0x06 /* Public */,
      23,    0,  330,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      24,    0,  331,    2, 0x02 /* Public */,
      25,    1,  332,    2, 0x02 /* Public */,
      27,    0,  335,    2, 0x02 /* Public */,
      28,    1,  336,    2, 0x02 /* Public */,
      30,    0,  339,    2, 0x02 /* Public */,
      32,    1,  340,    2, 0x02 /* Public */,
      34,    0,  343,    2, 0x02 /* Public */,
      35,    0,  344,    2, 0x02 /* Public */,
      36,    1,  345,    2, 0x02 /* Public */,
      38,    0,  348,    2, 0x02 /* Public */,
      39,    1,  349,    2, 0x02 /* Public */,
      41,    0,  352,    2, 0x02 /* Public */,
      42,    1,  353,    2, 0x02 /* Public */,
      44,    0,  356,    2, 0x02 /* Public */,
      45,    1,  357,    2, 0x02 /* Public */,
      47,    0,  360,    2, 0x02 /* Public */,
      48,    1,  361,    2, 0x02 /* Public */,
      50,    0,  364,    2, 0x02 /* Public */,
      51,    1,  365,    2, 0x02 /* Public */,
      53,    0,  368,    2, 0x02 /* Public */,
      54,    1,  369,    2, 0x02 /* Public */,
      56,    0,  372,    2, 0x02 /* Public */,
      57,    1,  373,    2, 0x02 /* Public */,
      59,    0,  376,    2, 0x02 /* Public */,
      60,    1,  377,    2, 0x02 /* Public */,
      62,    0,  380,    2, 0x02 /* Public */,
      63,    1,  381,    2, 0x02 /* Public */,
      65,    0,  384,    2, 0x02 /* Public */,
      66,    1,  385,    2, 0x02 /* Public */,
      68,    0,  388,    2, 0x02 /* Public */,
      69,    1,  389,    2, 0x02 /* Public */,
      71,    0,  392,    2, 0x02 /* Public */,
      72,    1,  393,    2, 0x02 /* Public */,
      74,    0,  396,    2, 0x02 /* Public */,
      75,    1,  397,    2, 0x02 /* Public */,
      77,    0,  400,    2, 0x02 /* Public */,
      78,    1,  401,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   29,
    0x80000000 | 31,
    QMetaType::Void, 0x80000000 | 31,   33,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   46,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   52,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   64,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   73,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   76,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   79,

 // properties: name, type, flags
      34, QMetaType::Int, 0x00495001,
      24, QMetaType::QString, 0x00495103,
      27, QMetaType::QString, 0x00495103,
      35, QMetaType::Int, 0x00495103,
      38, QMetaType::Int, 0x00495103,
      44, QMetaType::Int, 0x00495103,
      41, QMetaType::Int, 0x00495103,
      30, 0x80000000 | 31, 0x0049510b,
      47, QMetaType::Int, 0x00495103,
      53, QMetaType::Int, 0x00495103,
      56, QMetaType::Int, 0x00495103,
      59, QMetaType::Int, 0x00495103,
      62, QMetaType::Int, 0x00495103,
      65, QMetaType::Int, 0x00495103,
      68, QMetaType::Int, 0x00495103,
      71, QMetaType::Int, 0x00495103,
      74, QMetaType::Int, 0x00495103,
      77, QMetaType::Int, 0x00495103,
      80, QMetaType::QString, 0x00495103,
      81, QMetaType::QString, 0x00495103,
      82, QMetaType::Int, 0x00495103,
      50, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       4,
       0,
       1,
       5,
       6,
       8,
       7,
       2,
       9,
      10,
      11,
      12,
      13,
      14,
      15,
      16,
      17,
      18,
      19,
      20,
      21,
       3,

       0        // eod
};

void DeviceInformation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeviceInformation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->modelChanged(); break;
        case 2: _t->connectTypeChanged(); break;
        case 3: _t->stateChanged(); break;
        case 4: _t->idChanged(); break;
        case 5: _t->maxBacthChanged(); break;
        case 6: _t->sampleChanged(); break;
        case 7: _t->heightOptionChanged(); break;
        case 8: _t->lowerLimitChanged(); break;
        case 9: _t->connectIDChanged(); break;
        case 10: _t->goodRateChanged(); break;
        case 11: _t->goodCyclesChanged(); break;
        case 12: _t->suspectCyclesChanged(); break;
        case 13: _t->notDefiniteChanged(); break;
        case 14: _t->powerChanged(); break;
        case 15: _t->timeChanged(); break;
        case 16: _t->energyChanged(); break;
        case 17: _t->heightPreChanged(); break;
        case 18: _t->heightPostChanged(); break;
        case 19: _t->mesIPChanged(); break;
        case 20: _t->deviceIPChanged(); break;
        case 21: _t->mesPortChanged(); break;
        case 22: { QString _r = _t->name();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: { QString _r = _t->model();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->setModel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: { QmlEnum::CONNECTTYPE _r = _t->connectType();
            if (_a[0]) *reinterpret_cast< QmlEnum::CONNECTTYPE*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->setConnectType((*reinterpret_cast< const QmlEnum::CONNECTTYPE(*)>(_a[1]))); break;
        case 28: { int _r = _t->id();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: { int _r = _t->maxBacth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->setMaxBacth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: { int _r = _t->sample();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->setSample((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: { int _r = _t->heightOption();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->setHeightOption((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: { int _r = _t->lowerLimit();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->setLowerLimit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: { int _r = _t->connectID();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->setConnectID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: { QString _r = _t->state();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->setState((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: { int _r = _t->goodRate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 42: _t->setGoodRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: { int _r = _t->goodCycles();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->setGoodCycles((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: { int _r = _t->suspectCycles();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 46: _t->setSuspectCycles((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: { int _r = _t->notDefinite();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 48: _t->setNotDefinite((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: { int _r = _t->power();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 50: _t->setPower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: { int _r = _t->time();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 52: _t->setTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: { int _r = _t->energy();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 54: _t->setEnergy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: { int _r = _t->heightPre();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 56: _t->setHeightPre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: { int _r = _t->heightPost();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->setHeightPost((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::nameChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::modelChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::connectTypeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::stateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::idChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::maxBacthChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::sampleChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::heightOptionChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::lowerLimitChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::connectIDChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::goodRateChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::goodCyclesChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::suspectCyclesChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::notDefiniteChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::powerChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::timeChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::energyChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::heightPreChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::heightPostChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::mesIPChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::deviceIPChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (DeviceInformation::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DeviceInformation::mesPortChanged)) {
                *result = 21;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<DeviceInformation *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->model(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->maxBacth(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->sample(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->lowerLimit(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->heightOption(); break;
        case 7: *reinterpret_cast< QmlEnum::CONNECTTYPE*>(_v) = _t->connectType(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->connectID(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->goodRate(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->goodCycles(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->suspectCycles(); break;
        case 12: *reinterpret_cast< int*>(_v) = _t->notDefinite(); break;
        case 13: *reinterpret_cast< int*>(_v) = _t->power(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->time(); break;
        case 15: *reinterpret_cast< int*>(_v) = _t->energy(); break;
        case 16: *reinterpret_cast< int*>(_v) = _t->heightPre(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->heightPost(); break;
        case 18: *reinterpret_cast< QString*>(_v) = _t->mesIP(); break;
        case 19: *reinterpret_cast< QString*>(_v) = _t->deviceIP(); break;
        case 20: *reinterpret_cast< int*>(_v) = _t->mesPort(); break;
        case 21: *reinterpret_cast< QString*>(_v) = _t->state(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<DeviceInformation *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setModel(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setMaxBacth(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setSample(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setLowerLimit(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setHeightOption(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setConnectType(*reinterpret_cast< QmlEnum::CONNECTTYPE*>(_v)); break;
        case 8: _t->setConnectID(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setGoodRate(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->setGoodCycles(*reinterpret_cast< int*>(_v)); break;
        case 11: _t->setSuspectCycles(*reinterpret_cast< int*>(_v)); break;
        case 12: _t->setNotDefinite(*reinterpret_cast< int*>(_v)); break;
        case 13: _t->setPower(*reinterpret_cast< int*>(_v)); break;
        case 14: _t->setTime(*reinterpret_cast< int*>(_v)); break;
        case 15: _t->setEnergy(*reinterpret_cast< int*>(_v)); break;
        case 16: _t->setHeightPre(*reinterpret_cast< int*>(_v)); break;
        case 17: _t->setHeightPost(*reinterpret_cast< int*>(_v)); break;
        case 18: _t->setMesIP(*reinterpret_cast< QString*>(_v)); break;
        case 19: _t->setDeviceIP(*reinterpret_cast< QString*>(_v)); break;
        case 20: _t->setMesPort(*reinterpret_cast< int*>(_v)); break;
        case 21: _t->setState(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

static const QMetaObject::SuperData qt_meta_extradata_DeviceInformation[] = {
    QMetaObject::SuperData::link<QmlEnum::staticMetaObject>(),
    nullptr
};

QT_INIT_METAOBJECT const QMetaObject DeviceInformation::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DeviceInformation.data,
    qt_meta_data_DeviceInformation,
    qt_static_metacall,
    qt_meta_extradata_DeviceInformation,
    nullptr
} };


const QMetaObject *DeviceInformation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeviceInformation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeviceInformation.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DeviceInformation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 59)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 59;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 59)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 59;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 22;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 22;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DeviceInformation::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DeviceInformation::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DeviceInformation::connectTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DeviceInformation::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void DeviceInformation::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void DeviceInformation::maxBacthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void DeviceInformation::sampleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void DeviceInformation::heightOptionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void DeviceInformation::lowerLimitChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void DeviceInformation::connectIDChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void DeviceInformation::goodRateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void DeviceInformation::goodCyclesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void DeviceInformation::suspectCyclesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void DeviceInformation::notDefiniteChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void DeviceInformation::powerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void DeviceInformation::timeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void DeviceInformation::energyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void DeviceInformation::heightPreChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void DeviceInformation::heightPostChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void DeviceInformation::mesIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void DeviceInformation::deviceIPChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void DeviceInformation::mesPortChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
