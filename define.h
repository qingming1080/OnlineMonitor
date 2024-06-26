#ifndef DEFINE_H
#define DEFINE_H

#include <QString>
#include <QByteArray>
#include <QDateTime>

enum _CONFIGURATION_COLUMN
{
    _CONFIGURATION_welder_id       = 0,    // 焊机ID
    _CONFIGURATION_welder_name     = 1,    // 焊机名称
    _CONFIGURATION_welder_type     = 2,    // 焊机型号
    _CONFIGURATION_production_bacth = 3,    // 最大生产批量
    _CONFIGURATION_model_sample     = 4,    // 学习样本数
    _CONFIGURATION_lower_limit      = 5,    // 良率下限
    _CONFIGURATION_height_option    = 6,    // 高度模式
};

struct _Configuration_Data
{
    int welder_id;          // 焊机ID
    QString welder_name;    // 焊机名称
    QString welder_type;    // 焊机型号
    int productionBacth;    // 最大生产批量
    int modelSample;        // 学习样本数
    int lowerLimit;         // 良率下限
    int heightOption;       // 高度模式
};

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
    int id;                   // 网口号
    int type;                 // 类型
    int protocol;             // 协议
    QString localIP;          // 本地IP
    int localPort;            // 本地端口
    QString remoteIP;         // 远程IP
    int serverPort;           // 服务器端口
    QString user;             // 用户
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
    int siganl;     // 信号    0:alarm  1:reset 2:not_definite
};

enum _MODEL_COLUMN
{
    _MODEL_id               = 0,    // Model_id
    _MODEL_welder_id        = 1,    // 焊机id
    _MODEL_energy           = 2,    // 能量
    _MODEL_amplitude        = 3,    // 振幅
    _MODEL_pressure         = 4,    // 压力
    _MODEL_welder_time      = 5,    // 焊机时间
    _MODEL_serial_number    = 6,    // 序号
    _MODEL_power            = 7,    // 功率
    _MODEL_create_time      = 8,    // 创建时间
    _MODEL_tensile_force    = 9,    // 撕拉力
    _MODEL_residual_degree  = 10,   // 残留度
};

struct _Model_Data
{
    int id;                 // Model_id
    int welder_id;          // 焊机id
    int energy;             // 能量
    int amplitude;          // 振幅
    int pressure;           // 压力
    QDateTime welder_time;  // 焊机时间
    int serial_number;      // 序号
    int power;              // 功率
    QDateTime create_time;  // 创建时间
    int tensile_force;      // 撕拉力
    int residual_degree;    // 残留度
};

enum _PRODUCTION_COLUMN
{
    _PRODUCTION_batch_id                = 0,    // 生产id
    _PRODUCTION_welder_id               = 1,    // 焊机id
    _PRODUCTION_power                   = 2,    // 功率
    _PRODUCTION_welder_time             = 3,    // 焊接时间
    _PRODUCTION_energy                  = 4,    // 能量
    _PRODUCTION_pre_height              = 5,    // 焊前高度
    _PRODUCTION_post_height             = 6,    // 焊后高度
    _PRODUCTION_create_time             = 7,    // 创建时间
    _PRODUCTION_good_rate               = 8,    // 良率
    _PRODUCTION_counting_total_cycles   = 9,    // 总计
    _PRODUCTION_good_subtotal_cycles    = 10,   // 合格
    _PRODUCTION_suspect_subtotal_cycles = 11,   // 可疑
    _PRODUCTION_not_definite_cycles     = 12,   // 次品
};

struct _Production_Data
{
    int batch_id;                   // 生产id
    int welder_id;                  // 焊机id
    int power;                      // 功率
    QDateTime welder_time;          // 焊接时间
    int energy;                     // 能量
    int pre_height;                 // 焊前高度
    int post_height;                // 焊后高度
    QDateTime create_time;          // 创建时间
    double good_rate;               // 良率
    int counting_total_cycles;      // 总计
    int good_subtotal_cycles;       // 合格
    int suspect_subtotal_cycles;    // 可疑
    int not_definite_cycles;        // 次品
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
