#ifndef DEFINE_H
#define DEFINE_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QDateTime>

#define CONFIGURATION_TABLENAME     QString("configuration")
#define NETWORK_TABLENAME           QString("connection_network")
#define RS232_TABLENAME             QString("connection_rs232")
#define IO_TABLENAME                QString("io_data")
#define MODEL_TABLENAME             QString("model")
#define PRODUCTION_TABLENAME        QString("production")
#define SYSTEM_TABLENAME            QString("system_conf")
#define USER_TABLENAME              QString("user")

enum _CONFIGURATION_COLUMN
{
    _CONFIGURATION_welder_id        = 0,    // 焊机ID
    _CONFIGURATION_welder_name      = 1,    // 焊机名称
    _CONFIGURATION_welder_type      = 2,    // 焊机型号
    _CONFIGURATION_production_bacth = 3,    // 最大生产批量
    _CONFIGURATION_model_sample     = 4,    // 学习样本数
    _CONFIGURATION_lower_limit      = 5,    // 良率下限
    _CONFIGURATION_height_option    = 6,    // 高度模式
    _CONFIGURATION_connect_type     = 7,    // 连接方式
    _CONFIGURATION_connect_id       = 8,    // 连接方式ID
};

struct _Configuration_Data
{
    int welder_id;           // 焊机ID
    QString welder_name;     // 焊机名称
    QString welder_type;     // 焊机型号
    int production_bacth;    // 最大生产批量
    int model_sample;        // 学习样本数
    int lower_limit;         // 良率下限
    int height_option;       // 高度模式
    int connect_type;        // 连接方式     0_RS232  1_Network
    int connect_id;          // 连接方式ID
};
Q_DECLARE_METATYPE(_Configuration_Data)

enum _NETWORK_COLUMN
{
    _NETWORK_id          = 0,   // 网口号
    _NETWORK_type        = 1,   // 类型
    _NETWORK_protocol    = 2,   // 协议
    _NETWORK_local_ip    = 3,   // 本地IP
    _NETWORK_local_port  = 4,   // 本地端口
    _NETWORK_remote_ip   = 5,   // 远程IP
    _NETWORK_server_port = 6,   // 服务器端口
    _NETWORK_user        = 7,   // 用户
};

struct _Network_Data
{
    int id;                    // 网口号
    int type;                  // 类型  0_Server  1_User
    int protocol;              // 协议  0_TCP/IP  1_OPCUA
    QString local_ip;          // 本地IP
    int local_port;            // 本地端口
    QString remote_ip;         // 远程IP
    int server_port;           // 服务器端口
    QString user;              // 用户
};

enum _RS232_COLUMN
{
    _RS232_id           = 0,    // 串口id
    _RS232_port         = 1,    // 串口号
    _RS232_baud_rate    = 2,    // 波特率
    _RS232_data_bit     = 3,    // 数据位
    _RS232_parity_bit   = 4,    // 奇偶校验位
    _RS232_stop_bit     = 5,    // 停止位
};

struct _RS232_Data
{
    int id;                 // 串口id
    QString port;           // 串口号
    int baud_rate;          // 波特率
    int data_bit;           // 数据位
    QString parity_bit;     // 奇偶校验位
    int stop_bit;           // 停止位
};

enum _IO_COLUMN

{
    _IO_id          = 0,    // io_id
    _IO_welder_id   = 1,    // 焊接id
//    _IO_type        = 2,    // 输入输出
    _IO_pin         = 3,    // pin
    _IO_available   = 4,    // 有效的
    _IO_signal      = 5,    // 信号
};

struct _IO_Data
{
    int id;         // io_id
    int welder_id;  // 焊接id
//    int type;       // 输入输出
    int pin;        // pin
    int available;  // 有效的  0:off  1:on
    int signal;     // 信号    0:alarm  1:reset 2:not_definite
};

enum _MANUAL_COLUMN
{
    _MANUAL_id              = 0,    // Manual_ ID
    _MANUAL_welder_id       = 1,    // 焊机ID
    _MANUAL_create_time     = 2,    // 创建时间
    _MANUAL_serial_number   = 3,    // 序号
    _MANUAL_cycle_count     = 4,    // 循环总计
    _MANUAL_energy          = 5,    // 能量
    _MANUAL_amplitude       = 6,    // 振幅
    _MANUAL_pressure        = 7,    // 压力
    _MANUAL_time            = 8,    // 焊接时间
    _MANUAL_power           = 9,    // 功率
    _MANUAL_pre_height      = 10,   // 焊前高度
    _MANUAL_post_height     = 11,   // 焊后高度
    _MANUAL_actual_force    = 12,   // 撕拉力
    _MANUAL_actual_degree   = 13,   // 残留度
};

struct _Manual_Data
{
    int id;                   // Manual_ ID
    int welder_id;            // 焊机ID
    QString create_time;      // 创建时间
    int serial_number;        // 序号
    int cycle_count;          // 循环总计
    int energy;               // 能量
    int amplitude;            // 振幅
    int pressure;             // 压力
    QString time;             // 焊接时间
    int power;                // 功率
    int pre_height;           // 焊前高度
    int post_height;          // 焊后高度
    int actual_force;         // 撕拉力
    int actual_degree;        // 残留度
};

enum _MODEL_COLUMN
{
    _MODEL_id                   = 0,       // 模型id
    _MODEL_welder_id            = 1,       // 焊机id
    _MODEL_create_time          = 2,       // 创建时间
    _MODEL_energy               = 3,       // 能量
    _MODEL_amplitude            = 4,       // 振幅
    _MODEL_pressure             = 5,       // 压力
    _MODEL_time_alpha           = 6,       // 焊机时间Alpha
    _MODEL_time_beta            = 7,       // 焊机时间Beta
    _MODEL_power_alpha          = 8,       // 功率Alpha
    _MODEL_power_beta           = 9,       // 功率Beta
    _MODEL_pre_height_alpha     = 10,      // 焊前高度Alpha
    _MODEL_pre_height_beta      = 11,      // 焊前高度Beta
    _MODEL_post_height_alpha    = 12,      // 焊后高度Alpha
    _MODEL_post_height_beta     = 13,      // 焊后高度Beta
    _MODEL_force_alpha          = 14,      // 撕拉力Alpha
    _MODEL_force_beta           = 15,      // 撕拉力Beta
    _MODEL_residual_alpha       = 16,      // 残留度Alpha
    _MODEL_residual_beta        = 17,      // 残留度Beta
    _MODEL_current_sample_count = 18,      // 当前样本数
};

struct _Model_Data
{
    int id;                            // 模型id
    int welder_id;                     // 焊机id
    QString create_time;               // 创建时间
    int energy;                        // 能量
    int amplitude;                     // 振幅
    int pressure;                      // 压力
    QString time_alpha;                // 焊机时间Alpha
    QString time_beta;                 // 焊机时间Beta
    int power_alpha;                   // 功率Alpha
    int power_beta;                    // 功率Beta
    int pre_height_alpha;              // 焊前高度Alpha
    int pre_height_beta;               // 焊前高度Beta
    int post_height_alpha;             // 焊后高度Alpha
    int post_height_beta;              // 焊后高度Beta
    int force_alpha;                   // 撕拉力Alpha
    int force_beta;                    // 撕拉力Beta
    int residual_alpha;                // 残留度Alpha
    int residual_beta;                 // 残留度Beta
    int current_sample_count;          // 当前样本数
};

enum _PRODUCTION_COLUMN
{
    _PRODUCTION_id                      = 0,    // 生产ID
    _PRODUCTION_welder_id               = 1,    // 焊机ID
    _PRODUCTION_model_id                = 2,    // 模型ID
    _PRODUCTION_create_time             = 3,    // 创建时间
    _PRODUCTION_serial_number           = 4,    // 序号Barcode
    _PRODUCTION_cycle_count             = 5,    // 循环值
    _PRODUCTION_batch_count             = 6,    // 生产值
    _PRODUCTION_energy                  = 7,    // 能量
    _PRODUCTION_amplitude               = 8,    // 振幅
    _PRODUCTION_pressure                = 9,    // 压力
    _PRODUCTION_time                    = 10,   // 焊接时间
    _PRODUCTION_power                   = 11,   // 功率
    _PRODUCTION_pre_height              = 12,   // 焊前高度
    _PRODUCTION_post_height             = 13,   // 焊后高度
    _PRODUCTION_force                   = 14,   // 撕拉力
    _PRODUCTION_residual                = 15,   // 残留度
    _PRODUCTION_good_rate               = 16,   // 良率
    _PRODUCTION_good_subtotal_cycles    = 17,   // 合格
    _PRODUCTION_suspect_subtotal_cycles = 18,   // 次品
    _PRODUCTION_not_definite_cycles     = 19,   // 可疑
};

struct _Production_Data
{
    int id;                                // 生产ID
    int welder_id;                         // 焊机ID
    int model_id;                          // 模型ID
    QString create_time;                   // 创建时间
    int serial_number;                     // 序号Barcode
    int cycle_count;                       // 循环值
    int batch_count;                       // 生产值
    int energy;                            // 能量
    int amplitude;                         // 振幅
    int pressure;                          // 压力
    int time;                              // 焊接时间
    int power;                             // 功率
    int pre_height;                        // 焊前高度
    int post_height;                       // 焊后高度
    int force;                             // 撕拉力
    int residual;                          // 残留度
    int good_rate;                         // 良率
    int good_subtotal_cycles;              // 合格
    int suspect_subtotal_cycles;           // 次品
    int not_definite_cycles;               // 可疑
};

enum _SYSTEM_COLUMN
{
    _SYSTEM_id                   = 0,   // id
    _SYSTEM_welder_id            = 1,   // 设备id
    _SYSTEM_single_fact_setting  = 2,   // 单因素设置
    _SYSTEM_general_fact_setting = 3,   // 通用系数设置
    _SYSTEM_other_fact_setting   = 4,   // 通用系数设置
    _SYSTEM_auto_model_limit     = 5,   // 自动学习上限
};

struct _System_Data
{
    int id;                     // id
    int welder_id;              // 设备id
    int single_fact_setting;    // 单因素设置
    int general_fact_setting;   // 通用系数设置
    int other_fact_setting;     // 通用系数设置
    int auto_model_limit;       // 自动学习上限
};









#endif // DEFINE_H
