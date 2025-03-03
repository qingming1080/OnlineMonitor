/****************************************************************************
** Meta object code from reading C++ file 'qmlenum.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../modbusNov12/OnlineMonitor/qmlenum.h"
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
    QByteArrayData data[118];
    char stringdata0[2192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QmlEnum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QmlEnum_t qt_meta_stringdata_QmlEnum = {
    {
QT_MOC_LITERAL(0, 0, 7), // "QmlEnum"
QT_MOC_LITERAL(1, 8, 20), // "CONFIGURATION_COLUMN"
QT_MOC_LITERAL(2, 29, 23), // "CONFIGURATION_welder_id"
QT_MOC_LITERAL(3, 53, 25), // "CONFIGURATION_welder_name"
QT_MOC_LITERAL(4, 79, 25), // "CONFIGURATION_welder_type"
QT_MOC_LITERAL(5, 105, 30), // "CONFIGURATION_production_bacth"
QT_MOC_LITERAL(6, 136, 26), // "CONFIGURATION_model_sample"
QT_MOC_LITERAL(7, 163, 25), // "CONFIGURATION_lower_limit"
QT_MOC_LITERAL(8, 189, 27), // "CONFIGURATION_height_option"
QT_MOC_LITERAL(9, 217, 26), // "CONFIGURATION_connect_type"
QT_MOC_LITERAL(10, 244, 24), // "CONFIGURATION_connect_id"
QT_MOC_LITERAL(11, 269, 25), // "CONFIGURATION_delete_type"
QT_MOC_LITERAL(12, 295, 22), // "CONFIGURATION_mes_port"
QT_MOC_LITERAL(13, 318, 20), // "CONFIGURATION_mes_ip"
QT_MOC_LITERAL(14, 339, 23), // "CONFIGURATION_device_ip"
QT_MOC_LITERAL(15, 363, 14), // "NETWORK_COLUMN"
QT_MOC_LITERAL(16, 378, 10), // "NETWORK_id"
QT_MOC_LITERAL(17, 389, 12), // "NETWORK_type"
QT_MOC_LITERAL(18, 402, 16), // "NETWORK_protocol"
QT_MOC_LITERAL(19, 419, 16), // "NETWORK_local_ip"
QT_MOC_LITERAL(20, 436, 18), // "NETWORK_local_port"
QT_MOC_LITERAL(21, 455, 17), // "NETWORK_remote_ip"
QT_MOC_LITERAL(22, 473, 19), // "NETWORK_server_port"
QT_MOC_LITERAL(23, 493, 12), // "NETWORK_user"
QT_MOC_LITERAL(24, 506, 13), // "MANUAL_COLUMN"
QT_MOC_LITERAL(25, 520, 9), // "MANUAL_id"
QT_MOC_LITERAL(26, 530, 16), // "MANUAL_welder_id"
QT_MOC_LITERAL(27, 547, 18), // "MANUAL_create_time"
QT_MOC_LITERAL(28, 566, 20), // "MANUAL_serial_number"
QT_MOC_LITERAL(29, 587, 18), // "MANUAL_cycle_count"
QT_MOC_LITERAL(30, 606, 13), // "MANUAL_energy"
QT_MOC_LITERAL(31, 620, 16), // "MANUAL_amplitude"
QT_MOC_LITERAL(32, 637, 15), // "MANUAL_pressure"
QT_MOC_LITERAL(33, 653, 11), // "MANUAL_time"
QT_MOC_LITERAL(34, 665, 12), // "MANUAL_power"
QT_MOC_LITERAL(35, 678, 17), // "MANUAL_pre_height"
QT_MOC_LITERAL(36, 696, 18), // "MANUAL_post_height"
QT_MOC_LITERAL(37, 715, 19), // "MANUAL_actual_force"
QT_MOC_LITERAL(38, 735, 20), // "MANUAL_actual_degree"
QT_MOC_LITERAL(39, 756, 17), // "PRODUCTION_COLUMN"
QT_MOC_LITERAL(40, 774, 13), // "PRODUCTION_id"
QT_MOC_LITERAL(41, 788, 20), // "PRODUCTION_welder_id"
QT_MOC_LITERAL(42, 809, 19), // "PRODUCTION_model_id"
QT_MOC_LITERAL(43, 829, 22), // "PRODUCTION_create_time"
QT_MOC_LITERAL(44, 852, 24), // "PRODUCTION_serial_number"
QT_MOC_LITERAL(45, 877, 22), // "PRODUCTION_cycle_count"
QT_MOC_LITERAL(46, 900, 22), // "PRODUCTION_batch_count"
QT_MOC_LITERAL(47, 923, 17), // "PRODUCTION_energy"
QT_MOC_LITERAL(48, 941, 20), // "PRODUCTION_amplitude"
QT_MOC_LITERAL(49, 962, 19), // "PRODUCTION_pressure"
QT_MOC_LITERAL(50, 982, 15), // "PRODUCTION_time"
QT_MOC_LITERAL(51, 998, 16), // "PRODUCTION_power"
QT_MOC_LITERAL(52, 1015, 21), // "PRODUCTION_pre_height"
QT_MOC_LITERAL(53, 1037, 22), // "PRODUCTION_post_height"
QT_MOC_LITERAL(54, 1060, 16), // "PRODUCTION_force"
QT_MOC_LITERAL(55, 1077, 19), // "PRODUCTION_residual"
QT_MOC_LITERAL(56, 1097, 20), // "PRODUCTION_good_rate"
QT_MOC_LITERAL(57, 1118, 31), // "PRODUCTION_good_subtotal_cycles"
QT_MOC_LITERAL(58, 1150, 34), // "PRODUCTION_suspect_subtotal_c..."
QT_MOC_LITERAL(59, 1185, 30), // "PRODUCTION_not_definite_cycles"
QT_MOC_LITERAL(60, 1216, 23), // "PRODUCTION_final_result"
QT_MOC_LITERAL(61, 1240, 13), // "SYSTEM_COLUMN"
QT_MOC_LITERAL(62, 1254, 9), // "SYSTEM_id"
QT_MOC_LITERAL(63, 1264, 16), // "SYSTEM_welder_id"
QT_MOC_LITERAL(64, 1281, 26), // "SYSTEM_single_fact_setting"
QT_MOC_LITERAL(65, 1308, 27), // "SYSTEM_general_fact_setting"
QT_MOC_LITERAL(66, 1336, 25), // "SYSTEM_other_fact_setting"
QT_MOC_LITERAL(67, 1362, 23), // "SYSTEM_auto_model_limit"
QT_MOC_LITERAL(68, 1386, 12), // "MODEL_COLUMN"
QT_MOC_LITERAL(69, 1399, 8), // "MODEL_id"
QT_MOC_LITERAL(70, 1408, 15), // "MODEL_welder_id"
QT_MOC_LITERAL(71, 1424, 17), // "MODEL_create_time"
QT_MOC_LITERAL(72, 1442, 12), // "MODEL_energy"
QT_MOC_LITERAL(73, 1455, 15), // "MODEL_amplitude"
QT_MOC_LITERAL(74, 1471, 14), // "MODEL_pressure"
QT_MOC_LITERAL(75, 1486, 16), // "MODEL_time_alpha"
QT_MOC_LITERAL(76, 1503, 15), // "MODEL_time_beta"
QT_MOC_LITERAL(77, 1519, 17), // "MODEL_power_alpha"
QT_MOC_LITERAL(78, 1537, 16), // "MODEL_power_beta"
QT_MOC_LITERAL(79, 1554, 22), // "MODEL_pre_height_alpha"
QT_MOC_LITERAL(80, 1577, 21), // "MODEL_pre_height_beta"
QT_MOC_LITERAL(81, 1599, 23), // "MODEL_post_height_alpha"
QT_MOC_LITERAL(82, 1623, 22), // "MODEL_post_height_beta"
QT_MOC_LITERAL(83, 1646, 17), // "MODEL_force_alpha"
QT_MOC_LITERAL(84, 1664, 16), // "MODEL_force_beta"
QT_MOC_LITERAL(85, 1681, 20), // "MODEL_residual_alpha"
QT_MOC_LITERAL(86, 1702, 19), // "MODEL_residual_beta"
QT_MOC_LITERAL(87, 1722, 26), // "MODEL_current_sample_count"
QT_MOC_LITERAL(88, 1749, 12), // "RS232_COLUMN"
QT_MOC_LITERAL(89, 1762, 8), // "RS232_id"
QT_MOC_LITERAL(90, 1771, 10), // "RS232_port"
QT_MOC_LITERAL(91, 1782, 15), // "RS232_baud_rate"
QT_MOC_LITERAL(92, 1798, 14), // "RS232_data_bit"
QT_MOC_LITERAL(93, 1813, 16), // "RS232_parity_bit"
QT_MOC_LITERAL(94, 1830, 14), // "RS232_stop_bit"
QT_MOC_LITERAL(95, 1845, 9), // "IO_COLUMN"
QT_MOC_LITERAL(96, 1855, 5), // "IO_id"
QT_MOC_LITERAL(97, 1861, 12), // "IO_welder_id"
QT_MOC_LITERAL(98, 1874, 6), // "IO_pin"
QT_MOC_LITERAL(99, 1881, 12), // "IO_available"
QT_MOC_LITERAL(100, 1894, 9), // "IO_signal"
QT_MOC_LITERAL(101, 1904, 11), // "CONNECTTYPE"
QT_MOC_LITERAL(102, 1916, 19), // "CONNECTTYPE_Network"
QT_MOC_LITERAL(103, 1936, 17), // "CONNECTTYPE_RS232"
QT_MOC_LITERAL(104, 1954, 6), // "SIGNAL"
QT_MOC_LITERAL(105, 1961, 12), // "SIGNAL_alarm"
QT_MOC_LITERAL(106, 1974, 12), // "SIGNAL_reset"
QT_MOC_LITERAL(107, 1987, 17), // "SIGNAL_noDefinite"
QT_MOC_LITERAL(108, 2005, 7), // "MESSAGE"
QT_MOC_LITERAL(109, 2013, 18), // "MESSAGE_suspicious"
QT_MOC_LITERAL(110, 2032, 17), // "MESSAGE_defective"
QT_MOC_LITERAL(111, 2050, 17), // "MESSAGE_noConnect"
QT_MOC_LITERAL(112, 2068, 18), // "MESSAGE_lowerValue"
QT_MOC_LITERAL(113, 2087, 22), // "MESSAGE_defectiveOften"
QT_MOC_LITERAL(114, 2110, 23), // "MESSAGE_suspiciousOften"
QT_MOC_LITERAL(115, 2134, 18), // "MESSAGE_upperValue"
QT_MOC_LITERAL(116, 2153, 17), // "MESSAGE_studyOver"
QT_MOC_LITERAL(117, 2171, 20) // "MESSAGE_touchSuccess"

    },
    "QmlEnum\0CONFIGURATION_COLUMN\0"
    "CONFIGURATION_welder_id\0"
    "CONFIGURATION_welder_name\0"
    "CONFIGURATION_welder_type\0"
    "CONFIGURATION_production_bacth\0"
    "CONFIGURATION_model_sample\0"
    "CONFIGURATION_lower_limit\0"
    "CONFIGURATION_height_option\0"
    "CONFIGURATION_connect_type\0"
    "CONFIGURATION_connect_id\0"
    "CONFIGURATION_delete_type\0"
    "CONFIGURATION_mes_port\0CONFIGURATION_mes_ip\0"
    "CONFIGURATION_device_ip\0NETWORK_COLUMN\0"
    "NETWORK_id\0NETWORK_type\0NETWORK_protocol\0"
    "NETWORK_local_ip\0NETWORK_local_port\0"
    "NETWORK_remote_ip\0NETWORK_server_port\0"
    "NETWORK_user\0MANUAL_COLUMN\0MANUAL_id\0"
    "MANUAL_welder_id\0MANUAL_create_time\0"
    "MANUAL_serial_number\0MANUAL_cycle_count\0"
    "MANUAL_energy\0MANUAL_amplitude\0"
    "MANUAL_pressure\0MANUAL_time\0MANUAL_power\0"
    "MANUAL_pre_height\0MANUAL_post_height\0"
    "MANUAL_actual_force\0MANUAL_actual_degree\0"
    "PRODUCTION_COLUMN\0PRODUCTION_id\0"
    "PRODUCTION_welder_id\0PRODUCTION_model_id\0"
    "PRODUCTION_create_time\0PRODUCTION_serial_number\0"
    "PRODUCTION_cycle_count\0PRODUCTION_batch_count\0"
    "PRODUCTION_energy\0PRODUCTION_amplitude\0"
    "PRODUCTION_pressure\0PRODUCTION_time\0"
    "PRODUCTION_power\0PRODUCTION_pre_height\0"
    "PRODUCTION_post_height\0PRODUCTION_force\0"
    "PRODUCTION_residual\0PRODUCTION_good_rate\0"
    "PRODUCTION_good_subtotal_cycles\0"
    "PRODUCTION_suspect_subtotal_cycles\0"
    "PRODUCTION_not_definite_cycles\0"
    "PRODUCTION_final_result\0SYSTEM_COLUMN\0"
    "SYSTEM_id\0SYSTEM_welder_id\0"
    "SYSTEM_single_fact_setting\0"
    "SYSTEM_general_fact_setting\0"
    "SYSTEM_other_fact_setting\0"
    "SYSTEM_auto_model_limit\0MODEL_COLUMN\0"
    "MODEL_id\0MODEL_welder_id\0MODEL_create_time\0"
    "MODEL_energy\0MODEL_amplitude\0"
    "MODEL_pressure\0MODEL_time_alpha\0"
    "MODEL_time_beta\0MODEL_power_alpha\0"
    "MODEL_power_beta\0MODEL_pre_height_alpha\0"
    "MODEL_pre_height_beta\0MODEL_post_height_alpha\0"
    "MODEL_post_height_beta\0MODEL_force_alpha\0"
    "MODEL_force_beta\0MODEL_residual_alpha\0"
    "MODEL_residual_beta\0MODEL_current_sample_count\0"
    "RS232_COLUMN\0RS232_id\0RS232_port\0"
    "RS232_baud_rate\0RS232_data_bit\0"
    "RS232_parity_bit\0RS232_stop_bit\0"
    "IO_COLUMN\0IO_id\0IO_welder_id\0IO_pin\0"
    "IO_available\0IO_signal\0CONNECTTYPE\0"
    "CONNECTTYPE_Network\0CONNECTTYPE_RS232\0"
    "SIGNAL\0SIGNAL_alarm\0SIGNAL_reset\0"
    "SIGNAL_noDefinite\0MESSAGE\0MESSAGE_suspicious\0"
    "MESSAGE_defective\0MESSAGE_noConnect\0"
    "MESSAGE_lowerValue\0MESSAGE_defectiveOften\0"
    "MESSAGE_suspiciousOften\0MESSAGE_upperValue\0"
    "MESSAGE_studyOver\0MESSAGE_touchSuccess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QmlEnum[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
      11,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,   13,   69,
      15,   15, 0x0,    8,   95,
      24,   24, 0x0,   14,  111,
      39,   39, 0x0,   21,  139,
      61,   61, 0x0,    6,  181,
      68,   68, 0x0,   19,  193,
      88,   88, 0x0,    6,  231,
      95,   95, 0x0,    5,  243,
     101,  101, 0x0,    2,  253,
     104,  104, 0x0,    3,  257,
     108,  108, 0x0,    9,  263,

 // enum data: key, value
       2, uint(QmlEnum::CONFIGURATION_welder_id),
       3, uint(QmlEnum::CONFIGURATION_welder_name),
       4, uint(QmlEnum::CONFIGURATION_welder_type),
       5, uint(QmlEnum::CONFIGURATION_production_bacth),
       6, uint(QmlEnum::CONFIGURATION_model_sample),
       7, uint(QmlEnum::CONFIGURATION_lower_limit),
       8, uint(QmlEnum::CONFIGURATION_height_option),
       9, uint(QmlEnum::CONFIGURATION_connect_type),
      10, uint(QmlEnum::CONFIGURATION_connect_id),
      11, uint(QmlEnum::CONFIGURATION_delete_type),
      12, uint(QmlEnum::CONFIGURATION_mes_port),
      13, uint(QmlEnum::CONFIGURATION_mes_ip),
      14, uint(QmlEnum::CONFIGURATION_device_ip),
      16, uint(QmlEnum::NETWORK_id),
      17, uint(QmlEnum::NETWORK_type),
      18, uint(QmlEnum::NETWORK_protocol),
      19, uint(QmlEnum::NETWORK_local_ip),
      20, uint(QmlEnum::NETWORK_local_port),
      21, uint(QmlEnum::NETWORK_remote_ip),
      22, uint(QmlEnum::NETWORK_server_port),
      23, uint(QmlEnum::NETWORK_user),
      25, uint(QmlEnum::MANUAL_id),
      26, uint(QmlEnum::MANUAL_welder_id),
      27, uint(QmlEnum::MANUAL_create_time),
      28, uint(QmlEnum::MANUAL_serial_number),
      29, uint(QmlEnum::MANUAL_cycle_count),
      30, uint(QmlEnum::MANUAL_energy),
      31, uint(QmlEnum::MANUAL_amplitude),
      32, uint(QmlEnum::MANUAL_pressure),
      33, uint(QmlEnum::MANUAL_time),
      34, uint(QmlEnum::MANUAL_power),
      35, uint(QmlEnum::MANUAL_pre_height),
      36, uint(QmlEnum::MANUAL_post_height),
      37, uint(QmlEnum::MANUAL_actual_force),
      38, uint(QmlEnum::MANUAL_actual_degree),
      40, uint(QmlEnum::PRODUCTION_id),
      41, uint(QmlEnum::PRODUCTION_welder_id),
      42, uint(QmlEnum::PRODUCTION_model_id),
      43, uint(QmlEnum::PRODUCTION_create_time),
      44, uint(QmlEnum::PRODUCTION_serial_number),
      45, uint(QmlEnum::PRODUCTION_cycle_count),
      46, uint(QmlEnum::PRODUCTION_batch_count),
      47, uint(QmlEnum::PRODUCTION_energy),
      48, uint(QmlEnum::PRODUCTION_amplitude),
      49, uint(QmlEnum::PRODUCTION_pressure),
      50, uint(QmlEnum::PRODUCTION_time),
      51, uint(QmlEnum::PRODUCTION_power),
      52, uint(QmlEnum::PRODUCTION_pre_height),
      53, uint(QmlEnum::PRODUCTION_post_height),
      54, uint(QmlEnum::PRODUCTION_force),
      55, uint(QmlEnum::PRODUCTION_residual),
      56, uint(QmlEnum::PRODUCTION_good_rate),
      57, uint(QmlEnum::PRODUCTION_good_subtotal_cycles),
      58, uint(QmlEnum::PRODUCTION_suspect_subtotal_cycles),
      59, uint(QmlEnum::PRODUCTION_not_definite_cycles),
      60, uint(QmlEnum::PRODUCTION_final_result),
      62, uint(QmlEnum::SYSTEM_id),
      63, uint(QmlEnum::SYSTEM_welder_id),
      64, uint(QmlEnum::SYSTEM_single_fact_setting),
      65, uint(QmlEnum::SYSTEM_general_fact_setting),
      66, uint(QmlEnum::SYSTEM_other_fact_setting),
      67, uint(QmlEnum::SYSTEM_auto_model_limit),
      69, uint(QmlEnum::MODEL_id),
      70, uint(QmlEnum::MODEL_welder_id),
      71, uint(QmlEnum::MODEL_create_time),
      72, uint(QmlEnum::MODEL_energy),
      73, uint(QmlEnum::MODEL_amplitude),
      74, uint(QmlEnum::MODEL_pressure),
      75, uint(QmlEnum::MODEL_time_alpha),
      76, uint(QmlEnum::MODEL_time_beta),
      77, uint(QmlEnum::MODEL_power_alpha),
      78, uint(QmlEnum::MODEL_power_beta),
      79, uint(QmlEnum::MODEL_pre_height_alpha),
      80, uint(QmlEnum::MODEL_pre_height_beta),
      81, uint(QmlEnum::MODEL_post_height_alpha),
      82, uint(QmlEnum::MODEL_post_height_beta),
      83, uint(QmlEnum::MODEL_force_alpha),
      84, uint(QmlEnum::MODEL_force_beta),
      85, uint(QmlEnum::MODEL_residual_alpha),
      86, uint(QmlEnum::MODEL_residual_beta),
      87, uint(QmlEnum::MODEL_current_sample_count),
      89, uint(QmlEnum::RS232_id),
      90, uint(QmlEnum::RS232_port),
      91, uint(QmlEnum::RS232_baud_rate),
      92, uint(QmlEnum::RS232_data_bit),
      93, uint(QmlEnum::RS232_parity_bit),
      94, uint(QmlEnum::RS232_stop_bit),
      96, uint(QmlEnum::IO_id),
      97, uint(QmlEnum::IO_welder_id),
      98, uint(QmlEnum::IO_pin),
      99, uint(QmlEnum::IO_available),
     100, uint(QmlEnum::IO_signal),
     102, uint(QmlEnum::CONNECTTYPE_Network),
     103, uint(QmlEnum::CONNECTTYPE_RS232),
     105, uint(QmlEnum::SIGNAL_alarm),
     106, uint(QmlEnum::SIGNAL_reset),
     107, uint(QmlEnum::SIGNAL_noDefinite),
     109, uint(QmlEnum::MESSAGE_suspicious),
     110, uint(QmlEnum::MESSAGE_defective),
     111, uint(QmlEnum::MESSAGE_noConnect),
     112, uint(QmlEnum::MESSAGE_lowerValue),
     113, uint(QmlEnum::MESSAGE_defectiveOften),
     114, uint(QmlEnum::MESSAGE_suspiciousOften),
     115, uint(QmlEnum::MESSAGE_upperValue),
     116, uint(QmlEnum::MESSAGE_studyOver),
     117, uint(QmlEnum::MESSAGE_touchSuccess),

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
