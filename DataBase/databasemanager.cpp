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

bool DataBaseManager::getWelderID(QList<int> &IdList)
{
    IdList.clear();

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);

    qDebug() << execStr;
    if (!query.exec(execStr))
    {
        qDebug() << "Configuration查询失败: " << query.lastError();
        return false;
    }

    while(query.next())
    {
        IdList.push_back(query.value(CONFIGURATION_COLUMN::WELDER_ID).toInt());
    }

    return true;
}

bool DataBaseManager::getAllConfigureationDevice(QList<DB_CONFIGURE> &list)
{
    bool bResult = false;
    list.clear();
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);

    if (!query.exec(execStr))
    {
        qDebug() << "Configuration查询失败: " << query.lastError();
        return false;
    }

    while(query.next())
    {
        DB_CONFIGURE configure;
        configure.WelderID               = query.value(CONFIGURATION_COLUMN::WELDER_ID).toInt();
        configure.WelderName             = query.value(CONFIGURATION_COLUMN::WELDER_NAME).toString();
        configure.WelderType             = query.value(CONFIGURATION_COLUMN::WELDER_TYPE).toInt();
        configure.ProductionBatch        = query.value(CONFIGURATION_COLUMN::PRODUCTION_BATCH).toInt();
        configure.MaxModelSamples        = query.value(CONFIGURATION_COLUMN::MAX_MODEL_SAMPLES).toInt();
        configure.YieldRateLowerLimit    = query.value(CONFIGURATION_COLUMN::YIELD_RATE_LOWER_LIMIT).toInt();
        configure.HeightEncoderOption    = query.value(CONFIGURATION_COLUMN::HEIGHT_ENCODER_OPTION).toInt();
        configure.ConnectType            = query.value(CONFIGURATION_COLUMN::CONNECT_TYPE).toInt();
        configure.ConnectTypeId          = query.value(CONFIGURATION_COLUMN::CONNECT_TYPE_ID).toInt();
        configure.SingleFactSetting      = query.value(CONFIGURATION_COLUMN::SINGLE_FACT_SETTING).toInt();
        configure.GeneralFactSetting     = query.value(CONFIGURATION_COLUMN::GENERAL_FACT_SETTING).toInt();
        configure.OtherFactSetting       = query.value(CONFIGURATION_COLUMN::OTHER_FACT_SETTING).toInt();
        configure.AutoLearnCount         = query.value(CONFIGURATION_COLUMN::AUTO_LEARN_COUNT).toInt();
        configure.ForceThreshold         = query.value(CONFIGURATION_COLUMN::FORCE_THRESHOLD).toInt();
        configure.ResidualThreshold      = query.value(CONFIGURATION_COLUMN::RESIDUAL_THRESHOLD).toInt();
        list.push_back(configure);
    }
    if(list.count() > 0)
        bResult = true;

    return bResult;
}

bool DataBaseManager::getConfigurationDevice(const int welderID, DB_CONFIGURE &configure)
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
        configure.SingleFactSetting      = query.value(CONFIGURATION_COLUMN::SINGLE_FACT_SETTING).toInt();
        configure.GeneralFactSetting     = query.value(CONFIGURATION_COLUMN::GENERAL_FACT_SETTING).toInt();
        configure.OtherFactSetting       = query.value(CONFIGURATION_COLUMN::OTHER_FACT_SETTING).toInt();
        configure.AutoLearnCount         = query.value(CONFIGURATION_COLUMN::AUTO_LEARN_COUNT).toInt();
        configure.ForceThreshold         = query.value(CONFIGURATION_COLUMN::FORCE_THRESHOLD).toInt();
        configure.ResidualThreshold      = query.value(CONFIGURATION_COLUMN::RESIDUAL_THRESHOLD).toInt();
        bResult = true;
    }
    return bResult;
}

bool DataBaseManager::removeConfigurationDevice(const int welderID)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(CONFIGURATION_COLUMN::WELDER_ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", welderID);
    bool ret = query.exec();
    return ret;
}

bool DataBaseManager::insertConfigurationDevice(const DB_CONFIGURE configure)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 ("
                              "welder_name, "
                              "welder_type, "
                              "production_bacth, "
                              "model_sample, "
                              "lower_limit, "
                              "height_option, "
                              "suspicious_option, "
                              "connect_type, "
                              "connect_id, "
                              "single_fact_setting, "
                              "general_fact_setting, "
                              "other_fact_setting, "
                              "auto_learn_count, "
                              "force_threshold, "
                              "residual_threshold"
                              ") VALUES ("
                              ":welder_name, "
                              ":welder_type, "
                              ":production_bacth, "
                              ":model_sample, "
                              ":lower_limit, "
                              ":height_option, "
                              ":suspicious_option, "
                              ":connect_type, "
                              ":connect_id, "
                              ":single_fact_setting, "
                              ":general_fact_setting, "
                              ":other_fact_setting, "
                              ":auto_learn_count, "
                              ":force_threshold, "
                              ":residual_threshold"
                              ")").arg(CONFIGURATION_TABLENAME);
     query.prepare(execStr);

    // 绑定属性
     query.bindValue(":welder_name", configure.WelderName);
     query.bindValue(":welder_type", configure.WelderType);
     query.bindValue(":production_bacth", configure.ProductionBatch);
     query.bindValue(":model_sample", configure.MaxModelSamples);
     query.bindValue(":lower_limit", configure.YieldRateLowerLimit);
     query.bindValue(":height_option", configure.HeightEncoderOption ? 1 : 0);
     query.bindValue(":suspicious_option", configure.SuspiciousOption? 1 : 0);
     query.bindValue(":connect_type", configure.ConnectType);
     query.bindValue(":connect_id", configure.ConnectTypeId);
     query.bindValue(":single_fact_setting", configure.SingleFactSetting);
     query.bindValue(":general_fact_setting", configure.GeneralFactSetting);
     query.bindValue(":other_fact_setting", configure.OtherFactSetting);
     query.bindValue(":auto_learn_count", configure.AutoLearnCount);
     query.bindValue(":force_threshold", configure.ForceThreshold);
     query.bindValue(":residual_threshold", configure.ResidualThreshold);
    bool ret = query.exec();
    if (!ret) {
        qWarning() << "Insert configuration failed:" << query.lastError().text();
    }
    return ret;
}

bool DataBaseManager::updateConfigurationDevice(const int welderID, const DB_CONFIGURE configure)
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
                              "suspicious_option = :suspicious_option, "
                              "connect_type = :connect_type, "
                              "connect_id = :connect_id, "
                              "single_fact_setting = :single_fact_setting, "
                              "general_fact_setting = :general_fact_setting, "
                              "other_fact_setting = :other_fact_setting, "
                              "auto_learn_count = :auto_learn_count, "
                              "force_threshold = :force_threshold, "
                              "residual_threshold = :residual_threshold "
                              "WHERE welder_id = :welder_id")
                          .arg(CONFIGURATION_TABLENAME);

    // 绑定参数
    query.bindValue(":welder_name", configure.WelderName);
    query.bindValue(":welder_type", configure.WelderType);
    query.bindValue(":production_bacth", configure.ProductionBatch);
    query.bindValue(":model_sample", configure.MaxModelSamples);
    query.bindValue(":lower_limit", configure.YieldRateLowerLimit);
    query.bindValue(":height_option", configure.HeightEncoderOption ? 1 : 0);
    query.bindValue(":suspicious_option", configure.SuspiciousOption? 1 : 0);
    query.bindValue(":connect_type", configure.ConnectType);
    query.bindValue(":connect_id", configure.ConnectTypeId);
    query.bindValue(":single_fact_setting", configure.SingleFactSetting);
    query.bindValue(":general_fact_setting", configure.GeneralFactSetting);
    query.bindValue(":other_fact_setting", configure.OtherFactSetting);
    query.bindValue(":auto_learn_count", configure.AutoLearnCount);
    query.bindValue(":force_threshold", configure.ForceThreshold);
    query.bindValue(":residual_threshold", configure.ResidualThreshold);
    query.bindValue(":welder_id",welderID);

    bool ret = query.exec();
    if (!ret) {
        qWarning() << "Update configuration failed:" << query.lastError().text();
    }
    return ret;
}


bool DataBaseManager::getAllNetworkConfigure(QList<DataBaseManager::DB_NETWORK>& list)
{
    bool bResult = false;
    list.clear();
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 > 1").arg(NETWORK_TABLENAME, getNetwork_ColumnName(QmlEnum::NETWORK_id));
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        DB_NETWORK data;
        data.Id             = query.value(QmlEnum::NETWORK_id).toInt();
        data.Type           = query.value(QmlEnum::NETWORK_type).toInt();
        data.Protocol       = query.value(QmlEnum::NETWORK_protocol).toInt();
        data.ServerPort    = query.value(QmlEnum::NETWORK_server_port).toInt();
        data.RemoteIP      = query.value(QmlEnum::NETWORK_remote_ip).toString();
        data.LocalIP       = query.value(QmlEnum::NETWORK_local_ip).toString();
        data.User           = query.value(QmlEnum::NETWORK_user).toString();
        list.push_back(data);

    }
    if(list.empty() == false)
        bResult = true;

    return bResult;
}

bool DataBaseManager::updateNetworkConfigure(const int id, const DB_NETWORK network)
{
    QSqlQuery query;

    // 构建更新SQL语句，更新指定welder_id的设备配置
    QString execStr = QString("UPDATE %1 SET "
                              "type = :type, "
                              "protocol = :protocol, "
                              "local_ip = :local_ip, "
                              "local_port = :local_port, "
                              "remote_ip = :remote_ip, "
                              "server_port = :server_port, "
                              "user = :user "
                              "WHERE id = :id")
                          .arg(NETWORK_TABLENAME);

    // 绑定参数
    query.bindValue(":type", network.Type);
    query.bindValue(":protocol", network.Protocol);
    query.bindValue(":local_ip", network.LocalIP);
    query.bindValue(":local_port", network.LocalPort);
    query.bindValue(":remote_ip", network.RemoteIP);
    query.bindValue(":server_port", network.ServerPort);
    query.bindValue(":user", network.User);
    query.bindValue(":id", id);

    bool ret = query.exec();
    if (!ret) {
        qWarning() << "Update network failed:" << query.lastError().text();
    }
    return ret;
}

bool DataBaseManager::getNetworkConfigure(const int id, DB_NETWORK& network)
{
    bool bResult = false;

    // 构造查询字符串，选择 id 匹配的行
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE id = %2")
                          .arg(NETWORK_TABLENAME)
                          .arg(id);

    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
        return bResult;  // 返回空的结果
    }

    if (query.next())
    {
        network.Type        = query.value(QmlEnum::NETWORK_type).toInt();
        network.Protocol    = query.value(QmlEnum::NETWORK_protocol).toInt();
        network.ServerPort  = query.value(QmlEnum::NETWORK_server_port).toInt();
        network.LocalPort   = query.value(QmlEnum::NETWORK_local_port).toInt();
        network.RemoteIP    = query.value(QmlEnum::NETWORK_remote_ip).toString();
        network.LocalIP     = query.value(QmlEnum::NETWORK_local_ip).toString();
        network.User        = query.value(QmlEnum::NETWORK_user).toString();
        bResult = true;
    }
    return bResult;
}


QList<DataBaseManager::DB_RS232> DataBaseManager::getRS232Data()
{
    QList<DB_RS232> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(RS232_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        DB_RS232 data;
        // data.id             = query.value(QmlEnum::RS232_id).toInt();
        data.Port          = query.value(QmlEnum::RS232_port).toInt();
        data.BaudRate      = query.value(QmlEnum::RS232_baud_rate).toInt();
        data.DataBit       = query.value(QmlEnum::RS232_data_bit).toInt();
        data.ParityBit     = query.value(QmlEnum::RS232_parity_bit).toInt();
        data.StopBit       = query.value(QmlEnum::RS232_stop_bit).toInt();
        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::getRS232Configure(const int id, DB_RS232& rs232)
{
    bool bResult = false;

    // 构造查询字符串，选择 id 匹配的行
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE id = %2")
                          .arg(RS232_TABLENAME)
                          .arg(id);

    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
        return bResult;  // 返回空的结果
    }

    if (query.next())
    {
        rs232.Port        = query.value(QmlEnum::RS232_port).toInt();
        rs232.BaudRate    = query.value(QmlEnum::RS232_baud_rate).toInt();
        rs232.DataBit     = query.value(QmlEnum::RS232_data_bit).toInt();
        rs232.ParityBit   = query.value(QmlEnum::RS232_parity_bit).toInt();
        rs232.StopBit     = query.value(QmlEnum::RS232_stop_bit).toInt();
        bResult = true;
    }
    return bResult;
}


bool DataBaseManager::updateRS232Configure(const int id, const DB_RS232 rs232)
{
    QSqlQuery query;
    query.prepare("UPDATE connection_rs232 "
                  "SET port = :port, "
                  "baud_rate = :baudrate, "
                  "data_bit = :databit, "
                  "parity_bit = :paritybit, "
                  "stop_bit = :stopbit "
                  "WHERE id = :id");

    query.bindValue(":port", rs232.Port);
    query.bindValue(":baudrate", rs232.BaudRate);
    query.bindValue(":databit", rs232.DataBit);
    query.bindValue(":paritybit", rs232.ParityBit);
    query.bindValue(":stopbit", rs232.StopBit);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "Failed to update RS232 configuration:" << query.lastError().text();
        return false;
    }
    return true;
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
        data.CreateTime     = query.value(QmlEnum::MANUAL_create_time).toInt();
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
        // data.CreateTime        = query.value(QmlEnum::MODEL_create_time).toString();
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

QList<DataBaseManager::DB_PRODUCTION> DataBaseManager::getProductionData(int welderID, int finalResult, bool exportAll)
{
    QList<DB_PRODUCTION> list;

    QSqlQuery query;
    if(welderID != 0 && finalResult != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID AND %3 = :finalResult ORDER BY create_time DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_WELDER_ID)
                                   , getProduction_ColumnName(FINAL_RESULT));

        if (!exportAll) execStr += " LIMIT 150";
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
        query.bindValue(":finalResult", finalResult-1);
    }
    else if(welderID != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY create_time DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_WELDER_ID));

        if (!exportAll) execStr += " LIMIT 150";
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
    }
    else if(finalResult != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :finalResult ORDER BY create_time DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(FINAL_RESULT));
        if (!exportAll) execStr += " LIMIT 150";
        query.prepare(execStr);
        query.bindValue(":finalResult", finalResult-1);
    }
    else
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 ORDER BY %2 DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_CREATE_TIME));
        if (!exportAll) execStr += " LIMIT 150";
        query.prepare(execStr);
    }

    if (!query.exec())
    {
        qDebug() << "Production查询失败: " << query.lastError();
    }

    while(query.next())
    {
        DB_PRODUCTION data;
        // data.id                       = query.value(QmlEnum::PRODUCTION_id).toInt();
        data.WelderID                = query.value(PRODUCTION_WELDER_ID).toInt();
        data.ModelID                 = query.value(MODEL_ID).toInt();
        data.CreateTime              = query.value(PRODUCTION_CREATE_TIME).toInt();
        data.SerialNumber            = query.value(SERIAL_NUMBER).toInt();
        data.CycleCount              = query.value(CYCLE_COUNT).toInt();
        data.BatchCount              = query.value(BATCH_COUNT).toInt();
        data.Energy                  = query.value(ENERGY).toInt();

        data.Amplitude               = query.value(AMPLITUDE).toInt();
        data.WeldPressure            = query.value(WELD_PRESSURE).toInt();
        data.TriggertPressure        = query.value(TRIGGER_PRESSURE).toInt();
        data.WeldTime                = query.value(WELD_TIME).toInt();
        data.PeakPower               = query.value(PEAK_POWER).toInt();
        data.Preheight               = query.value(PRE_HEIGHT).toInt();
        data.PostHeight              = query.value(POST_HEIGHT).toInt();

        data.Force                   = query.value(FORCE).toInt();
        data.Residual                = query.value(RESIDUAL).toInt();
        data.FinalResult             = query.value(FINAL_RESULT).toInt();

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
                                   , getProduction_ColumnName(PRODUCTION_WELDER_ID)
                                   , getProduction_ColumnName(PRODUCTION_CREATE_TIME));
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
        if(query.exec() && query.next())
        {
            endTime = query.value(PRODUCTION_CREATE_TIME).toDateTime();
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
    QList<DB_PRODUCTION> list = getAllTrendData(welderID, interVal, startTime, endTime);
    int timeInterVal = -interVal / 60;
    QList<int> production_num_list;     // 60个时间段每个时间段的生产总数列表
    QList<int> good_num_list;           // 60个时间段每个时间段的良品总数列表
    for(int i = 0; i < 60; ++i)
    {
        production_num_list.push_back(0);
        good_num_list.push_back(0);
    }

    // 开始计算每个时间段的生产总数与良品总数
    // for(int i = 0; i < list.size(); ++i)
    // {
    //     QDateTime creatTime = list.at(i).CreateTime;
    //     int finalResult = list.at(i).FinalResult;

    //     int timeslot_index = startTime.secsTo(creatTime)/60;
    //     if(timeslot_index >= 0 && timeslot_index < 60)
    //     {
    //         production_num_list[timeslot_index]++;
    //         if(finalResult == 0)
    //         {
    //             good_num_list[timeslot_index]++;
    //         }
    //     }
    // }

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
                          .arg(PRODUCTION_TABLENAME, getProduction_ColumnName(PRODUCTION_ID));

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

bool DataBaseManager::insertProductionRow(DB_PRODUCTION data)
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
    query.bindValue(":welder_id", data.WelderID);
    query.bindValue(":model_id", data.ModelID);
    // query.bindValue(":create_time", data.CreateTime);
    query.bindValue(":serial_number",data.SerialNumber);
    query.bindValue(":cycle_count", data.CycleCount);
    query.bindValue(":batch_count",data.BatchCount);
    query.bindValue(":energy", data.Energy);
    query.bindValue(":amplitude", data.Amplitude);
    query.bindValue(":pressure", data.WeldPressure);
    query.bindValue(":time", data.WeldTime);
    query.bindValue(":power", data.PeakPower);
    query.bindValue(":pre_height", data.Preheight);
    query.bindValue(":post_height", data.PostHeight);
    query.bindValue(":force", data.Force);
    query.bindValue(":residual", data.Residual);
    query.bindValue(":final_result", data.FinalResult);

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

bool DataBaseManager::getSystemData(const int welderID, DataBaseManager::DB_SYSTEM& system)
{
    bool bResult = false;
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(SYSTEM_TABLENAME, getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN::WELD_ID));
    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }
    if(query.next())
    {
        // data.id                   = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_id).toInt();
        // data.welder_id            = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_welder_id).toInt();
        system.SingleFactorSetting      = query.value(QmlEnum::SINGLE_FACTOR_SETTING).toInt();
        system.GeneralFactorSetting     = query.value(QmlEnum::GENERAL_FACTOR_SETTING).toInt();
        system.ForceThreshold           = query.value(QmlEnum::FORCE_THRESHOLD).toInt();
        // data.ResidualThreshold = query.value(QmlEnum::SYSTEM_COLUMN::SYSTEM_other_fact_setting).toInt();
        system.AutoLearningCount        = query.value(QmlEnum::AUTO_LEARNING_COUNT).toInt();
        bResult = true;
    }
    return bResult;
}

bool DataBaseManager::setSystemData(int id, QmlEnum::SYSTEM_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(SYSTEM_TABLENAME, getSystem_ColumnName(column), getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN::WELD_ID));

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
        qDebug() << m_database.lastError();
    }
    else
    {
        qDebug() << "Database Open Success";
        // b_hasFeature = m_database.driver()->hasFeature(QSqlDriver::QuerySize);
        // qDebug() << "数据库是否允许获取行数" << b_hasFeature;
    }
}


QString DataBaseManager::getConfiguration_ColumnName(CONFIGURATION_COLUMN column)
{
    switch(static_cast<int>(column))
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
    case CONFIGURATION_COLUMN::SINGLE_FACT_SETTING:
        return "single_fact_setting";
    case CONFIGURATION_COLUMN::GENERAL_FACT_SETTING:
        return "general_fact_setting";
    case CONFIGURATION_COLUMN::OTHER_FACT_SETTING:
        return "other_fact_setting";
    case CONFIGURATION_COLUMN::AUTO_LEARN_COUNT:
        return "auto_learn_count";
    case CONFIGURATION_COLUMN::FORCE_THRESHOLD:
        return "force_threshold";
    case CONFIGURATION_COLUMN::RESIDUAL_THRESHOLD:
        return "residual_threshold";
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

QString DataBaseManager::getProduction_ColumnName(PRODUCTION_COLUMN column)
{
    switch(column)
    {
    case PRODUCTION_ID:
        return "id";
    case PRODUCTION_WELDER_ID:
        return "welder_id";
    case MODEL_ID:
        return "model_id";
    case PRODUCTION_CREATE_TIME:
        return "create_time";
    case SERIAL_NUMBER:
        return "serial_number";
    case CYCLE_COUNT:
        return "cycle_count";
    case BATCH_COUNT:
        return "batch_count";
    case ENERGY:
        return "energy";
    case AMPLITUDE:
        return "amplitude";
    case WELD_PRESSURE:
        return "pressure";
    case WELD_TIME:
        return "time";
    case PEAK_POWER:
        return "power";
    case PRE_HEIGHT:
        return "pre_height";
    case POST_HEIGHT:
        return "post_height";
    case FORCE:
        return "force";
    case RESIDUAL:
        return "residual";
    case TRIGGER_PRESSURE:
        return "trigger_pressure";
    case FINAL_RESULT:
        return "final_result";
    }

    return "";
}

QString DataBaseManager::getSystem_ColumnName(QmlEnum::SYSTEM_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::SINGLE_FACTOR_SETTING:
        return "single_factor_setting";
    case QmlEnum::GENERAL_FACTOR_SETTING:
        return "general_factor_setting";
    case QmlEnum::FORCE_THRESHOLD:
        return "force_threshold_setting";
    case QmlEnum::RESIDUAL_THRESHOLD:
        return "residual_threshold";
    case QmlEnum::AUTO_LEARNING_COUNT:
        return "auto_learning_count";
    case QmlEnum::WELD_ID:
        return "welder_id";
    }

    return "";
}

QList<DataBaseManager::DB_PRODUCTION> DataBaseManager::getAllTrendData(int welderID, int interVal, QDateTime startTime, QDateTime endTime)
{
    QList<DB_PRODUCTION> list;

    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE %2 BETWEEN '%3' AND '%4' AND %5 = '%6'")
                          .arg(PRODUCTION_TABLENAME
                               , getProduction_ColumnName(PRODUCTION_CREATE_TIME)
                               , startTime.toString("yyyy-MM-dd hh:mm:ss")
                               , endTime.toString("yyyy-MM-dd hh:mm:ss")
                               , getProduction_ColumnName(PRODUCTION_WELDER_ID)
                               , QString::number(welderID));

    if(!query.exec(execStr))
    {
        qDebug() << "Trend获取失败 " << welderID << query.lastError();
    }

    while(query.next())
    {
        DB_PRODUCTION data;
        // 生产时间
        // data.CreateTime  = query.value(QmlEnum::PRODUCTION_create_time).toString();
        // 产品状态
        data.FinalResult = query.value(FINAL_RESULT).toInt();

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
