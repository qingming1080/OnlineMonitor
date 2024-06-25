#ifndef DEFINE_H
#define DEFINE_H

#include <QString>
#include <QByteArray>

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

#endif // DEFINE_H
