#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QApplication>

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

QList<int> DataBaseManager::getDeviceNums()
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);

    qDebug() << execStr;
    if (!query.exec(execStr))
    {
        qDebug() << "Configuration查询失败: " << query.lastError();
    }

    QList<int> nums;
    while(query.next()){
        nums.push_back(query.value(QmlEnum::CONFIGURATION_welder_id).toInt());
    }

    return nums;
}

_Configuration_Data DataBaseManager::getConfigurationData(int welderID)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID").arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(QmlEnum::CONFIGURATION_welder_id));

    query.prepare(execStr);
    query.bindValue(":welderID", welderID);

    if (!query.exec())
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    if(query.next())
    {
        _Configuration_Data data;
        data.welder_id        = query.value(QmlEnum::CONFIGURATION_welder_id).toInt();
        data.welder_name      = query.value(QmlEnum::CONFIGURATION_welder_name).toString();
        data.welder_type      = query.value(QmlEnum::CONFIGURATION_welder_type).toString();
        data.production_bacth = query.value(QmlEnum::CONFIGURATION_production_bacth).toInt();
        data.model_sample     = query.value(QmlEnum::CONFIGURATION_model_sample).toInt();
        data.lower_limit      = query.value(QmlEnum::CONFIGURATION_lower_limit).toInt();
        data.height_option    = query.value(QmlEnum::CONFIGURATION_height_option).toInt();
        data.connect_type     = query.value(QmlEnum::CONFIGURATION_connect_type).toInt();
        data.connect_id       = query.value(QmlEnum::CONFIGURATION_connect_id).toInt();
        data.mes_port         = query.value(QmlEnum::CONFIGURATION_mes_port).toInt();
        data.mes_ip           = query.value(QmlEnum::CONFIGURATION_mes_ip).toString();
        data.device_ip        = query.value(QmlEnum::CONFIGURATION_device_ip).toString();

        return data;
    }

    _Configuration_Data data;
    return data;
}

bool DataBaseManager::setConfigurationData(int deviceID, QmlEnum::CONFIGURATION_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(column), getConfiguration_ColumnName(QmlEnum::CONFIGURATION_welder_id));

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
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(QmlEnum::CONFIGURATION_welder_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", deviceID);
    bool ret = query.exec();
    return ret;
}

bool DataBaseManager::insertConfigurationDevice(_Configuration_Data data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":welder_id"
                              ", :welder_name"
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
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":welder_name", data.welder_name);
    query.bindValue(":welder_type", data.welder_type);
    query.bindValue(":production_bacth", data.production_bacth);
    query.bindValue(":model_sample", data.model_sample);
    query.bindValue(":lower_limit", data.lower_limit);
    query.bindValue(":height_option", data.height_option);
    query.bindValue(":connect_type", data.connect_type);
    query.bindValue(":connect_id", data.connect_id);
    query.bindValue(":mes_port", data.mes_port);
    query.bindValue(":mes_ip", data.mes_ip);
    query.bindValue(":device_ip", data.device_ip);
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
        data.local_ip       = query.value(QmlEnum::NETWORK_local_ip).toString();
        data.local_port     = query.value(QmlEnum::NETWORK_local_port).toInt();
        data.remote_ip      = query.value(QmlEnum::NETWORK_remote_ip).toString();
        data.server_port    = query.value(QmlEnum::NETWORK_server_port).toInt();
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
                              ", :local_ip"
                              ", :local_port"
                              ", :remote_ip"
                              ", :server_port"
                              ", :user)")
                          .arg(NETWORK_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":type", data.type);
    query.bindValue(":protocol", data.protocol);
    query.bindValue(":local_ip", data.local_ip);
    query.bindValue(":local_port", data.local_port);
    query.bindValue(":remote_ip", data.remote_ip);
    query.bindValue(":server_port", data.server_port);
    query.bindValue(":user", data.user);

    return query.exec();
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

QList<_Manual_Data> DataBaseManager::getManualData(int welderID)
{
    QList<_Manual_Data> list;

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
        _Manual_Data data;
        data.id              = query.value(QmlEnum::MANUAL_id).toInt();
        data.welder_id       = query.value(QmlEnum::MANUAL_welder_id).toInt();
        data.create_time     = query.value(QmlEnum::MANUAL_create_time).toString();
        data.serial_number   = query.value(QmlEnum::MANUAL_serial_number).toInt();
        data.cycle_count     = query.value(QmlEnum::MANUAL_cycle_count).toInt();
        data.energy          = query.value(QmlEnum::MANUAL_energy).toInt();
        data.amplitude       = query.value(QmlEnum::MANUAL_amplitude).toInt();
        data.pressure        = query.value(QmlEnum::MANUAL_pressure).toInt();
        data.time            = query.value(QmlEnum::MANUAL_time).toString();
        data.power           = query.value(QmlEnum::MANUAL_power).toInt();
        data.pre_height      = query.value(QmlEnum::MANUAL_pre_height).toInt();
        data.post_height     = query.value(QmlEnum::MANUAL_post_height).toInt();
        data.actual_force    = query.value(QmlEnum::MANUAL_actual_force).toInt();
        data.actual_degree   = query.value(QmlEnum::MANUAL_actual_degree).toInt();

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

bool DataBaseManager::insertManualRow(_Manual_Data data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :welder_id"
                              ", :create_time"
                              ", :serial_number"
                              ", :cycle_count"
                              ", :energy"
                              ", :amplitude"
                              ", :pressure"
                              ", :time"
                              ", :power"
                              ", :pre_height"
                              ", :post_height"
                              ", :actual_force"
                              ", :actual_degree)").arg(MANUAL_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":create_time", data.create_time);
    query.bindValue(":serial_number", data.serial_number);
    query.bindValue(":cycle_count", data.cycle_count);
    query.bindValue(":energy", data.energy);
    query.bindValue(":amplitude", data.amplitude);
    query.bindValue(":pressure", data.pressure);
    query.bindValue(":time", data.time);
    query.bindValue(":power", data.power);
    query.bindValue(":pre_height", data.pre_height);
    query.bindValue(":post_height", data.post_height);
    query.bindValue(":actual_force", data.actual_force);
    query.bindValue(":actual_degree", data.actual_degree);

    return query.exec();
}

QList<_Model_Data> DataBaseManager::getModelData()
{
    QList<_Model_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(MODEL_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Model_Data data;
        data.id                    = query.value(QmlEnum::MODEL_id).toInt();
        data.welder_id             = query.value(QmlEnum::MODEL_welder_id).toInt();
        data.create_time           = query.value(QmlEnum::MODEL_create_time).toString();
        data.energy                = query.value(QmlEnum::MODEL_energy).toInt();
        data.amplitude             = query.value(QmlEnum::MODEL_amplitude).toInt();
        data.pressure              = query.value(QmlEnum::MODEL_pressure).toInt();
        data.time_alpha            = query.value(QmlEnum::MODEL_time_alpha).toString();
        data.time_beta             = query.value(QmlEnum::MODEL_time_beta).toString();
        data.power_alpha           = query.value(QmlEnum::MODEL_power_alpha).toInt();
        data.power_beta            = query.value(QmlEnum::MODEL_power_beta).toInt();
        data.pre_height_alpha      = query.value(QmlEnum::MODEL_pre_height_alpha).toInt();
        data.pre_height_beta       = query.value(QmlEnum::MODEL_pre_height_beta).toInt();
        data.post_height_alpha     = query.value(QmlEnum::MODEL_post_height_alpha).toInt();
        data.post_height_beta      = query.value(QmlEnum::MODEL_post_height_beta).toInt();
        data.force_alpha           = query.value(QmlEnum::MODEL_force_alpha).toInt();
        data.force_beta            = query.value(QmlEnum::MODEL_force_beta).toInt();
        data.residual_alpha        = query.value(QmlEnum::MODEL_residual_alpha).toInt();
        data.residual_beta         = query.value(QmlEnum::MODEL_residual_beta).toInt();
        data.current_sample_count  = query.value(QmlEnum::MODEL_current_sample_count).toInt();

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

bool DataBaseManager::insertModelRow(_Model_Data data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :welder_id"
                              ", :create_time"
                              ", :energy"
                              ", :amplitude"
                              ", :pressure"
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
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":create_time", data.create_time);
    query.bindValue(":energy", data.energy);
    query.bindValue(":amplitude", data.amplitude);
    query.bindValue(":pressure", data.pressure);
    query.bindValue(":time_alpha", data.time_alpha);
    query.bindValue(":time_beta", data.time_beta);
    query.bindValue(":power_alpha", data.power_alpha);
    query.bindValue(":power_beta", data.power_beta);
    query.bindValue(":pre_height_alpha", data.pre_height_alpha);
    query.bindValue(":pre_height_beta", data.pre_height_beta);
    query.bindValue(":post_height_alpha", data.post_height_alpha);
    query.bindValue(":post_height_beta", data.post_height_beta);
    query.bindValue(":force_alpha", data.force_alpha);
    query.bindValue(":force_beta", data.force_beta);
    query.bindValue(":residual_alpha", data.residual_alpha);
    query.bindValue(":residual_beta", data.residual_beta);
    query.bindValue(":current_sample_count", data.current_sample_count);

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

        // 能量 ***J -> ***
        QString energyStr = query.value(QmlEnum::PRODUCTION_energy).toString();
        data.energy = energyStr.leftRef(energyStr.length()-1).toInt();

        data.amplitude                = query.value(QmlEnum::PRODUCTION_amplitude).toInt();
        data.pressure                 = query.value(QmlEnum::PRODUCTION_pressure).toInt();

        // 时间 *.**s - > *.**
        data.time                     = query.value(QmlEnum::PRODUCTION_time).toString();
        data.time = data.time.left(data.time.length()-1);

        // 功率 ***W -> ***
        QString powerStr = query.value(QmlEnum::PRODUCTION_power).toString();
        data.power = powerStr.leftRef(powerStr.length()-1).toInt();

        // 高度 *.**mm -> *.**
        QString pre_heightStr = query.value(QmlEnum::PRODUCTION_pre_height).toString();
        data.pre_height = pre_heightStr.leftRef(pre_heightStr.length()-2).toDouble();
        QString post_heightStr = query.value(QmlEnum::PRODUCTION_post_height).toString();
        data.post_height = post_heightStr.leftRef(post_heightStr.length()-2).toDouble();

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

//_Weld_TrendData DataBaseManager::getWeldTrendData(int welderID)
//{
//    _Weld_TrendData result;

//    QSqlQuery query;
//    if(welderID != 0)
//    {
//        // %1_表格名称
//        QString execStr = QString("SELECT * FROM %1 WHERE %2 = :welderID ORDER BY %3 DESC LIMIT 150")
//                              .arg(PRODUCTION_TABLENAME
//                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_welder_id)
//                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time));

//        query.prepare(execStr);
//        query.bindValue(":welderID", welderID);
//    }
//    else
//    {
//        // %1_表格名称
//        QString execStr = QString("SELECT * FROM %1 ORDER BY %2 DESC LIMIT 150")
//                              .arg(PRODUCTION_TABLENAME
//                                   , getProduction_ColumnName(QmlEnum::PRODUCTION_create_time));
//        qDebug() << execStr;
//        query.prepare(execStr);
//    }

//    if (!query.exec())
//    {
//        qDebug() << "Production查询失败: " << query.lastError();
//    }

//    bool isFirst = true;
//    while(query.next())
//    {
//        _Production_Data data;
//        data.id                       = query.value(QmlEnum::PRODUCTION_id).toInt();
//        data.welder_id                = query.value(QmlEnum::PRODUCTION_welder_id).toInt();
//        data.model_id                 = query.value(QmlEnum::PRODUCTION_model_id).toInt();
//        data.create_time              = query.value(QmlEnum::PRODUCTION_create_time).toString();
//        data.serial_number            = query.value(QmlEnum::PRODUCTION_serial_number).toInt();
//        data.cycle_count              = query.value(QmlEnum::PRODUCTION_cycle_count).toInt();
//        data.batch_count              = query.value(QmlEnum::PRODUCTION_batch_count).toInt();

//        // 能量 ***J -> ***
//        QString energyStr = query.value(QmlEnum::PRODUCTION_energy).toString();
//        data.energy = energyStr.leftRef(energyStr.length()-1).toInt();

//        data.amplitude                = query.value(QmlEnum::PRODUCTION_amplitude).toInt();
//        data.pressure                 = query.value(QmlEnum::PRODUCTION_pressure).toInt();

//        // 时间 *.**s - > *.**
//        data.time                     = query.value(QmlEnum::PRODUCTION_time).toString();
//        data.time = data.time.left(data.time.length()-1);

//        // 功率 ***W -> ***
//        QString powerStr = query.value(QmlEnum::PRODUCTION_power).toString();
//        data.power = powerStr.leftRef(powerStr.length()-1).toInt();

//        // 高度 *.**mm -> *.**
//        QString pre_heightStr = query.value(QmlEnum::PRODUCTION_pre_height).toString();
//        data.pre_height = pre_heightStr.leftRef(pre_heightStr.length()-2).toDouble();
//        QString post_heightStr = query.value(QmlEnum::PRODUCTION_post_height).toString();
//        data.post_height = post_heightStr.leftRef(post_heightStr.length()-2).toDouble();

//        data.force                    = query.value(QmlEnum::PRODUCTION_force).toInt();
//        data.residual                 = query.value(QmlEnum::PRODUCTION_residual).toInt();
//        data.good_rate                = query.value(QmlEnum::PRODUCTION_good_rate).toInt();
//        data.good_subtotal_cycles     = query.value(QmlEnum::PRODUCTION_good_subtotal_cycles).toInt();
//        data.suspect_subtotal_cycles  = query.value(QmlEnum::PRODUCTION_suspect_subtotal_cycles).toInt();
//        data.not_definite_cycles      = query.value(QmlEnum::PRODUCTION_not_definite_cycles).toInt();
//        data.final_result             = query.value(QmlEnum::PRODUCTION_final_result).toInt();

//        // 计入首次大小
//        if(isFirst)
//        {
//            isFirst = false;

//            result.id_X_Min = data.id;
//            result.id_X_Max = data.id;
//            result.before_Y_Min = data.pre_height;
//            result.before_Y_Max = data.pre_height;
//            result.after_Y_Min = data.post_height;
//            result.after_Y_Max = data.post_height;
//            result.time_Y_Min = data.time;
//            result.time_Y_Max = data.time;
//            result.power_Y_Min = data.power;
//            result.power_Y_Max = data.power;
//        }

//        // 确定X轴大小
//        if(data.id < result.id_X_Min)
//            result.id_X_Min = data.id;
//        if(data.id > result.id_X_Max)
//            result.id_X_Max = data.id;
//        // 焊前高度 Y轴
//        if(data.pre_height < result.before_Y_Min)
//            result.before_Y_Min = data.pre_height;
//        if(data.pre_height > result.before_Y_Max)
//            result.before_Y_Max = data.pre_height;
//        // 焊后高度 Y轴
//        if(data.post_height < result.after_Y_Min)
//            result.after_Y_Min = data.post_height;
//        if(data.post_height > result.after_Y_Max)
//            result.after_Y_Max = data.post_height;
//        // 时间 Y轴
//        if(data.time.toDouble() < result.time_Y_Min.toDouble())
//            result.time_Y_Min = data.time;
//        if(data.time.toDouble() > result.time_Y_Max.toDouble())
//            result.time_Y_Max = data.time;
//        // 功率
//        if(data.power < result.power_Y_Min)
//            result.power_Y_Min = data.power;
//        if(data.power > result.power_Y_Max)
//            result.power_Y_Max = data.power;

//        result.data.push_back(data);
//    }

//    return result;
//}

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
        QPair<int, QString> pair;
        pair.second = startTime.addSecs(timeInterVal * i).toString("yyyy-MM-dd hh:mm:ss");
        result.points.push_back(pair);
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
        if(production_num == 0)
            result.points[i].first = 0;
        else
            result.points[i].first = double(good_num)/production_num * 100;
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
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values("
                              ":id"
                              ", :welder_id"
                              ", :model_id"
                              ", :create_time"
                              ", :serial_number"
                              ", :cycle_count"
                              ", :batch_count"
                              ", :energy"
                              ", :amplitude"
                              ", :pressure"
                              ", :time"
                              ", :power"
                              ", :pre_height"
                              ", :post_height"
                              ", :force"
                              ", :residual"
                              ", :good_rate"
                              ", :good_subtotal_cycles"
                              ", :suspect_subtotal_cycles"
                              ", :not_definite_cycles)")
                          .arg(PRODUCTION_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":model_id", data.model_id);
    query.bindValue(":create_time", data.create_time);
    query.bindValue(":serial_number", data.serial_number);
    query.bindValue(":cycle_count", data.cycle_count);
    query.bindValue(":batch_count", data.batch_count);
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



    return query.exec();
}

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
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/onlinemonitor.db";
    qDebug() << dbPath;
    m_database.setDatabaseName(dbPath);
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

QString DataBaseManager::getConfiguration_ColumnName(QmlEnum::CONFIGURATION_COLUMN column)
{
    switch(column)
    {
    case QmlEnum::CONFIGURATION_welder_id:
        return "welder_id";
    case QmlEnum::CONFIGURATION_welder_name:
        return "welder_name";
    case QmlEnum::CONFIGURATION_welder_type:
        return "welder_type";
    case QmlEnum::CONFIGURATION_production_bacth:
        return "production_bacth";
    case QmlEnum::CONFIGURATION_model_sample:
        return "model_sample";
    case QmlEnum::CONFIGURATION_lower_limit:
        return "lower_limit";
    case QmlEnum::CONFIGURATION_height_option:
        return "height_option";
    case QmlEnum::CONFIGURATION_connect_type:
        return "connect_type";
    case QmlEnum::CONFIGURATION_connect_id:
        return "connect_id";
    case QmlEnum::CONFIGURATION_mes_port:
        return "mes_port";
    case QmlEnum::CONFIGURATION_mes_ip:
        return "mes_ip";
    case QmlEnum::CONFIGURATION_device_ip:
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
    case QmlEnum::MODEL_pressure:
        return "pressure";
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
