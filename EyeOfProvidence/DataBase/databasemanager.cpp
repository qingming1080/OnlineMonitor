#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <algorithm>

#include "DataBase/databasehelper.h"


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

DataBaseHelper *DataBaseManager::getDataBaseHelper() const
{
    return m_databaseHelper;
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
        qDebug() << "getWelderID: " << query.lastError();
        return false;
    }

    while(query.next())
    {
        IdList.push_back(query.value(CONFIGURATION_COLUMN::WELDER_ID).toInt());
    }

    return true;
}

bool DataBaseManager::getAllConfigurationDevice(QList<DB_CONFIGURE> &list)
{
    bool bResult = false;
    list.clear();
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);

    if (!query.exec(execStr))
    {
        qDebug() << "getAllConfigurationDevice: " << query.lastError();
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
        qDebug() << "getConfigurationDevice: " << query.lastError();
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
        configure.SuspiciousOption       = query.value(CONFIGURATION_COLUMN::SUSPICIOUS_OPTION).toInt();
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

int DataBaseManager::insertConfigurationDevice(const DB_CONFIGURE configure)
{
    int iWelderId = -1;
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
    if (!ret)
    {
        qWarning() << "Insert configuration failed:" << query.lastError().text();
        iWelderId = -1;
    }
    else
        iWelderId = query.lastInsertId().toInt();
    return iWelderId;
}

bool DataBaseManager::updateConfigurationDevice(const int welderID, const DB_CONFIGURE configure)
{
    QSqlQuery query;
    QString execStr = QString(
                          "UPDATE %1 SET "
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
                          "WHERE welder_id = :welder_id"
                          ).arg(CONFIGURATION_TABLENAME);

    if (!query.prepare(execStr)) {
        qWarning() << "Failed to prepare SQL:" << query.lastError().text();
        return false;
    }

    query.bindValue(":welder_name", configure.WelderName);
    query.bindValue(":welder_type", configure.WelderType);
    query.bindValue(":production_bacth", configure.ProductionBatch);
    query.bindValue(":model_sample", configure.MaxModelSamples);
    query.bindValue(":lower_limit", configure.YieldRateLowerLimit);
    query.bindValue(":height_option", configure.HeightEncoderOption ? 1 : 0);
    query.bindValue(":suspicious_option", configure.SuspiciousOption ? 1 : 0);
    query.bindValue(":connect_type", configure.ConnectType);
    query.bindValue(":connect_id", configure.ConnectTypeId);
    query.bindValue(":single_fact_setting", configure.SingleFactSetting);
    query.bindValue(":general_fact_setting", configure.GeneralFactSetting);
    query.bindValue(":other_fact_setting", configure.OtherFactSetting);
    query.bindValue(":auto_learn_count", configure.AutoLearnCount);
    query.bindValue(":force_threshold", configure.ForceThreshold);
    query.bindValue(":residual_threshold", configure.ResidualThreshold);
    query.bindValue(":welder_id", welderID);


    bool ret = query.exec();
    if (!ret) {
        qWarning() << "Update configuration failed:" << query.lastError().text();
        qWarning() << "Executed query:" << query.lastQuery();
        return false;
    }

    int affectedRows = query.numRowsAffected();
    if (affectedRows == 0) {
        qWarning() << "No rows updated! welder_id may not exist:" << welderID;
        return false;
    }

    return true;
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
        qDebug() << "getAllNetworkConfigure: " << query.lastError();
    }

    while(query.next())
    {
        DB_NETWORK data;
        data.Id             = query.value(QmlEnum::NETWORK_id).toInt();
        data.Type           = query.value(QmlEnum::NETWORK_type).toInt();
        data.Protocol       = query.value(QmlEnum::NETWORK_protocol).toInt();
        data.ServerPort     = query.value(QmlEnum::NETWORK_server_port).toInt();
        data.RemoteIP       = query.value(QmlEnum::NETWORK_remote_ip).toString();
        data.LocalIP        = query.value(QmlEnum::NETWORK_local_ip).toString();
        data.User           = query.value(QmlEnum::NETWORK_user).toString();
        list.push_back(data);

    }
    if(list.empty() == false)
        bResult = true;

    return bResult;
}
bool DataBaseManager::updateNetworkConfigure(const int id, const DB_NETWORK network){

    QSqlQuery query;

    QString execStr = QString(
                          "UPDATE %1 SET "
                          "type = :type, "
                          "protocol = :protocol, "
                          "local_ip = :local_ip, "
                          "remote_ip = :remote_ip, "
                          "server_port = :server_port, "
                          "\"user\" = :user "
                          "WHERE id = :id"
                          ).arg(NETWORK_TABLENAME);

    if (!query.prepare(execStr)) {
        qWarning() << "Failed to prepare SQL:" << query.lastError().text();
        return false;
    }


    query.bindValue(":type", network.Type);
    query.bindValue(":protocol", network.Protocol);
    query.bindValue(":local_ip", network.LocalIP);
    query.bindValue(":remote_ip", network.RemoteIP);
    query.bindValue(":server_port", network.ServerPort);
    query.bindValue(":user", network.User);
    query.bindValue(":id", id);

    bool ret = query.exec();
    if (!ret) {
        qWarning() << "Update network failed:" << query.lastError().text();
        qWarning() << "Executed query:" << query.lastQuery();
        return false;
    }
    return true;
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
        qDebug() << "getNetworkConfigure: " << query.lastError();
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

bool DataBaseManager::getAllRS232Configure(QList<DataBaseManager::DB_RS232>& list)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(RS232_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "getAllRS232Configure: " << query.lastError();
    }
    while(query.next())
    {
        DataBaseManager::DB_RS232 data;
        data.Id             = query.value(QmlEnum::RS232_id).toInt();
        data.Port           = query.value(QmlEnum::RS232_port).toString();
        data.BaudRate      = query.value(QmlEnum::RS232_baud_rate).toInt();
        data.DataBit       = query.value(QmlEnum::RS232_data_bit).toInt();
        data.ParityBit     = query.value(QmlEnum::RS232_parity_bit).toInt();
        data.StopBit       = query.value(QmlEnum::RS232_stop_bit).toInt();
        list.push_back(data);
    }
    return !list.empty();
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
        qDebug() << "getRS232Configure: " << query.lastError();
        return bResult;  // 返回空的结果
    }

    if (query.next())
    {
        rs232.Port        = query.value(QmlEnum::RS232_port).toString();
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
        qDebug() << "getIOData: " << query.lastError();
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
        qDebug() << "getIOAvailable: " << query.lastError();
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

bool DataBaseManager::getManualRecords(int welderID, QList<DataBaseManager::DB_MANUAL>& list)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(MANUAL_TABLENAME, getManual_ColumnName(MANUAL_TABLE::WELDER_ID));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "getManualRecords: " << query.lastError();
    }

    while(query.next())
    {
        DB_MANUAL data;
        data.Id             = query.value(MANUAL_TABLE::ID).toInt();
        data.WelderId       = query.value(MANUAL_TABLE::WELDER_ID).toInt();
        qint64 timeStamp    = query.value(MANUAL_TABLE::CREATE_TIME).toLongLong();
        data.CreateTime     = QDateTime::fromSecsSinceEpoch(timeStamp, Qt::UTC);
        data.CycleCount     = query.value(MANUAL_TABLE::CYCLE_COUNT).toInt();
        data.Energy         = query.value(MANUAL_TABLE::ENERGY).toInt();
        data.Amplitude      = query.value(MANUAL_TABLE::AMPLITUDE).toInt();
        data.TriggerPressure= query.value(MANUAL_TABLE::TRIGGER_PRESSURE).toInt();
        data.WeldPressure   = query.value(MANUAL_TABLE::WELD_PRESSURE).toInt();
        data.WeldTime       = query.value(MANUAL_TABLE::WELD_TIME).toInt();
        data.PeakPower      = query.value(MANUAL_TABLE::PEAK_POWER).toInt();
        data.Preheight      = query.value(MANUAL_TABLE::PRE_HEIGHT).toInt();
        data.PostHeight     = query.value(MANUAL_TABLE::POST_HEIGHT).toInt();
        data.ActualForce    = query.value(MANUAL_TABLE::ACTUAL_FORCE).toInt();
        data.ActualResidual = query.value(MANUAL_TABLE::ACTUAL_RESIDUAL).toInt();
        data.IsNewComming   = false;
        data.IsSelected     = true;
        data.IsAddByManual  = false;
        list.push_back(data);
    }
    return !list.empty();
}

bool DataBaseManager::removeManualRecords(const int welderID)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:welder_id")
                          .arg(MANUAL_TABLENAME, getManual_ColumnName(MANUAL_TABLE::WELDER_ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":welder_id", welderID);

    return query.exec();
}

bool DataBaseManager::removeManualRecord(const int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(MANUAL_TABLENAME, getManual_ColumnName(MANUAL_TABLE::ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::insertManualRecord(DB_MANUAL data)
{
    QSqlQuery query(m_database);
    QString execStr = QString(
                          "INSERT INTO %1 (welder_id, create_time, cycle_count, "
                          "energy, amplitude, trigger_pressure, weld_pressure, time, power, pre_height, post_height, "
                          "actual_force, actual_residual) "
                          "VALUES (:welder_id, :create_time, :cycle_count, "
                          ":energy, :amplitude, :trigger_pressure, :weld_pressure, :time, :power, :pre_height, :post_height, "
                          ":actual_force, :actual_residual)"
                          ).arg(MANUAL_TABLENAME);


    query.prepare(execStr);

    query.bindValue(":welder_id", data.WelderId);
    query.bindValue(":create_time", data.CreateTime.toSecsSinceEpoch());
    query.bindValue(":cycle_count", data.CycleCount);
    query.bindValue(":energy", data.Energy);
    query.bindValue(":amplitude", data.Amplitude);
    query.bindValue(":trigger_pressure", data.TriggerPressure);
    query.bindValue(":weld_pressure", data.WeldPressure);
    query.bindValue(":time", data.WeldTime);
    query.bindValue(":power", data.PeakPower);
    query.bindValue(":pre_height", data.Preheight);
    query.bindValue(":post_height", data.PostHeight);
    query.bindValue(":actual_force", data.ActualForce);
    query.bindValue(":actual_residual", data.ActualResidual);

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
    return true;
}

bool DataBaseManager::updateManualRecord(const int id, const DB_MANUAL data)
{
    QSqlQuery query;
    QString execStr = QString(
                          "UPDATE %1 SET "
                          "welder_id = :welder_id, "
                          "create_time = :create_time, "
                          "cycle_count = :cycle_count, "
                          "energy = :energy, "
                          "amplitude = :amplitude, "
                          "trigger_pressure = :trigger_pressure, "
                          "weld_pressure = :weld_pressure, "
                          "time = :time, "
                          "power = :power, "
                          "pre_height = :pre_height, "
                          "post_height = :post_height, "
                          "actual_force = :actual_force, "
                          "actual_residual = :actual_residual "
                          "WHERE id = :id"
                          ).arg(MANUAL_TABLENAME);

    if (!query.prepare(execStr)) {
        qWarning() << "Failed to prepare SQL:" << query.lastError().text();
        return false;
    }

    query.bindValue(":welder_id",           data.WelderId);
    query.bindValue(":create_time",         data.CreateTime.toSecsSinceEpoch());
    query.bindValue(":cycle_count",         data.CycleCount);
    query.bindValue(":energy",              data.Energy);
    query.bindValue(":amplitude",           data.Amplitude);
    query.bindValue(":trigger_pressure",    data.TriggerPressure);
    query.bindValue(":weld_pressure",       data.WeldPressure);
    query.bindValue(":time",                data.WeldTime);
    query.bindValue(":power",               data.PeakPower);
    query.bindValue(":pre_height",          data.Preheight);
    query.bindValue(":post_height",         data.PostHeight);
    query.bindValue(":actual_force",        data.ActualForce);
    query.bindValue(":actual_residual",     data.ActualResidual);
    query.bindValue(":id", id);
    bool ret = query.exec();
    if (!ret)
    {
        qWarning() << "Update Manual failed:" << query.lastError().text();
        qWarning() << "Executed query:" << query.lastQuery();
        return false;
    }
    return true;
}

bool DataBaseManager::getModelRecords(QList<DB_MODEL>& list)
{
    DB_MODEL data;
    QSqlQuery query;
    QString strJson;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(MODEL_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "getModelRecords: " << query.lastError();
    }

    while(query.next())
    {
        data.id                 = query.value(MODEL_TABLE::ID).toInt();
        data.WelderId           = query.value(MODEL_TABLE::WELDER_ID).toInt();
        qint64 timeStamp        = query.value(MANUAL_TABLE::CREATE_TIME).toLongLong();
        data.CreateTime         = QDateTime::fromSecsSinceEpoch(timeStamp, Qt::UTC);
        data.Energy             = query.value(MODEL_TABLE::ENERGY).toInt();
        data.Amplitude          = query.value(MODEL_TABLE::AMPLITUDE).toInt();
        data.TriggerPressure    = query.value(MODEL_TABLE::TRIGGER_PRESSURE).toInt();
        data.WeldPressure       = query.value(MODEL_TABLE::WELD_PRESSURE).toInt();
        strJson                 = query.value(MODEL_TABLE::ALPHA_BETA).toString();
        JsonFormat2AlphaBeta(strJson, data.WeldTime, data.PeakPower, data.Preheight, data.PostHeight);
        strJson                 = query.value(MODEL_TABLE::COEFFICIENT).toString();
        JsonFormat2Coefficient(strJson, data.PeelForce, data.Residual);
        strJson                 = query.value(MODEL_TABLE::CENTRALIZED).toString();
        JsonFormat2Centralized(strJson, data.Centralized);
        data.SampleCount  = query.value(MODEL_TABLE::SAMPLE_COUNT).toInt();
        data.BatchCount   = query.value(MODEL_TABLE::BATCH_COUNT).toInt();
        data.isAvailable  = query.value(MODEL_TABLE::AVAILABLE).toBool();
        list.push_back(data);
    }

    return !list.empty();
}

bool DataBaseManager::getModelRecord(const int welderID, DB_MODEL &model)
{
    QSqlQuery query;
    QString strJson;
    bool bResult = false;
    // %1_表格名称 %2_列名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID")
                          .arg(MODEL_TABLENAME, getModel_ColumnName(MODEL_TABLE::WELDER_ID));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);
    if (!query.exec())
    {
        qDebug() << "getModelRecord: " << query.lastError();
    }

    while(query.next())
    {
        model.id                 = query.value(MODEL_TABLE::ID).toInt();
        model.WelderId           = query.value(MODEL_TABLE::WELDER_ID).toInt();
        qint64 timeStamp        = query.value(MANUAL_TABLE::CREATE_TIME).toLongLong();
        model.CreateTime         = QDateTime::fromSecsSinceEpoch(timeStamp, Qt::UTC);
        model.Energy             = query.value(MODEL_TABLE::ENERGY).toInt();
        model.Amplitude          = query.value(MODEL_TABLE::AMPLITUDE).toInt();
        model.TriggerPressure    = query.value(MODEL_TABLE::TRIGGER_PRESSURE).toInt();
        model.WeldPressure       = query.value(MODEL_TABLE::WELD_PRESSURE).toInt();
        strJson                 = query.value(MODEL_TABLE::ALPHA_BETA).toString();
        JsonFormat2AlphaBeta(strJson, model.WeldTime, model.PeakPower, model.Preheight, model.PostHeight);
        strJson                 = query.value(MODEL_TABLE::COEFFICIENT).toString();
        JsonFormat2Coefficient(strJson, model.PeelForce, model.Residual);
        strJson                 = query.value(MODEL_TABLE::CENTRALIZED).toString();
        JsonFormat2Centralized(strJson, model.Centralized);
        model.SampleCount  = query.value(MODEL_TABLE::SAMPLE_COUNT).toInt();
        model.BatchCount   = query.value(MODEL_TABLE::BATCH_COUNT).toInt();
        model.isAvailable  = query.value(MODEL_TABLE::AVAILABLE).toBool();
        bResult = true;
    }
    return bResult;
}

bool DataBaseManager::removeModelRecord(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(MODEL_TABLENAME, getModel_ColumnName(MODEL_TABLE::ID));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);
    return query.exec();
}

bool DataBaseManager::updateModelRecord(const int id, const DB_MODEL model)
{
    QSqlQuery query;
    QString execStr = QString(
                          "UPDATE %1 SET "
                          "welder_id = :welder_id, "
                          "create_time = :create_time, "
                          "energy = :energy, "
                          "amplitude = :amplitude, "
                          "trigger_pressure = :trigger_pressure, "
                          "weld_pressure = :weld_pressure, "
                          "alpha_beta = :alpha_beta, "
                          "coefficient = :coefficient, "
                          "centralized = :centralized, "
                          "sample_count = :sample_count, "
                          "batch_count = :batch_count, "
                          "available = :available "
                          "WHERE id = :id"
                          ).arg(MODEL_TABLENAME);

    if (!query.prepare(execStr)) {
        qWarning() << "Failed to prepare SQL:" << query.lastError().text();
        return false;
    }

    QString strJson;
    query.bindValue(":welder_id",           model.WelderId);
    query.bindValue(":create_time",         model.CreateTime.toSecsSinceEpoch());
    query.bindValue(":energy",              model.Energy);
    query.bindValue(":amplitude",           model.Amplitude);
    query.bindValue(":trigger_pressure",    model.TriggerPressure);
    query.bindValue(":weld_pressure",       model.WeldPressure);
    AlphaBeta2JsonFormat(model.WeldTime, model.PeakPower, model.Preheight, model.PostHeight, strJson);
    query.bindValue(":alpha_beta",          strJson);
    Coefficient2JsonFormat(model.PeelForce, model.Residual, strJson);
    query.bindValue(":coefficient",         strJson);
    Centralized2JsonFormat(model.Centralized, strJson);
    query.bindValue(":centralized",         strJson);
    query.bindValue(":sample_count",        model.SampleCount);
    query.bindValue(":batch_count",         model.BatchCount);
    query.bindValue(":available",           model.isAvailable);
    query.bindValue(":id", id);
    bool ret = query.exec();
    if (!ret)
    {
        qWarning() << "Update Model failed:" << query.lastError().text();
        qWarning() << "Executed query:" << query.lastQuery();
        return false;
    }
    return true;
}

bool DataBaseManager::insertModelRecord(DB_MODEL model)
{
    QString strJson;
    QSqlQuery query;
    // Insert specifying columns explicitly (exclude autoincrement id)
    QString execStr = QString("INSERT INTO %1 ("
                              "welder_id, create_time, energy, amplitude, trigger_pressure, weld_pressure, "
                              "alpha_beta, coefficient, centralized, sample_count, batch_count, available) "
                              "VALUES ("
                              ":welder_id, :create_time, :energy, :amplitude, :trigger_pressure, :weld_pressure, "
                              ":alpha_beta, :coefficient, :centralized, :sample_count, :batch_count, :available)")
                          .arg(MODEL_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":welder_id", model.WelderId);
    query.bindValue(":create_time", model.CreateTime.toSecsSinceEpoch());
    query.bindValue(":energy", model.Energy);
    query.bindValue(":amplitude", model.Amplitude);
    query.bindValue(":trigger_pressure", model.TriggerPressure);
    query.bindValue(":weld_pressure", model.WeldPressure);
    AlphaBeta2JsonFormat(model.WeldTime, model.PeakPower, model.Preheight, model.PostHeight, strJson);
    query.bindValue(":alpha_beta", strJson);
    Coefficient2JsonFormat(model.PeelForce, model.Residual, strJson);
    query.bindValue(":coefficient", strJson);
    Centralized2JsonFormat(model.Centralized, strJson);
    query.bindValue(":centralized", strJson);
    query.bindValue(":sample_count", model.SampleCount);
    query.bindValue(":batch_count", model.BatchCount);
    query.bindValue(":available", model.isAvailable);

    bool ret = query.exec();
    if (!ret)
    {
        qWarning() << "Insert Model failed:" << query.lastError().text();
        qWarning() << "Executed query:" << query.lastQuery();
        return false;
    }
    return true;
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
                                   , getProduction_ColumnName(PRODUCTION_TABLE::WELDER_ID)
                                   , getProduction_ColumnName(PRODUCTION_TABLE::FINAL_RESULT));

        if (!exportAll) execStr += " LIMIT 500";
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
        query.bindValue(":finalResult", finalResult);
    }
    else if(welderID != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY create_time DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_TABLE::WELDER_ID));

        if (!exportAll) execStr += " LIMIT 500";
        query.prepare(execStr);
        query.bindValue(":welderID", welderID);
    }
    else if(finalResult != 0)
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :finalResult ORDER BY create_time DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_TABLE::FINAL_RESULT));
        if (!exportAll) execStr += " LIMIT 500";
        query.prepare(execStr);
        query.bindValue(":finalResult", finalResult);
    }
    else
    {
        // %1_表格名称
        QString execStr = QString("SELECT * FROM %1 ORDER BY %2 DESC")
                              .arg(PRODUCTION_TABLENAME
                                   , getProduction_ColumnName(PRODUCTION_TABLE::CREATE_TIME));
        if (!exportAll) execStr += " LIMIT 500";
        query.prepare(execStr);
    }

    if (!query.exec())
    {
        qDebug() << "getProductionData: " << query.lastError();
    }

    while(query.next())
    {
        DB_PRODUCTION data;
        // data.id                       = query.value(QmlEnum::PRODUCTION_id).toInt();
        data.WelderID                = query.value(PRODUCTION_TABLE::WELDER_ID).toInt();
        data.CreateTime              = query.value(PRODUCTION_TABLE::CREATE_TIME).toLongLong();
        data.SerialNumber            = query.value(PRODUCTION_TABLE::SERIAL_NUMBER).toInt();
        data.CycleCount              = query.value(PRODUCTION_TABLE::CYCLE_COUNT).toInt();
        data.BatchCount              = query.value(PRODUCTION_TABLE::BATCH_COUNT).toInt();
        data.Energy                  = query.value(PRODUCTION_TABLE::ENERGY).toInt();
        data.Amplitude               = query.value(PRODUCTION_TABLE::AMPLITUDE).toInt();
        data.WeldPressure            = query.value(PRODUCTION_TABLE::WELD_PRESSURE).toInt();
        data.TriggerPressure        = query.value(PRODUCTION_TABLE::TRIGGER_PRESSURE).toInt();
        data.WeldTime                = query.value(PRODUCTION_TABLE::WELD_TIME).toInt();
        data.PeakPower               = query.value(PRODUCTION_TABLE::PEAK_POWER).toInt();
        data.Preheight               = query.value(PRODUCTION_TABLE::PRE_HEIGHT).toInt();
        data.PostHeight              = query.value(PRODUCTION_TABLE::POST_HEIGHT).toInt();

        data.Force                   = query.value(PRODUCTION_TABLE::FORCE).toInt();
        data.Residual                = query.value(PRODUCTION_TABLE::RESIDUAL).toInt();
        data.FinalResult             = query.value(PRODUCTION_TABLE::FINAL_RESULT).toInt();
        // 历史记录，最新的最先显示
        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::getProductionLastRecord(const int welderID, DB_PRODUCTION& production)
{
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY %3 DESC LIMIT 1")
                          .arg(PRODUCTION_TABLENAME
                               , getProduction_ColumnName(PRODUCTION_TABLE::WELDER_ID)
                               , getProduction_ColumnName(PRODUCTION_TABLE::CREATE_TIME));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec()) {
        qDebug() << "getProductionLastRecord: query failed:" << query.lastError();
        return false;
    }

    if (!query.next()) {
        // no record
        return false;
    }

    // Fill output struct from the row
    production.ProductionID  = query.value(PRODUCTION_TABLE::ID).toInt();
    production.WelderID      = query.value(PRODUCTION_TABLE::WELDER_ID).toInt();
    production.CreateTime    = query.value(PRODUCTION_TABLE::CREATE_TIME).toLongLong();
    production.SerialNumber  = query.value(PRODUCTION_TABLE::SERIAL_NUMBER).toString();
    production.CycleCount    = query.value(PRODUCTION_TABLE::CYCLE_COUNT).toInt();
    production.BatchCount    = query.value(PRODUCTION_TABLE::BATCH_COUNT).toInt();
    production.Energy        = query.value(PRODUCTION_TABLE::ENERGY).toInt();
    production.Amplitude     = query.value(PRODUCTION_TABLE::AMPLITUDE).toInt();
    production.WeldPressure  = query.value(PRODUCTION_TABLE::WELD_PRESSURE).toInt();
    production.TriggerPressure = query.value(PRODUCTION_TABLE::TRIGGER_PRESSURE).toInt();
    production.WeldTime      = query.value(PRODUCTION_TABLE::WELD_TIME).toInt();
    production.PeakPower     = query.value(PRODUCTION_TABLE::PEAK_POWER).toInt();
    production.Preheight     = query.value(PRODUCTION_TABLE::PRE_HEIGHT).toInt();
    production.PostHeight    = query.value(PRODUCTION_TABLE::POST_HEIGHT).toInt();
    production.Force         = query.value(PRODUCTION_TABLE::FORCE).toInt();
    production.Residual      = query.value(PRODUCTION_TABLE::RESIDUAL).toInt();
    production.FinalResult   = query.value(PRODUCTION_TABLE::FINAL_RESULT).toInt();
    return true;
}

bool DataBaseManager::getProductionRecords(const int welderID, const quint64 startTime, const quint64 endTime, QList<DB_PRODUCTION> &list)
{
    list.clear();
    QSqlQuery query;
    QString execStr = QString("SELECT * FROM %1 WHERE %2 BETWEEN '%3' AND '%4' AND %5 = '%6'")
                          .arg(PRODUCTION_TABLENAME
                               , getProduction_ColumnName(PRODUCTION_TABLE::CREATE_TIME)
                               , QString::number(startTime)
                               , QString::number(endTime)
                               , getProduction_ColumnName(PRODUCTION_TABLE::WELDER_ID)
                               , QString::number(welderID));

    if(!query.exec(execStr))
    {
        qDebug() << "Trend获取失败 " << welderID << query.lastError();
        return false;
    }

    while(query.next())
    {
        DB_PRODUCTION production;
        production.ProductionID  = query.value(PRODUCTION_TABLE::ID).toInt();
        production.WelderID      = query.value(PRODUCTION_TABLE::WELDER_ID).toInt();
        production.CreateTime    = query.value(PRODUCTION_TABLE::CREATE_TIME).toLongLong();
        production.SerialNumber  = query.value(PRODUCTION_TABLE::SERIAL_NUMBER).toString();
        production.CycleCount    = query.value(PRODUCTION_TABLE::CYCLE_COUNT).toInt();
        production.BatchCount    = query.value(PRODUCTION_TABLE::BATCH_COUNT).toInt();
        production.Energy        = query.value(PRODUCTION_TABLE::ENERGY).toInt();
        production.Amplitude     = query.value(PRODUCTION_TABLE::AMPLITUDE).toInt();
        production.WeldPressure  = query.value(PRODUCTION_TABLE::WELD_PRESSURE).toInt();
        production.TriggerPressure = query.value(PRODUCTION_TABLE::TRIGGER_PRESSURE).toInt();
        production.WeldTime      = query.value(PRODUCTION_TABLE::WELD_TIME).toInt();
        production.PeakPower     = query.value(PRODUCTION_TABLE::PEAK_POWER).toInt();
        production.Preheight     = query.value(PRODUCTION_TABLE::PRE_HEIGHT).toInt();
        production.PostHeight    = query.value(PRODUCTION_TABLE::POST_HEIGHT).toInt();
        production.Force         = query.value(PRODUCTION_TABLE::FORCE).toInt();
        production.Residual      = query.value(PRODUCTION_TABLE::RESIDUAL).toInt();
        production.FinalResult   = query.value(PRODUCTION_TABLE::FINAL_RESULT).toInt();
        list.push_back(production);
    }

    return !list.empty();
}

bool DataBaseManager::removeProductionRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(PRODUCTION_TABLENAME, getProduction_ColumnName(PRODUCTION_TABLE::ID));

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
                              "welder_id, create_time, serial_number, cycle_count, batch_count, "
                              "energy, amplitude, trigger_pressure, weld_pressure, time, "
                              "power, pre_height, post_height, force, residual, final_result) "
                              "VALUES ("
                              ":welder_id, :create_time, :serial_number, :cycle_count, :batch_count, "
                              ":energy, :amplitude, :trigger_pressure, :weld_pressure, :time, "
                              ":power, :pre_height, :post_height, :force, :residual, :final_result)").arg(PRODUCTION_TABLENAME);

    // 准备查询
    query.prepare(execStr);

    // 绑定参数
    query.bindValue(":welder_id", data.WelderID);
    query.bindValue(":create_time", data.CreateTime);
    query.bindValue(":serial_number",data.SerialNumber);
    query.bindValue(":cycle_count", data.CycleCount);
    query.bindValue(":batch_count",data.BatchCount);
    query.bindValue(":energy", data.Energy);
    query.bindValue(":amplitude", data.Amplitude);
    query.bindValue(":trigger_pressure", data.TriggerPressure);
    query.bindValue(":weld_pressure", data.WeldPressure);
    query.bindValue(":time", data.WeldTime);
    query.bindValue(":power", data.PeakPower);
    query.bindValue(":pre_height", data.Preheight);
    query.bindValue(":post_height", data.PostHeight);
    query.bindValue(":force", data.Force);
    query.bindValue(":residual", data.Residual);
    query.bindValue(":final_result", data.FinalResult);
    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        // db.rollback(); // 回滚事务
        return false;
    }

    QString TrimStr = QString(
                          "DELETE FROM %1 "
                          "WHERE id IN ("
                          "   SELECT id FROM %1 "
                          "   ORDER BY id ASC "
                          "   LIMIT (SELECT MAX(COUNT(*) - 5000, 0) FROM %1)"
                          ")"
                          ).arg(PRODUCTION_TABLENAME);

    if (!query.exec(TrimStr)) {
        qDebug() << "Trim failed:" << query.lastError().text();
        // db.rollback();
        return false;
    }
    return true;
}

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
        qDebug() << "getSystemData: " << query.lastError();
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
    m_databaseHelper = new DataBaseHelper(this);

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

        // Configure SQLite pragmas for better reliability/performance on SD cards (Raspberry Pi)
        QSqlQuery pragmaQ(m_database);

        // Enable WAL mode (better write performance/concurrency). This returns the journal mode as result.
        if (pragmaQ.exec("PRAGMA journal_mode = WAL;")) {
            if (pragmaQ.next())
                qDebug() << "PRAGMA journal_mode:" << pragmaQ.value(0).toString();
            else
                qDebug() << "PRAGMA journal_mode executed";
        } else {
            qDebug() << "PRAGMA journal_mode failed:" << pragmaQ.lastError().text();
        }

        // Reduce synchronous level from FULL to NORMAL to reduce fsync frequency (tradeoff durability vs speed)
        if (!pragmaQ.exec("PRAGMA synchronous = NORMAL;")) {
            qDebug() << "PRAGMA synchronous failed:" << pragmaQ.lastError().text();
        } else {
            qDebug() << "PRAGMA synchronous set to NORMAL";
        }

        // Busy timeout to wait for locks rather than failing immediately
        if (!pragmaQ.exec("PRAGMA busy_timeout = 5000;")) {
            qDebug() << "PRAGMA busy_timeout failed:" << pragmaQ.lastError().text();
        } else {
            qDebug() << "PRAGMA busy_timeout set to 5000ms";
        }

        // Use memory for temporary store to reduce disk writes
        if (!pragmaQ.exec("PRAGMA temp_store = MEMORY;")) {
            qDebug() << "PRAGMA temp_store failed:" << pragmaQ.lastError().text();
        } else {
            qDebug() << "PRAGMA temp_store set to MEMORY";
        }

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
    case CONFIGURATION_COLUMN::SUSPICIOUS_OPTION:
        return "suspicious_option";
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

QString DataBaseManager::getManual_ColumnName(MANUAL_TABLE::MANUAL_COLUMN column)
{
    switch(column)
    {
    case MANUAL_TABLE::ID:
        return "id";
    case MANUAL_TABLE::WELDER_ID:
        return "welder_id";
    case MANUAL_TABLE::CREATE_TIME:
        return "create_time";
    case MANUAL_TABLE::CYCLE_COUNT:
        return "cycle_count";
    case MANUAL_TABLE::ENERGY:
        return "energy";
    case MANUAL_TABLE::AMPLITUDE:
        return "amplitude";
    case MANUAL_TABLE::TRIGGER_PRESSURE:
        return "trigger_pressure";
    case MANUAL_TABLE::WELD_PRESSURE:
        return "weld_pressure";
    case MANUAL_TABLE::WELD_TIME:
        return "time";
    case MANUAL_TABLE::PEAK_POWER:
        return "power";
    case MANUAL_TABLE::PRE_HEIGHT:
        return "pre_height";
    case MANUAL_TABLE::POST_HEIGHT:
        return "post_height";
    case MANUAL_TABLE::ACTUAL_FORCE:
        return "actual_force";
    case MANUAL_TABLE::ACTUAL_RESIDUAL:
        return "actual_residual";
    case MANUAL_TABLE::IS_SELECTED:
        break;
    default:
        break;
    }
    return "";
}

QString DataBaseManager::getModel_ColumnName(MODEL_TABLE::MODEL_COLUMN column)
{
    switch(column)
    {
    case MODEL_TABLE::ID:
        return "id";
    case MODEL_TABLE::WELDER_ID:
        return "welder_id";
    case MODEL_TABLE::CREATE_TIME:
        return "create_time";
    case MODEL_TABLE::ENERGY:
        return "energy";
    case MODEL_TABLE::AMPLITUDE:
        return "amplitude";
    case MODEL_TABLE::TRIGGER_PRESSURE:
        return "trigger_pressure";
    case MODEL_TABLE::WELD_PRESSURE:
        return "weld_pressure";
    case MODEL_TABLE::ALPHA_BETA:
        return "alpha_beta";
    case MODEL_TABLE::COEFFICIENT:
        return "coefficient";
    case MODEL_TABLE::CENTRALIZED:
        return "centralized";
    case MODEL_TABLE::SAMPLE_COUNT:
        return "sample_count";
    case MODEL_TABLE::BATCH_COUNT:
        return "batch_count";
    case MODEL_TABLE::AVAILABLE:
        return "available";
    }
    return "";
}

QString DataBaseManager::getProduction_ColumnName(PRODUCTION_TABLE::PRODUCTION_COLUMN column)
{
    switch(column)
    {
    case PRODUCTION_TABLE::ID:
        return "id";
    case PRODUCTION_TABLE::WELDER_ID:
        return "welder_id";
    case PRODUCTION_TABLE::CREATE_TIME:
        return "create_time";
    case PRODUCTION_TABLE::SERIAL_NUMBER:
        return "serial_number";
    case PRODUCTION_TABLE::CYCLE_COUNT:
        return "cycle_count";
    case PRODUCTION_TABLE::BATCH_COUNT:
        return "batch_count";
    case PRODUCTION_TABLE::ENERGY:
        return "energy";
    case PRODUCTION_TABLE::AMPLITUDE:
        return "amplitude";
    case PRODUCTION_TABLE::WELD_PRESSURE:
        return "pressure";
    case PRODUCTION_TABLE::WELD_TIME:
        return "time";
    case PRODUCTION_TABLE::PEAK_POWER:
        return "power";
    case PRODUCTION_TABLE::PRE_HEIGHT:
        return "pre_height";
    case PRODUCTION_TABLE::POST_HEIGHT:
        return "post_height";
    case PRODUCTION_TABLE::FORCE:
        return "force";
    case PRODUCTION_TABLE::RESIDUAL:
        return "residual";
    case PRODUCTION_TABLE::TRIGGER_PRESSURE:
        return "trigger_pressure";
    case PRODUCTION_TABLE::FINAL_RESULT:
        return "final_result";
    case PRODUCTION_TABLE::WELDER_NAME:
        return "";
    default:
        return "";
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

bool DataBaseManager::AlphaBeta2JsonFormat(const ALPHA_BETA WeldTime, const ALPHA_BETA PeakPower, const ALPHA_BETA Preheight, const ALPHA_BETA PostHeight, QString &strJson)
{
    // Produce a compact representation: an array of 4 elements, each is [Alpha, Beta]
    // e.g. [[a,b],[a,b],[a,b],[a,b]]
    auto makePair = [](const ALPHA_BETA &ab) {
        QJsonArray p;
        p.append(ab.Alpha);
        p.append(ab.Beta);
        return p;
    };

    QJsonArray arr;
    arr.append(makePair(WeldTime));
    arr.append(makePair(PeakPower));
    arr.append(makePair(Preheight));
    arr.append(makePair(PostHeight));

    QJsonDocument doc(arr);
    strJson = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    return true;
}

bool DataBaseManager::JsonFormat2AlphaBeta(const QString strJson, ALPHA_BETA &WeldTime, ALPHA_BETA &PeakPower, ALPHA_BETA &Preheight, ALPHA_BETA &PostHeight)
{
    if (strJson.isEmpty()) return false;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "JsonFormat2AlphaBeta: parse error:" << err.errorString();
        return false;
    }

    if (!doc.isArray()) {
        qDebug() << "JsonFormat2AlphaBeta: expected JSON array";
        return false;
    }

    QJsonArray arr = doc.array();
    if (arr.size() < 4) {
        qDebug() << "JsonFormat2AlphaBeta: array size < 4";
        return false;
    }
    // Accept either the older object format {"Alpha":..,"Beta":..} or the new compact [alpha,beta]
    auto parseAB = [](const QJsonValue &v, ALPHA_BETA &out) {
        if (v.isObject()) {
            QJsonObject o = v.toObject();
            out.Alpha = o.value("Alpha").toDouble(0.0);
            out.Beta  = o.value("Beta").toDouble(0.0);
            return true;
        }
        if (v.isArray()) {
            QJsonArray a = v.toArray();
            if (a.size() < 2) return false;
            out.Alpha = a.at(0).toDouble(0.0);
            out.Beta  = a.at(1).toDouble(0.0);
            return true;
        }
        return false;
    };

    bool ok = true;
    ok &= parseAB(arr.at(0), WeldTime);
    ok &= parseAB(arr.at(1), PeakPower);
    ok &= parseAB(arr.at(2), Preheight);
    ok &= parseAB(arr.at(3), PostHeight);

    if (!ok) {
        qDebug() << "JsonFormat2AlphaBeta: one or more elements invalid";
        return false;
    }

    return true;
}

bool DataBaseManager::Coefficient2JsonFormat(const POLYNOMIAL_COEFFICIENT PeelForce, const POLYNOMIAL_COEFFICIENT Residual, QString &strJson)
{
    // Compact format: each coefficient is an array in the order
    // [P00, P10, P01, P20, P11, P02]
    auto makeArray = [](const POLYNOMIAL_COEFFICIENT &c) {
        QJsonArray a;
        a.append(c.P00);
        a.append(c.P10);
        a.append(c.P01);
        a.append(c.P20);
        a.append(c.P11);
        a.append(c.P02);
        return a;
    };

    QJsonArray arr;
    arr.append(makeArray(PeelForce)); // index 0
    arr.append(makeArray(Residual));  // index 1

    QJsonDocument doc(arr);
    strJson = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    return true;
}

bool DataBaseManager::JsonFormat2Coefficient(const QString strJson, POLYNOMIAL_COEFFICIENT &PeelForce, POLYNOMIAL_COEFFICIENT &Residual)
{
    if (strJson.isEmpty()) return false;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "JsonFormat2Coefficient: parse error:" << err.errorString();
        return false;
    }

    if (!doc.isArray()) {
        qDebug() << "JsonFormat2Coefficient: expected JSON array";
        return false;
    }

    QJsonArray arr = doc.array();
    if (arr.size() < 2) {
        qDebug() << "JsonFormat2Coefficient: array size < 2";
        return false;
    }
    // Accept either object form {"P00":...,"P10":...} or compact array form [P00,P10,P01,P20,P11,P02]
    auto parseC = [](const QJsonValue &v, POLYNOMIAL_COEFFICIENT &out) {
        if (v.isObject()) {
            QJsonObject o = v.toObject();
            out.P00 = o.value("P00").toDouble(0.0);
            out.P10 = o.value("P10").toDouble(0.0);
            out.P01 = o.value("P01").toDouble(0.0);
            out.P20 = o.value("P20").toDouble(0.0);
            out.P11 = o.value("P11").toDouble(0.0);
            out.P02 = o.value("P02").toDouble(0.0);
            return true;
        }
        if (v.isArray()) {
            QJsonArray a = v.toArray();
            // Expect at least 6 elements in the compact format
            if (a.size() < 6) return false;
            out.P00 = a.at(0).toDouble(0.0);
            out.P10 = a.at(1).toDouble(0.0);
            out.P01 = a.at(2).toDouble(0.0);
            out.P20 = a.at(3).toDouble(0.0);
            out.P11 = a.at(4).toDouble(0.0);
            out.P02 = a.at(5).toDouble(0.0);
            return true;
        }
        return false;
    };

    bool ok = true;
    ok &= parseC(arr.at(0), PeelForce);
    ok &= parseC(arr.at(1), Residual);

    if (!ok) {
        qDebug() << "JsonFormat2Coefficient: one or more elements invalid";
        return false;
    }

    return true;
}

bool DataBaseManager::Centralized2JsonFormat(const CENTRALIZED_PROPERTY Centralized, QString &strJson)
{
    // Produce a compact numeric array: [TimeMean, TimeStd, PowerMean, PowrStd, ForceMean, ResidualMean]
    QJsonArray arr;
    arr.append(Centralized.TimeMean);
    arr.append(Centralized.TimeStd);
    arr.append(Centralized.PowerMean);
    arr.append(Centralized.PowerStd);
    arr.append(Centralized.ForceMean);
    arr.append(Centralized.ResidualMean);

    QJsonDocument doc(arr);
    strJson = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    return true;
}

bool DataBaseManager::JsonFormat2Centralized(const QString strJson, CENTRALIZED_PROPERTY &Centralized)
{
    if (strJson.isEmpty()) return false;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "JsonFormat2Centralized: parse error:" << err.errorString();
        return false;
    }
    if (!doc.isArray()) {
        qDebug() << "JsonFormat2Centralized: expected JSON array";
        return false;
    }
    QJsonArray arr = doc.array();
    // Strict mode: accept only a numeric array of exactly 6 elements:
    // [TimeMean, TimeStd, PowerMean, PowrStd, ForceMean, ResidualMean]
    if (arr.size() != 6) {
        qDebug() << "JsonFormat2Centralized: expected array of 6 numeric elements, got" << arr.size();
        return false;
    }

    for (int i = 0; i < 6; ++i) {
        QJsonValue v = arr.at(i);
        if (!v.isDouble()) {
            qDebug() << "JsonFormat2Centralized: element" << i << "is not numeric";
            return false;
        }
    }

    Centralized.TimeMean     = arr.at(0).toDouble(0.0);
    Centralized.TimeStd      = arr.at(1).toDouble(0.0);
    Centralized.PowerMean    = arr.at(2).toDouble(0.0);
    Centralized.PowerStd      = arr.at(3).toDouble(0.0);
    Centralized.ForceMean    = arr.at(4).toDouble(0.0);
    Centralized.ResidualMean = arr.at(5).toDouble(0.0);
    return true;
}
