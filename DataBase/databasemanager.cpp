#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QApplication>
#include <QFile>
#include "model/deviceinformation.h"
#include "tools/utilityfunction.h"

DataBaseManager* DataBaseManager::s_pDataBaseManager = nullptr;

DataBaseManager *DataBaseManager::getInstance()
{
    if(s_pDataBaseManager == nullptr)
        s_pDataBaseManager = new DataBaseManager();

    return s_pDataBaseManager;
}

DataBaseManager::~DataBaseManager()
{

}

void DataBaseManager::openTransaction()
{
    m_database.transaction();
}

void DataBaseManager::closeTransaction()
{
    m_database.commit();
}

QList<int> DataBaseManager::getDeviceCount()
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);

    qDebug() << execStr;
    if (!query.exec(execStr))
    {
        qDebug() << "Configuration查询失败: " << query.lastError();
    }

    QList<int> welderList;
    while(query.next())
    {
        welderList.push_back(query.value(CONFIGURATION_COLUMN::WELDER_ID).toInt());
    }

    return welderList;
}

bool DataBaseManager::getConfigurationData(int welderID, DataBaseManager::DB_CONFIGURE& configure)
{
    bool bResult = false;
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(CONFIGURATION_COLUMN::WELDER_ID));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
        return false;
    }

    if(query.next())
    {
        configure.WelderName             = query.value(CONFIGURATION_COLUMN::WELDER_NAME).toString();
        configure.WelderType             = query.value(CONFIGURATION_COLUMN::WELDER_TYPE).toInt();
        configure.ProductionBatch        = query.value(CONFIGURATION_COLUMN::PRODUCTION_BATCH).toInt();
        configure.MaxModelSamples        = query.value(CONFIGURATION_COLUMN::MAX_MODEL_SAMPLES).toInt();
        configure.YieldRateLowerLimit    = query.value(CONFIGURATION_COLUMN::YIELD_RATE_LOWER_LIMIT).toInt();
        configure.HeightEncoderOption    = query.value(CONFIGURATION_COLUMN::HEIGHT_ENCODER_OPTION).toInt();
        configure.ConnectType            = query.value(CONFIGURATION_COLUMN::CONNECT_TYPE).toInt();
        configure.ConnectTypeId          = query.value(CONFIGURATION_COLUMN::CONNECT_TYPE_ID).toInt();
        configure.MES_Port               = query.value(CONFIGURATION_COLUMN::MES_PORT).toInt();
        configure.MES_IP                 = query.value(CONFIGURATION_COLUMN::MES_IP).toString();
        configure.Device_IP              = query.value(CONFIGURATION_COLUMN::DEVICE_IP).toString();
        bResult = true;
    }
    return bResult;
}

bool DataBaseManager::setConfigurationData(int deviceID, CONFIGURATION_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(column), getConfiguration_ColumnName(CONFIGURATION_COLUMN::WELDER_ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", deviceID);

    return query.exec();
}

bool DataBaseManager::removeConfigurationDevice(int deviceID)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(CONFIGURATION_COLUMN::WELDER_ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", deviceID);
    bool ret = query.exec();
    return ret;
}

bool DataBaseManager::insertConfigurationDevice(DB_CONFIGURE data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":welder_name"
                              ", :welder_type"
                              ", :production_bacth"
                              ", :model_sample"
                              ", :lower_limit"
                              ", :height_option"
                              ", :connect_type"
                              ", :connect_id"
                              ", 0"
                              ", :mes_port"
                              ", :mes_ip"
                              ", :device_ip)")
                          .arg(CONFIGURATION_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":welder_name", data.WelderName);
    query.bindValue(":welder_type", data.WelderType);
    query.bindValue(":production_bacth", data.ProductionBatch);
    query.bindValue(":model_sample", data.MaxModelSamples);
    query.bindValue(":lower_limit", data.YieldRateLowerLimit);
    query.bindValue(":height_option", data.HeightEncoderOption);
    query.bindValue(":connect_type", data.ConnectType);
    query.bindValue(":connect_id", data.ConnectTypeId);
    query.bindValue(":mes_port", data.MES_Port);
    query.bindValue(":mes_ip", data.MES_IP);
    query.bindValue(":device_ip", data.Device_IP);
    bool ret = query.exec();
    return ret;
}

bool DataBaseManager::updateConfigurationDevice(const int WelderID, DB_CONFIGURE& data)
{
    QSqlQuery query;

    // 构建更新SQL语句，更新指定welder_id的设备配置
    QString execStr = QString("UPDATE %1 SET "
                              "welder_name = :welder_name, "
                              "welder_type = :welder_type, "
                              "production_bacth = :production_bacth, "
                              "model_sample = :model_sample, "
                              "lower_limit = :lower_limit, "
                              "height_option = :height_option, "
                              "connect_type = :connect_type, "
                              "connect_id = :connect_id, "
                              "mes_port = :mes_port, "
                              "mes_ip = :mes_ip, "
                              "device_ip = :device_ip "
                              "WHERE welder_id = :welder_id")
                          .arg(CONFIGURATION_TABLENAME);

    // 绑定参数
    query.prepare(execStr);
    query.bindValue(":welder_name", data.WelderName);
    query.bindValue(":welder_type", data.WelderType);
    query.bindValue(":production_bacth", data.ProductionBatch);
    query.bindValue(":model_sample", data.MaxModelSamples);
    query.bindValue(":lower_limit", data.YieldRateLowerLimit);
    query.bindValue(":height_option", data.HeightEncoderOption);
    query.bindValue(":connect_type", data.ConnectType);
    query.bindValue(":connect_id", data.ConnectTypeId);
    query.bindValue(":mes_port", data.MES_Port);
    query.bindValue(":mes_ip", data.MES_IP);
    query.bindValue(":device_ip", data.Device_IP);
    query.bindValue(":welder_id", WelderID); // 确保用 welder_id 来指定更新的记录

    bool ret = query.exec();
    return ret;
}


QList<_Network_Data> DataBaseManager::getNetworkData()
{
    QList<_Network_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(NETWORK_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Network_Data data;
        data.id             = query.value(QmlEnum::NETWORK_id).toInt();
        data.type           = query.value(QmlEnum::NETWORK_type).toInt();
        data.protocol       = query.value(QmlEnum::NETWORK_protocol).toInt();
        data.server_port    = query.value(QmlEnum::NETWORK_server_port).toInt();
        data.remote_ip      = query.value(QmlEnum::NETWORK_remote_ip).toString();
        data.local_ip       = query.value(QmlEnum::NETWORK_local_ip).toString();
        data.user           = query.value(QmlEnum::NETWORK_user).toString();

        list.push_back(data);

    }

    return list;
}

bool DataBaseManager::setNetworkData(int networkID, QmlEnum::NETWORK_COLUMN column, QVariant data)
{
    if(networkID == 1)
        return false;

    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(NETWORK_TABLENAME, getNetwork_ColumnName(column), getNetwork_ColumnName(QmlEnum::NETWORK_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", networkID);

    return query.exec();
}

bool DataBaseManager::removeNetworkRow(int networkID)
{
    if(networkID == 1)
        return false;

    QSqlQuery query;
    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(NETWORK_TABLENAME,getNetwork_ColumnName(QmlEnum::NETWORK_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", networkID);

    return query.exec();
}

bool DataBaseManager::insertNetworkRow(_Network_Data data)
{
    if(data.id == 1)
        return false;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :type"
                              ", :protocol"
                              ", :server_port"
                              ", :remote_ip"
                              ", :local_ip"
                              ", :user)")
                          .arg(NETWORK_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":type", data.type);
    query.bindValue(":protocol", data.protocol);
    query.bindValue(":server_port", data.server_port);
    query.bindValue(":remote_ip", data.remote_ip);
    query.bindValue(":local_ip", data.local_ip);
    query.bindValue(":user", data.user);

    return query.exec();
}

QStringList DataBaseManager::getNetworkInfoById(int id)
{
    QStringList result;  // 用来存储查询结果，包含 remote_ip、server_port 和 local_ip

    // 获取列名
    QString remoteIpColumn = getNetwork_ColumnName(QmlEnum::NETWORK_remote_ip);
    QString serverPortColumn = getNetwork_ColumnName(QmlEnum::NETWORK_server_port);
    QString localIpColumn = getNetwork_ColumnName(QmlEnum::NETWORK_local_ip);

    // 如果列名获取失败（空字符串），则直接返回
    if (remoteIpColumn.isEmpty() || serverPortColumn.isEmpty() || localIpColumn.isEmpty()) {
        return result;
    }

    // 构造查询字符串，选择 id 匹配的行
    QSqlQuery query;
    QString execStr = QString("SELECT %1, %2, %3 FROM %4 WHERE id = %5")
                          .arg(remoteIpColumn)
                          .arg(serverPortColumn)
                          .arg(localIpColumn)
                          .arg(NETWORK_TABLENAME)
                          .arg(id);

    if (!query.exec(execStr)) {
        qDebug() << "查询失败: " << query.lastError();
        return result;  // 返回空的结果
    }

    // 查询结果存在时，取出 remote_ip, server_port 和 local_ip
    if (query.next()) {
        result << query.value(0).toString();  // remote_ip
        result << query.value(1).toString();  // server_port
        result << query.value(2).toString();  // local_ip
    }

    return result;
}


QList<_RS232_Data> DataBaseManager::getRS232Data()
{
    QList<_RS232_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(RS232_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _RS232_Data data;
        data.id             = query.value(QmlEnum::RS232_id).toInt();
        data.port           = query.value(QmlEnum::RS232_port).toString();
        data.baud_rate      = query.value(QmlEnum::RS232_baud_rate).toInt();
        data.data_bit       = query.value(QmlEnum::RS232_data_bit).toInt();
        data.parity_bit     = query.value(QmlEnum::RS232_parity_bit).toString();
        data.stop_bit       = query.value(QmlEnum::RS232_stop_bit).toInt();

        list.push_back(data);
    }

    return list;
}

_RS232_Data DataBaseManager::getRS232DataById(int id)
{
    QList<_RS232_Data> list = getRS232Data();  // 获取所有 RS232 数据

    // 遍历列表查找匹配的 id
    for (const _RS232_Data &data : list) {
        if (data.id == id) {
            return data;  // 返回匹配的 RS232 数据
        }
    }

    // 如果没有找到对应的 id，返回一个空的 _RS232_Data 对象
    return _RS232_Data();
}



bool DataBaseManager::setRS232Data(int id, QmlEnum::RS232_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(RS232_TABLENAME, getRS232_ColumnName(column), getRS232_ColumnName(QmlEnum::RS232_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::removeRS232Row(int id)
{
    QSqlQuery query;
    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(RS232_TABLENAME, getRS232_ColumnName(QmlEnum::RS232_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::insertRS232Row(_RS232_Data data)
{
    if(data.id == 1)
        return false;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :port"
                              ", :baud_rate"
                              ", :data_bit"
                              ", :parity_bit"
                              ", :stop_bit)")
                          .arg(RS232_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":port", data.port);
    query.bindValue(":baud_rate", data.baud_rate);
    query.bindValue(":data_bit", data.data_bit);
    query.bindValue(":parity_bit", data.parity_bit);
    query.bindValue(":stop_bit", data.stop_bit);

    return query.exec();
}

QList<_IO_Data> DataBaseManager::getIOData(int welderID)
{
    QList<_IO_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(IO_TABLENAME, getIO_ColumnName(QmlEnum::IO_welder_id));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _IO_Data data;
        data.id         = query.value(QmlEnum::IO_id).toInt();
        data.welder_id  = query.value(QmlEnum::IO_welder_id).toInt();
        data.pin        = query.value(QmlEnum::IO_pin).toInt();
        data.available  = query.value(QmlEnum::IO_available).toInt();
        data.signal     = query.value(QmlEnum::IO_signal).toInt();

        list.push_back(data);
    }

    return list;
}

_IO_Data DataBaseManager::getIOAvailabel(int welderID)
{
    _IO_Data data;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(IO_TABLENAME, getIO_ColumnName(QmlEnum::IO_welder_id));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        if(query.value(QmlEnum::IO_signal).toInt() != 2)
            continue;

        data.id         = query.value(QmlEnum::IO_id).toInt();
        data.welder_id  = query.value(QmlEnum::IO_welder_id).toInt();
        data.pin        = query.value(QmlEnum::IO_pin).toInt();
        data.available  = query.value(QmlEnum::IO_available).toInt();
        data.signal     = query.value(QmlEnum::IO_signal).toInt();

        return data;
    }

    return data;
}

bool DataBaseManager::setIOData(int id, QmlEnum::IO_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(IO_TABLENAME, getIO_ColumnName(column), getIO_ColumnName(QmlEnum::IO_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::removeIOData(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(IO_TABLENAME, getIO_ColumnName(QmlEnum::IO_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::insertIORow(_IO_Data data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :welder_id"
                              ", :pin"
                              ", :available"
                              ", :signal)")
                          .arg(IO_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":pin", data.pin);
    query.bindValue(":available", data.available);
    query.bindValue(":signal", data.signal);

    return query.exec();
}

bool DataBaseManager::existsManualRowByCycle(int cycleCount)
{
    QSqlQuery query(m_database);
    query.prepare(QString("SELECT COUNT(*) FROM %1 WHERE cycle_count = :cycle_count")
                      .arg(MANUAL_TABLENAME));
    query.bindValue(":cycle_count", cycleCount);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;   // >0 表示存在
    }
    return false;
}

QList<DataBaseManager::DB_MANUAL> DataBaseManager::getManualData(int welderID)
{
    QList<DB_MANUAL> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(MANUAL_TABLENAME, getManual_ColumnName(QmlEnum::MANUAL_welder_id));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        DB_MANUAL data;
        // data.id              = query.value(QmlEnum::MANUAL_id).toInt();
        data.WelderId       = query.value(QmlEnum::MANUAL_welder_id).toInt();
        data.CreateTime     = query.value(QmlEnum::MANUAL_create_time).toString();
        data.serial_number  = query.value(QmlEnum::MANUAL_serial_number).toInt();
        data.CycleCount     = query.value(QmlEnum::MANUAL_cycle_count).toInt();
        data.Energy         = query.value(QmlEnum::MANUAL_energy).toInt();
        data.Amplitude      = query.value(QmlEnum::MANUAL_amplitude).toInt();
        data.WeldPressure   = query.value(QmlEnum::MANUAL_pressure).toInt();
        data.WeldTime       = query.value(QmlEnum::MANUAL_time).toInt();
        data.PeakPower      = query.value(QmlEnum::MANUAL_power).toInt();
        data.Preheight      = query.value(QmlEnum::MANUAL_pre_height).toInt();
        data.PostHeight     = query.value(QmlEnum::MANUAL_post_height).toInt();
        data.ActualForce    = query.value(QmlEnum::MANUAL_actual_force).toInt();
        data.ActualResidual = query.value(QmlEnum::MANUAL_actual_degree).toInt();
        data.IsNewComming   = false;
        list.push_back(data);
    }
    return list;
}

bool DataBaseManager::removeManualDevice(int deviceID)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:welder_id")
                          .arg(MANUAL_TABLENAME, getManual_ColumnName(QmlEnum::MANUAL_welder_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":welder_id", deviceID);

    return query.exec();
}

bool DataBaseManager::insertManualRow(DB_MANUAL data)
{

    if (existsManualRowByCycle(data.CycleCount))
    {
        qDebug() << "Skip duplicate cycle_count:" << data.CycleCount;
        return false;
    }
    QSqlQuery query(m_database);
    QString execStr = QString(
                          "INSERT INTO %1 (welder_id, create_time, serial_number, cycle_count, "
                          "energy, amplitude, pressure, time, power, pre_height, post_height, "
                          "actual_force, actual_degree) "
                          "VALUES (:welder_id, :create_time, :serial_number, :cycle_count, "
                          ":energy, :amplitude, :pressure, :time, :power, :pre_height, :post_height, "
                          ":actual_force, :actual_degree)"
                          ).arg(MANUAL_TABLENAME);

    query.prepare(execStr);

    query.bindValue(":welder_id", data.WelderId);
    query.bindValue(":create_time", data.CreateTime);
    query.bindValue(":serial_number", data.serial_number);
    query.bindValue(":cycle_count", data.CycleCount);
    query.bindValue(":energy", data.Energy);
    query.bindValue(":amplitude", data.Amplitude);
    query.bindValue(":pressure", data.WeldPressure);
    query.bindValue(":time", data.WeldTime);
    query.bindValue(":power", data.PeakPower);
    query.bindValue(":pre_height", data.Preheight);
    query.bindValue(":post_height", data.PostHeight);
    query.bindValue(":actual_force", data.ActualForce);
    query.bindValue(":actual_degree", data.ActualResidual);

    if (!m_database.transaction()) {
        qDebug() << "Failed to start transaction:" << m_database.lastError().text();
        return false;
    }

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        m_database.rollback();
        return false;
    }

    if (!m_database.commit()) {
        qDebug() << "Failed to commit transaction:" << m_database.lastError().text();
        return false;
    }

    qDebug() << "Insert success for serial_number:" << data.serial_number;
    return true;
}


QList<DataBaseManager::DB_MODEL> DataBaseManager::getModelData()
{
    QList<DB_MODEL> list;
    DB_MODEL data;
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(MODEL_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        data.id                 = query.value(QmlEnum::MODEL_id).toInt();
        data.WelderId          = query.value(QmlEnum::MODEL_welder_id).toInt();
        data.CreateTime        = query.value(QmlEnum::MODEL_create_time).toString();
        data.Energy             = query.value(QmlEnum::MODEL_energy).toInt();
        data.Amplitude          = query.value(QmlEnum::MODEL_amplitude).toInt();
        // data.pressure        = query.value(QmlEnum::MODEL_pressure).toInt();
        data.TriggerPressure                 = query.value(QmlEnum::MODEL_tp).toInt();
        data.WeldPressure                 = query.value(QmlEnum::MODEL_wp).toInt();
        data.WeldTime.Alpha      = query.value(QmlEnum::MODEL_time_alpha).toInt();
        data.WeldTime.Beta             = query.value(QmlEnum::MODEL_time_beta).toInt();
        data.PeakPower.Alpha           = query.value(QmlEnum::MODEL_power_alpha).toInt();
        data.PeakPower.Beta            = query.value(QmlEnum::MODEL_power_beta).toInt();
        data.Preheight.Alpha      = query.value(QmlEnum::MODEL_pre_height_alpha).toInt();
        data.Preheight.Beta       = query.value(QmlEnum::MODEL_pre_height_beta).toInt();
        data.PostHeight.Alpha     = query.value(QmlEnum::MODEL_post_height_alpha).toInt();
        data.PostHeight.Beta      = query.value(QmlEnum::MODEL_post_height_beta).toInt();
        // data.force_alpha           = query.value(QmlEnum::MODEL_force_alpha).toInt();
        // data.force_beta            = query.value(QmlEnum::MODEL_force_beta).toInt();
        // data.residual_alpha        = query.value(QmlEnum::MODEL_residual_alpha).toInt();
        // data.residual_beta         = query.value(QmlEnum::MODEL_residual_beta).toInt();
        data.SampleCount  = query.value(QmlEnum::MODEL_current_sample_count).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::removeModelRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(MODEL_TABLENAME, getModel_ColumnName(QmlEnum::MODEL_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::clearModel()
{
    QSqlQuery query;
    QString execStr = QString("TRUNCATE TABLE %1").arg(MODEL_TABLENAME);

    return query.exec(execStr);
}

bool DataBaseManager::insertModelRow(DB_MODEL model)
{

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :welder_id"
                              ", :create_time"
                              ", :energy"
                              ", :amplitude"
                              // ", :pressure"
                              ", :WP"
                              ", :TP"
                              ", :time_alpha"
                              ", :time_beta"
                              ", :power_alpha"
                              ", :power_beta"
                              ", :pre_height_alpha"
                              ", :pre_height_beta"
                              ", :post_height_alpha"
                              ", :post_height_beta"
                              ", :force_alpha"
                              ", :force_beta"
                              ", :residual_alpha"
                              ", :residual_beta"
                              ", :current_sample_count)")
                          .arg(MODEL_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", model.id);
    query.bindValue(":welder_id", model.WelderId);
    query.bindValue(":create_time", model.CreateTime);
    query.bindValue(":energy", model.Energy);
    query.bindValue(":amplitude", model.Amplitude);
    // query.bindValue(":pressure", data.pressure);
    query.bindValue(":pressure", model.TriggerPressure);
    query.bindValue(":pressure", model.WeldPressure);
    query.bindValue(":time_alpha", model.WeldTime.Alpha);
    query.bindValue(":time_beta", model.WeldTime.Beta);
    query.bindValue(":power_alpha", model.PeakPower.Alpha);
    query.bindValue(":power_beta", model.PeakPower.Beta);
    query.bindValue(":pre_height_alpha", model.Preheight.Alpha);
    query.bindValue(":pre_height_beta", model.Preheight.Beta);
    query.bindValue(":post_height_alpha", model.PostHeight.Alpha);
    query.bindValue(":post_height_beta", model.PostHeight.Beta);
    // query.bindValue(":force_alpha", data.force_alpha);
    // query.bindValue(":force_beta", data.force_beta);
    // query.bindValue(":residual_alpha", data.residual_alpha);
    // query.bindValue(":residual_beta", data.residual_beta);
    query.bindValue(":current_sample_count", model.SampleCount);

    return query.exec();
}

QList<_Production_Data> DataBaseManager::getProductionData(int welderID, int finalResult)
{
    QList<_Production_Data> list;

    QSqlQuery query;
    if(welderID != 0 && finalResult != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID AND %3 = :finalResult ORDER BY create_time DESC LIMIT 150")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id)
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_final_result));

        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
        query.bindValue(":finalResult", finalResult-1);
    }
    else if(welderID != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY create_time DESC LIMIT 150")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id));

        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
    }
    else if(finalResult != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :finalResult ORDER BY create_time DESC LIMIT 150")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_final_result));

        query.prepare(execStr);
        query.bindValue(":finalResult", finalResult-1);
    }
    else
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 ORDER BY %2 DESC LIMIT 150")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time));
        query.prepare(execStr);
    }

    if (!query.exec())
    {
        qDebug() << "Production查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Production_Data data;
        data.id                       = query.value(QmlEnum::PRODUCTION_id).toInt();
        data.welder_id                = query.value(QmlEnum::PRODUCTION_welder_id).toInt();
        data.model_id                 = query.value(QmlEnum::PRODUCTION_model_id).toInt();
        data.create_time              = query.value(QmlEnum::PRODUCTION_create_time).toString();
        data.serial_number            = query.value(QmlEnum::PRODUCTION_serial_number).toInt();
        data.cycle_count              = query.value(QmlEnum::PRODUCTION_cycle_count).toInt();
        data.batch_count              = query.value(QmlEnum::PRODUCTION_batch_count).toInt();
        data.energy                   = query.value(QmlEnum::PRODUCTION_energy).toInt();

        data.amplitude                = query.value(QmlEnum::PRODUCTION_amplitude).toInt();
        data.pressure                 = query.value(QmlEnum::PRODUCTION_pressure).toInt();
        data.time                     = query.value(QmlEnum::PRODUCTION_time).toInt();
        data.power                    = query.value(QmlEnum::PRODUCTION_power).toInt();
        data.pre_height               = query.value(QmlEnum::PRODUCTION_pre_height).toInt();
        data.post_height              = query.value(QmlEnum::PRODUCTION_post_height).toInt();

        data.force                    = query.value(QmlEnum::PRODUCTION_force).toInt();
        data.residual                 = query.value(QmlEnum::PRODUCTION_residual).toInt();
        data.good_rate                = query.value(QmlEnum::PRODUCTION_good_rate).toInt();
        data.good_subtotal_cycles     = query.value(QmlEnum::PRODUCTION_good_subtotal_cycles).toInt();
        data.suspect_subtotal_cycles  = query.value(QmlEnum::PRODUCTION_suspect_subtotal_cycles).toInt();
        data.not_definite_cycles      = query.value(QmlEnum::PRODUCTION_not_definite_cycles).toInt();
        data.final_result             = query.value(QmlEnum::PRODUCTION_final_result).toInt();

        // 历史记录，最新的最先显示
        list.push_front(data);
    }

    return list;
}

_Yield_TrendData DataBaseManager::getYieldTrendData(int interVal, int welderID)
{
    _Yield_TrendData result;

    // 获取最新设备生产记录时间
    QDateTime endTime;
    QDateTime startTime;
    {
        QSqlQuery query;
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY %3 DESC LIMIT 1")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id)
                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time));
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
        if(query.exec() && query.next())
        {
            endTime = query.value(QmlEnum::PRODUCTION_create_time).toDateTime();
            startTime = endTime.addSecs(interVal);
            result.startTime = startTime.toString("yyyy-MM-dd hh:mm:ss");
            result.endTime   = endTime.toString("yyyy-MM-dd hh:mm:ss");
        }
        else
        {
            qDebug() << "DataBaseManager::getYieldTrendData() 获取最新生产时间失败" << query.lastError();
            return result;
        }
    }

#ifdef false
    QDateTime currentTime = startTime;
    int timeInterVal = -interVal / 60;

    // 分段计算每个时间段的良率
    for(int i = 0; i < 60; ++i)
    {
        QDateTime tmpTime = currentTime.addSecs(timeInterVal);
        QSqlQuery query;
        QString execStr = QString("SELECT * FROM %1 WHERE %2 BETWEEN '%3' AND '%4' AND %5 = '%6'")
                                       .arg(PRODUCTION_TABLENAME
                                                              , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time)
                                                              , currentTime.toString("yyyy-MM-dd hh:mm:ss")
                                                              , tmpTime.toString("yyyy-MM-dd hh:mm:ss")
                                                              , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id)
                                                              , QString::number(welderID));
        // 当前分段的结束时间点
        QString time = tmpTime.toString("yyyy-MM-dd hh:mm:ss");
        if (!query.exec(execStr))
        {
            qDebug() << "Production查询失败: " << query.lastError() << query.lastQuery();
        }
        int produtcNum = 0;
        int goodNum = 0;
        while(query.next())
        {
            produtcNum++;
            if(query.value(QmlEnum::PRODUCTION_final_result).toInt() == 0)
                goodNum++;
        }
        QPair<int, QString> pair;
        pair.first = produtcNum==0?0:(double(goodNum)/produtcNum) * 100;
        pair.second = time;
        result.points.push_back(pair);
        currentTime = tmpTime;
    }
#endif
    // 缓存数据
    QList<_Production_Data> list = getAllTrendData(welderID, interVal, startTime, endTime);
    int timeInterVal = -interVal / 60;
    QList<int> production_num_list;     // 60个时间段每个时间段的生产总数列表
    QList<int> good_num_list;           // 60个时间段每个时间段的良品总数列表
    for(int i = 0; i < 60; ++i)
    {
        production_num_list.push_back(0);
        good_num_list.push_back(0);
    }

    // 开始计算每个时间段的生产总数与良品总数
    for(int i = 0; i < list.size(); ++i)
    {
        QDateTime creatTime = QDateTime::fromString(list.at(i).create_time, "yyyy-MM-dd hh:mm:ss");
        int finalResult = list.at(i).final_result;

        int timeslot_index = startTime.secsTo(creatTime)/60;
        if(timeslot_index >= 0 && timeslot_index < 60)
        {
            production_num_list[timeslot_index]++;
            if(finalResult == 0)
            {
                good_num_list[timeslot_index]++;
            }
        }
    }

    // 开始计算每个时间段的良率
    for(int i = 0; i < 60; ++i)
    {
        int production_num = production_num_list.at(i);
        int good_num = good_num_list.at(i);
        QPointF pos;
        if(production_num == 0)
            pos.ry() = 0;
        else
            pos.ry() = int(double(good_num)/production_num * 100);
        pos.rx() = startTime.addSecs(timeInterVal * i).toMSecsSinceEpoch();
        result.points.push_back(pos);
    }

    return result;
}

bool DataBaseManager::removeProductionRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(PRODUCTION_TABLENAME, getProduction_ColumnName(QmlEnum::PRODUCTION_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::clearProduction()
{
    QSqlQuery query;
    QString execStr = QString("TRUNCATE TABLE %1").arg(PRODUCTION_TABLENAME);

    return query.exec(execStr);
}

bool DataBaseManager::insertProductionRow(_Production_Data data)
{
    QSqlQuery query;

    // SQL 语句，不包括自增的 id 字段
    QString execStr = QString("INSERT INTO %1 ("
                              "welder_id, model_id, create_time,cycle_count,"
                              "energy, amplitude, pressure, time, power, pre_height, post_height, force, "
                              "residual, good_rate, good_subtotal_cycles, suspect_subtotal_cycles, "
                              "not_definite_cycles, final_result) VALUES ("
                              ":welder_id, :model_id, :create_time, :cycle_count,"
                              ":energy, :amplitude, :pressure, :time, :power, :pre_height, :post_height, :force, "
                              ":residual, :good_rate, :good_subtotal_cycles, :suspect_subtotal_cycles, "
                              ":not_definite_cycles, :final_result)").arg(PRODUCTION_TABLENAME);

    // 准备查询
    query.prepare(execStr);

    // 绑定参数
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":model_id", data.model_id);
    query.bindValue(":create_time", data.create_time);
    //query.bindValue(":serial_number",data.serial_number);
    query.bindValue(":cycle_count", data.cycle_count);
    //query.bindValue(":batch_count",data.batch_count);
    query.bindValue(":energy", data.energy);
    query.bindValue(":amplitude", data.amplitude);
    query.bindValue(":pressure", data.pressure);
    query.bindValue(":time", data.time);
    query.bindValue(":power", data.power);
    query.bindValue(":pre_height", data.pre_height);
    query.bindValue(":post_height", data.post_height);
    query.bindValue(":force", data.force);
    query.bindValue(":residual", data.residual);
    query.bindValue(":good_rate", data.good_rate);
    query.bindValue(":good_subtotal_cycles", data.good_subtotal_cycles);
    query.bindValue(":suspect_subtotal_cycles", data.suspect_subtotal_cycles);
    query.bindValue(":not_definite_cycles", data.not_definite_cycles);
    query.bindValue(":final_result", data.final_result);

    // 调试输出
    qDebug() << "SQL Query:" << execStr;
    qDebug() << "Bound Values:" << query.boundValues();

    // 执行插入并检查结果
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction(); // 开启事务

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    // 获取最后插入的自增 id
    int lastInsertedId = query.lastInsertId().toInt();

    // 更新 serial_number 和 batch_count
    QSqlQuery updateQuery;
    QString updateStr = QString("UPDATE %1 SET serial_number = :serial_number, batch_count = :batch_count WHERE id = :id")
                            .arg(PRODUCTION_TABLENAME);
    updateQuery.prepare(updateStr);
    updateQuery.bindValue(":serial_number", lastInsertedId);
    updateQuery.bindValue(":batch_count", lastInsertedId);
    updateQuery.bindValue(":id", lastInsertedId);

    if (!updateQuery.exec()) {
        qDebug() << "Update failed:" << updateQuery.lastError().text();
        db.rollback(); // 回滚事务
        return false;
    }

    db.commit(); // 提交事务
    return true;
}

// bool DataBaseManager::saveProductionDataofModbus(Device *device, const QVector<quint16> &inputs, quint32 cycleCount, DateTimeData date)
// {
        // if (!device) return false;

        // int deviceId = device->getDevInfoObject()->id();

        // _Production_Data record;

        // record.welder_id                            = deviceId;
        // record.create_time                          = UtilityFunction::buildDateTimeString(date);
        // record.cycle_count                          = cycleCount;
        // record.serial_number                        = cycleCount;                                   //循环值
        // record.batch_count                          = cycleCount;                                   //生产值
        // QString modelStr = device->getDevInfoObject()->model();
        // if (modelStr == "L20-VG") record.model_id = 1;
        // else if (modelStr == "L20-TS") record.model_id = 2;
        // else record.model_id = 0;

        // record.energy                               = inputs[HBModbusClient::DEV_ENERGY];
        // record.amplitude                            = inputs[HBModbusClient::DEV_AMPLITUDE];
        // record.pressure                             = inputs[HBModbusClient::DEV_WP];         //welde pressure
        // record.power                                = inputs[HBModbusClient::DEV_POWER];
        // record.time                                 = inputs[HBModbusClient::DEV_TIME];
        // record.pre_height                           = inputs[HBModbusClient::DEV_PRE_HEIGHT];
        // record.post_height                          = inputs[HBModbusClient::DEV_POST_HEIGHT];
        // record.force                                = 100;                          //TODO
        // record.residual                             = 100;                          //TODO
        // record.good_rate                            = 88;                           //TODO
        // record.good_subtotal_cycles                 = 88;                           //TODO
        // record.suspect_subtotal_cycles              = 88;                           //TODO
        // record.not_definite_cycles                  = 88;                           //TODO
        // record.final_result                         = 88;                           //TODO

        // return insertProductionRow(record);
//         return true;
// }

QList<_System_Data> DataBaseManager::getSystemData(int welderID)
{
    QList<_System_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(SYSTEM_TABLENAME, getSystem_ColumnName(QmlEnum::SYSTEM_welder_id));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _System_Data data;
        data.id                   = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_id).toInt();
        data.welder_id            = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_welder_id).toInt();
        data.single_fact_setting  = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_single_fact_setting).toInt();
        data.general_fact_setting = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_general_fact_setting).toInt();
        data.other_fact_setting   = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_other_fact_setting).toInt();
        data.auto_model_limit     = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_auto_model_limit).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setSystemData(int id, QmlEnum::SYSTEM_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(SYSTEM_TABLENAME, getSystem_ColumnName(column), getSystem_ColumnName(QmlEnum::SYSTEM_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", id);

    return query.exec();
}

int DataBaseManager::getLevelByPassword(QString password)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("SELECT * FROM %1 WHERE user_password='%2'")
                          .arg(USER_TABLENAME, password);
    qDebug() << "数据库路径:" << execStr;
    if(!query.exec(execStr))
    {
        qDebug() << query.lastError();
        return 0;
    }
    if(query.next())
        return query.value(3).toInt();

    return 0;
}

bool DataBaseManager::setUserPassword(QString password)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newPassword WHERE %3 = %4")
                          .arg(USER_TABLENAME, "user_password", "level", "2");

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newPassword", password);

    return query.exec();
}

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject{parent}
{
    init();
}

void DataBaseManager::init()
{

    QString dbName = "onlinemonitor.db";
    QString dbPath = QCoreApplication::applicationDirPath() + "/" + dbName;

    if (!QFile::exists(dbPath))
    {
        QString resourcePath = QString(":/databaseSource/%1").arg(dbName); // 假设放在 qrc:/database/
        if (!QFile::exists(resourcePath))
        {
            qDebug() << "Resource database not found:" << resourcePath;
            return;
        }

        if (!QFile::copy(resourcePath, dbPath))
        {
            qDebug() << "Failed to copy database from resource to:" << dbPath;
            return;
        }

        QFile::setPermissions(dbPath, QFile::WriteOwner | QFile::ReadOwner);
        qDebug() << "Database copied from resource to:" << dbPath;
    }
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbPath);
    // qDebug() << "I_WANT_TEST" << dbPath;
    if (!m_database.open())
    {
        qDebug() << "Database Open Fail ";
        qDebug() << m_database.lastError();
    }
    else
    {
        qDebug() << "Database Open Success";
        b_hasFeature = m_database.driver()->hasFeature(QSqlDriver::QuerySize);
        qDebug() << "数据库是否允许获取行数" << b_hasFeature;
    }
}


QString DataBaseManager::getConfiguration_ColumnName(CONFIGURATION_COLUMN column)
{
    switch(column)
    {
    case CONFIGURATION_COLUMN::WELDER_ID:
        return "welder_id";
    case CONFIGURATION_COLUMN::WELDER_NAME:
        return "welder_name";
    case CONFIGURATION_COLUMN::WELDER_TYPE:
        return "welder_type";
    case CONFIGURATION_COLUMN::PRODUCTION_BATCH:
        return "production_bacth";
    case CONFIGURATION_COLUMN::MAX_MODEL_SAMPLES:
        return "model_sample";
    case CONFIGURATION_COLUMN::YIELD_RATE_LOWER_LIMIT:
        return "lower_limit";
    case CONFIGURATION_COLUMN::HEIGHT_ENCODER_OPTION:
        return "height_option";
    case CONFIGURATION_COLUMN::CONNECT_TYPE:
        return "connect_type";
    case CONFIGURATION_COLUMN::CONNECT_TYPE_ID:
        return "connect_id";
    case CONFIGURATION_COLUMN::MES_PORT:
        return "mes_port";
    case CONFIGURATION_COLUMN::MES_IP:
        return "mes_ip";
    case CONFIGURATION_COLUMN::DEVICE_IP:
        return "device_ip";
    }

    return "";
}

QString DataBaseManager::getNetwork_ColumnName(QmlEnum::NETWORK_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::NETWORK_id:
        return "id";
    case QmlEnum::NETWORK_type:
        return "type";
    case QmlEnum::NETWORK_protocol:
        return "protocol";
    case QmlEnum::NETWORK_local_ip:
        return "local_ip";
    case QmlEnum::NETWORK_local_port:
        return "local_port";
    case QmlEnum::NETWORK_remote_ip:
        return "remote_ip";
    case QmlEnum::NETWORK_server_port:
        return "server_port";
    case QmlEnum::NETWORK_user:
        return "user";
    }

    return "";
}

QString DataBaseManager::getRS232_ColumnName(QmlEnum::RS232_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::RS232_id:
        return "id";
    case QmlEnum::RS232_port:
        return "port";
    case QmlEnum::RS232_baud_rate:
        return "baud_rate";
    case QmlEnum::RS232_data_bit:
        return "data_bit";
    case QmlEnum::RS232_parity_bit:
        return "parity_bit";
    case QmlEnum::RS232_stop_bit:
        return "stop_bit";
    }

    return "";
}

QString DataBaseManager::getIO_ColumnName(QmlEnum::IO_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::IO_id:
        return "id";
    case QmlEnum::IO_welder_id:
        return "welder_id";
    case QmlEnum::IO_pin:
        return "pin";
    case QmlEnum::IO_available:
        return "available";
    case QmlEnum::IO_signal:
        return "signal";
    }

    return "";
}

QString DataBaseManager::getManual_ColumnName(QmlEnum::MANUAL_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::MANUAL_id:
        return "id";
    case QmlEnum::MANUAL_welder_id:
        return "welder_id";
    case QmlEnum::MANUAL_create_time:
        return "create_time";
    case QmlEnum::MANUAL_serial_number:
        return "serial_number";
    case QmlEnum::MANUAL_cycle_count:
        return "cycle_count";
    case QmlEnum::MANUAL_energy:
        return "energy";
    case QmlEnum::MANUAL_amplitude:
        return "amplitude";
    case QmlEnum::MANUAL_pressure:
        return "pressure";
    case QmlEnum::MANUAL_time:
        return "time";
    case QmlEnum::MANUAL_power:
        return "power";
    case QmlEnum::MANUAL_pre_height:
        return "pre_height";
    case QmlEnum::MANUAL_post_height:
        return "post_height";
    case QmlEnum::MANUAL_actual_force:
        return "actual_force";
    case QmlEnum::MANUAL_actual_degree:
        return "actual_degree";
    }

    return "";
}

QString DataBaseManager::getModel_ColumnName(QmlEnum::MODEL_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::MODEL_id:
        return "id";
    case QmlEnum::MODEL_welder_id:
        return "welder_id";
    case QmlEnum::MODEL_create_time:
        return "create_time";
    case QmlEnum::MODEL_energy:
        return "energy";
    case QmlEnum::MODEL_amplitude:
        return "amplitude";
    // case QmlEnum::MODEL_pressure:
        return "pressure";
    case QmlEnum::MODEL_tp:
        return "tp";
    case QmlEnum::MODEL_wp:
        return "wp";
    case QmlEnum::MODEL_time_alpha:
        return "time_alpha";
    case QmlEnum::MODEL_time_beta:
        return "time_beta";
    case QmlEnum::MODEL_power_alpha:
        return "power_alpha";
    case QmlEnum::MODEL_power_beta:
        return "power_beta";
    case QmlEnum::MODEL_pre_height_alpha:
        return "pre_height_alpha";
    case QmlEnum::MODEL_pre_height_beta:
        return "pre_height_beta";
    case QmlEnum::MODEL_post_height_alpha:
        return "post_height_alpha";
    case QmlEnum::MODEL_post_height_beta:
        return "post_height_beta";
    case QmlEnum::MODEL_force_alpha:
        return "force_alpha";
    case QmlEnum::MODEL_force_beta:
        return "force_beta";
    case QmlEnum::MODEL_residual_alpha:
        return "residual_alpha";
    case QmlEnum::MODEL_residual_beta:
        return "residual_beta";
    case QmlEnum::MODEL_current_sample_count:
        return "current_sample_count";
    }

    return "";
}

QString DataBaseManager::getProduction_ColumnName(QmlEnum::PRODUCTION_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::PRODUCTION_id:
        return "id";
    case QmlEnum::PRODUCTION_welder_id:
        return "welder_id";
    case QmlEnum::PRODUCTION_model_id:
        return "model_id";
    case QmlEnum::PRODUCTION_create_time:
        return "create_time";
    case QmlEnum::PRODUCTION_serial_number:
        return "serial_number";
    case QmlEnum::PRODUCTION_cycle_count:
        return "cycle_count";
    case QmlEnum::PRODUCTION_batch_count:
        return "batch_count";
    case QmlEnum::PRODUCTION_energy:
        return "energy";
    case QmlEnum::PRODUCTION_amplitude:
        return "amplitude";
    case QmlEnum::PRODUCTION_pressure:
        return "pressure";
    case QmlEnum::PRODUCTION_time:
        return "time";
    case QmlEnum::PRODUCTION_power:
        return "power";
    case QmlEnum::PRODUCTION_pre_height:
        return "pre_height";
    case QmlEnum::PRODUCTION_post_height:
        return "post_height";
    case QmlEnum::PRODUCTION_force:
        return "force";
    case QmlEnum::PRODUCTION_residual:
        return "residual";
    case QmlEnum::PRODUCTION_good_rate:
        return "good_rate";
    case QmlEnum::PRODUCTION_good_subtotal_cycles:
        return "good_subtotal_cycles";
    case QmlEnum::PRODUCTION_suspect_subtotal_cycles:
        return "suspect_subtotal_cycles";
    case QmlEnum::PRODUCTION_not_definite_cycles:
        return "not_definite_cycles";
    case QmlEnum::PRODUCTION_final_result:
        return "final_result";
    }

    return "";
}

QString DataBaseManager::getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::SYSTEM_id:
        return "id";
    case QmlEnum::SYSTEM_welder_id:
        return "welder_id";
    case QmlEnum::SYSTEM_single_fact_setting:
        return "single_fact_setting";
    case QmlEnum::SYSTEM_general_fact_setting:
        return "general_fact_setting";
    case QmlEnum::SYSTEM_other_fact_setting:
        return "other_fact_setting";
    case QmlEnum::SYSTEM_auto_model_limit:
        return "auto_model_limit";
    }

    return "";
}

QList<_Production_Data> DataBaseManager::getAllTrendData(int welderID, int interVal, QDateTime startTime, QDateTime endTime)
{
    QList<_Production_Data> list;

    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE %2 BETWEEN '%3' AND '%4' AND %5 = '%6'")
                          .arg(PRODUCTION_TABLENAME
                               , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time)
                               , startTime.toString("yyyy-MM-dd hh:mm:ss")
                               , endTime.toString("yyyy-MM-dd hh:mm:ss")
                               , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id)
                               , QString::number(welderID));

    if(!query.exec(execStr))
    {
        qDebug() << "Trend获取失败 " << welderID << query.lastError();
    }

    while(query.next())
    {
        _Production_Data data;
        // 生产时间
        data.create_time  = query.value(QmlEnum::PRODUCTION_create_time).toString();
        // 产品状态
        data.final_result = query.value(QmlEnum::PRODUCTION_final_result).toInt();

        list.push_back(data);
    }

    return list;
}

// QString DataBaseManager::getDeviceInfo()
// {

//     int DEV_ID;
//     //焊机类型;
//     int DEV_TYPE;// 0 VG, 1, TC, 2 2000X
//     int CONNETID;// 0 Ethernet, 1 Serial, 2 analog
//     int DEV_AVAILABLE; // 0 Close, 1 Open
//     int DEV_IP;
//     int LOCAL_IP;

//      QSqlQuery query;

//      QSqlQuery


// }
