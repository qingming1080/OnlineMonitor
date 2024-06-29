#include "databasemanager.h"
#include <QDebug>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>

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

QList<_Configuration_Data> DataBaseManager::getConfigurationData()
{
    QList<_Configuration_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(CONFIGURATION_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Configuration_Data data;
        data.welder_id        = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_welder_id).toInt();
        data.welder_name      = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_welder_name).toString();
        data.welder_type      = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_welder_type).toString();
        data.production_bacth = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_production_bacth).toInt();
        data.model_sample     = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_model_sample).toInt();
        data.lower_limit      = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_lower_limit).toInt();
        data.height_option    = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_height_option).toInt();
        data.connect_type     = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_connect_type).toInt();
        data.connect_id       = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_connect_id).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setConfigurationData(int deviceID, _CONFIGURATION_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(column), getConfiguration_ColumnName(_CONFIGURATION_welder_id));

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
                          .arg(CONFIGURATION_TABLENAME, getConfiguration_ColumnName(_CONFIGURATION_welder_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", deviceID);

    return query.exec();
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
                              ", :connect_id)")
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

    return query.exec();
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
        data.id             = query.value(_NETWORK_COLUMN::_NETWORK_id).toInt();
        data.type           = query.value(_NETWORK_COLUMN::_NETWORK_type).toInt();
        data.protocol       = query.value(_NETWORK_COLUMN::_NETWORK_protocol).toInt();
        data.local_ip       = query.value(_NETWORK_COLUMN::_NETWORK_local_ip).toString();
        data.local_port     = query.value(_NETWORK_COLUMN::_NETWORK_local_port).toInt();
        data.remote_ip      = query.value(_NETWORK_COLUMN::_NETWORK_remote_ip).toString();
        data.server_port    = query.value(_NETWORK_COLUMN::_NETWORK_server_port).toInt();
        data.user           = query.value(_NETWORK_COLUMN::_NETWORK_user).toString();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setNetworkData(int networkID, _NETWORK_COLUMN column, QVariant data)
{
    if(networkID == 1)
        return false;

    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(NETWORK_TABLENAME, getNetwork_ColumnName(column), getNetwork_ColumnName(_NETWORK_id));

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
                          .arg(NETWORK_TABLENAME,getNetwork_ColumnName(_NETWORK_id));

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
        data.id             = query.value(_RS232_COLUMN::_RS232_id).toInt();
        data.port           = query.value(_RS232_COLUMN::_RS232_port).toString();
        data.baud_rate      = query.value(_RS232_COLUMN::_RS232_baud_rate).toInt();
        data.data_bit       = query.value(_RS232_COLUMN::_RS232_data_bit).toInt();
        data.parity_bit     = query.value(_RS232_COLUMN::_RS232_parity_bit).toString();
        data.stop_bit       = query.value(_RS232_COLUMN::_RS232_stop_bit).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setRS232Data(int id, _RS232_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(RS232_TABLENAME, getRS232_ColumnName(column), getRS232_ColumnName(_RS232_id));

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
                          .arg(RS232_TABLENAME, getRS232_ColumnName(_RS232_id));

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

QList<_IO_Data> DataBaseManager::getIOData()
{
    QList<_IO_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(IO_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _IO_Data data;
        data.id         = query.value(_IO_COLUMN::_IO_id).toInt();
        data.welder_id  = query.value(_IO_COLUMN::_IO_welder_id).toInt();
        data.pin        = query.value(_IO_COLUMN::_IO_pin).toInt();
        data.available  = query.value(_IO_COLUMN::_IO_available).toInt();
        data.signal     = query.value(_IO_COLUMN::_IO_signal).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setIOData(int id, _IO_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(IO_TABLENAME, getIO_ColumnName(column), getIO_ColumnName(_IO_id));

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
                          .arg(IO_TABLENAME, getIO_ColumnName(_IO_id));

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

QList<_Manual_Data> DataBaseManager::getManualData()
{
    QList<_Manual_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(MANUAL_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Manual_Data data;
        data.id              = query.value(_MANUAL_COLUMN::_MANUAL_id).toInt();
        data.welder_id       = query.value(_MANUAL_COLUMN::_MANUAL_welder_id).toInt();
        data.create_time     = query.value(_MANUAL_COLUMN::_MANUAL_create_time).toString();
        data.serial_number   = query.value(_MANUAL_COLUMN::_MANUAL_serial_number).toInt();
        data.cycle_count     = query.value(_MANUAL_COLUMN::_MANUAL_cycle_count).toInt();
        data.energy          = query.value(_MANUAL_COLUMN::_MANUAL_energy).toInt();
        data.amplitude       = query.value(_MANUAL_COLUMN::_MANUAL_amplitude).toInt();
        data.pressure        = query.value(_MANUAL_COLUMN::_MANUAL_pressure).toInt();
        data.time            = query.value(_MANUAL_COLUMN::_MANUAL_time).toString();
        data.power           = query.value(_MANUAL_COLUMN::_MANUAL_power).toInt();
        data.pre_height      = query.value(_MANUAL_COLUMN::_MANUAL_pre_height).toInt();
        data.post_height     = query.value(_MANUAL_COLUMN::_MANUAL_post_height).toInt();
        data.actual_force    = query.value(_MANUAL_COLUMN::_MANUAL_actual_force).toInt();
        data.actual_degree   = query.value(_MANUAL_COLUMN::_MANUAL_actual_degree).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setManualData(int id, _MANUAL_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(MANUAL_TABLENAME, getManual_ColumnName(column), getManual_ColumnName(_MANUAL_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":newdata", data);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::removeManualRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(MANUAL_TABLENAME, getManual_ColumnName(_MANUAL_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

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
        data.id                    = query.value(_MODEL_COLUMN::_MODEL_id).toInt();
        data.welder_id             = query.value(_MODEL_COLUMN::_MODEL_welder_id).toInt();
        data.create_time           = query.value(_MODEL_COLUMN::_MODEL_create_time).toString();
        data.energy                = query.value(_MODEL_COLUMN::_MODEL_energy).toInt();
        data.amplitude             = query.value(_MODEL_COLUMN::_MODEL_amplitude).toInt();
        data.pressure              = query.value(_MODEL_COLUMN::_MODEL_pressure).toInt();
        data.time_alpha            = query.value(_MODEL_COLUMN::_MODEL_time_alpha).toString();
        data.time_beta             = query.value(_MODEL_COLUMN::_MODEL_time_beta).toString();
        data.power_alpha           = query.value(_MODEL_COLUMN::_MODEL_power_alpha).toInt();
        data.power_beta            = query.value(_MODEL_COLUMN::_MODEL_power_beta).toInt();
        data.pre_height_alpha      = query.value(_MODEL_COLUMN::_MODEL_pre_height_alpha).toInt();
        data.pre_height_beta       = query.value(_MODEL_COLUMN::_MODEL_pre_height_beta).toInt();
        data.post_height_alpha     = query.value(_MODEL_COLUMN::_MODEL_post_height_alpha).toInt();
        data.post_height_beta      = query.value(_MODEL_COLUMN::_MODEL_post_height_beta).toInt();
        data.force_alpha           = query.value(_MODEL_COLUMN::_MODEL_force_alpha).toInt();
        data.force_beta            = query.value(_MODEL_COLUMN::_MODEL_force_beta).toInt();
        data.residual_alpha        = query.value(_MODEL_COLUMN::_MODEL_residual_alpha).toInt();
        data.residual_beta         = query.value(_MODEL_COLUMN::_MODEL_residual_beta).toInt();
        data.current_sample_count  = query.value(_MODEL_COLUMN::_MODEL_current_sample_count).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::removeModelRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(MODEL_TABLENAME, getModel_ColumnName(_MODEL_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
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

QList<_Production_Data> DataBaseManager::getProductionData()
{
    QList<_Production_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(PRODUCTION_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _Production_Data data;
        data.id                       = query.value(_PRODUCTION_COLUMN::_PRODUCTION_id).toInt();
        data.welder_id                = query.value(_PRODUCTION_COLUMN::_PRODUCTION_welder_id).toInt();
        data.model_id                 = query.value(_PRODUCTION_COLUMN::_PRODUCTION_model_id).toInt();
        data.create_time              = query.value(_PRODUCTION_COLUMN::_PRODUCTION_create_time).toString();
        data.serial_number            = query.value(_PRODUCTION_COLUMN::_PRODUCTION_serial_number).toInt();
        data.cycle_count              = query.value(_PRODUCTION_COLUMN::_PRODUCTION_cycle_count).toInt();
        data.batch_count              = query.value(_PRODUCTION_COLUMN::_PRODUCTION_batch_count).toInt();
        data.energy                   = query.value(_PRODUCTION_COLUMN::_PRODUCTION_energy).toInt();
        data.amplitude                = query.value(_PRODUCTION_COLUMN::_PRODUCTION_amplitude).toInt();
        data.pressure                 = query.value(_PRODUCTION_COLUMN::_PRODUCTION_pressure).toInt();
        data.time                     = query.value(_PRODUCTION_COLUMN::_PRODUCTION_time).toInt();
        data.power                    = query.value(_PRODUCTION_COLUMN::_PRODUCTION_power).toInt();
        data.pre_height               = query.value(_PRODUCTION_COLUMN::_PRODUCTION_pre_height).toInt();
        data.post_height              = query.value(_PRODUCTION_COLUMN::_PRODUCTION_post_height).toInt();
        data.force                    = query.value(_PRODUCTION_COLUMN::_PRODUCTION_force).toInt();
        data.residual                 = query.value(_PRODUCTION_COLUMN::_PRODUCTION_residual).toInt();
        data.good_rate                = query.value(_PRODUCTION_COLUMN::_PRODUCTION_good_rate).toInt();
        data.good_subtotal_cycles     = query.value(_PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles).toInt();
        data.suspect_subtotal_cycles  = query.value(_PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles).toInt();
        data.not_definite_cycles      = query.value(_PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::removeProductionRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(PRODUCTION_TABLENAME, getProduction_ColumnName(_PRODUCTION_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
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

QList<_System_Data> DataBaseManager::getSystemData()
{
    QList<_System_Data> list;

    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("SELECT * FROM %1").arg(SYSTEM_TABLENAME);
    if (!query.exec(execStr))
    {
        qDebug() << "查询失败: " << query.lastError();
    }

    while(query.next())
    {
        _System_Data data;
        data.id                   = query.value(_SYSTEM_COLUMN::_SYSTEM_id).toInt();
        data.welder_id            = query.value(_SYSTEM_COLUMN::_SYSTEM_welder_id).toInt();
        data.single_fact_setting  = query.value(_SYSTEM_COLUMN::_SYSTEM_single_fact_setting).toInt();
        data.general_fact_setting = query.value(_SYSTEM_COLUMN::_SYSTEM_general_fact_setting).toInt();
        data.other_fact_setting   = query.value(_SYSTEM_COLUMN::_SYSTEM_other_fact_setting).toInt();
        data.auto_model_limit     = query.value(_SYSTEM_COLUMN::_SYSTEM_auto_model_limit).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::setSystemData(int id, _SYSTEM_COLUMN column, QVariant data)
{
    QSqlQuery query;
    // %1_表格名称 %2_要修改的字段名称 %3_ID字段名称
    QString execStr = QString("UPDATE %1 SET %2 = :newdata WHERE %3 = :id")
                          .arg(SYSTEM_TABLENAME, getSystem_ColumnName(column), getSystem_ColumnName(_SYSTEM_id));

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
    qDebug() << execStr;
    if(!query.exec(execStr))
    {
        qDebug() << query.lastError();
        return 0;
    }
    if(query.next())
        return query.value(3).toInt();

    return 0;
}

DataBaseManager::DataBaseManager(QObject *parent)
    : QObject{parent}
{
    init();
}

void DataBaseManager::init()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("C:\\Users\\cxy\\Desktop\\HB平台\\数据库格式.db");
    if (!m_database.open())
    {
        qDebug() << "Database Open Fail ";
        qDebug() << m_database.lastError();
    }
    else
    {
        qDebug() << "Database Open Success";
        b_hasFeature = m_database.driver()->hasFeature(QSqlDriver::QuerySize);
    }
}

QString DataBaseManager::getConfiguration_ColumnName(_CONFIGURATION_COLUMN column)
{
    switch(column)
    {
    case _CONFIGURATION_welder_id:
        return "welder_id";
    case _CONFIGURATION_welder_name:
        return "welder_name";
    case _CONFIGURATION_welder_type:
        return "welder_type";
    case _CONFIGURATION_production_bacth:
        return "production_bacth";
    case _CONFIGURATION_model_sample:
        return "model_sample";
    case _CONFIGURATION_lower_limit:
        return "lower_limit";
    case _CONFIGURATION_height_option:
        return "height_option";
    case _CONFIGURATION_connect_type:
        return "connect_type";
    case _CONFIGURATION_connect_id:
        return "connect_id";
    }

    return "";
}

QString DataBaseManager::getNetwork_ColumnName(_NETWORK_COLUMN column)
{
    switch(column)
    {
    case _NETWORK_id:
        return "id";
    case _NETWORK_type:
        return "type";
    case _NETWORK_protocol:
        return "protocol";
    case _NETWORK_local_ip:
        return "local_ip";
    case _NETWORK_local_port:
        return "local_port";
    case _NETWORK_remote_ip:
        return "remote_ip";
    case _NETWORK_server_port:
        return "server_port";
    case _NETWORK_user:
        return "user";
    }

    return "";
}

QString DataBaseManager::getRS232_ColumnName(_RS232_COLUMN column)
{
    switch(column)
    {
    case _RS232_id:
        return "id";
    case _RS232_port:
        return "port";
    case _RS232_baud_rate:
        return "baud_rate";
    case _RS232_data_bit:
        return "data_bit";
    case _RS232_parity_bit:
        return "parity_bit";
    case _RS232_stop_bit:
        return "stop_bit";
    }

    return "";
}

QString DataBaseManager::getIO_ColumnName(_IO_COLUMN column)
{
    switch(column)
    {
    case _IO_id:
        return "id";
    case _IO_welder_id:
        return "welder_id";
    case _IO_pin:
        return "pin";
    case _IO_available:
        return "available";
    case _IO_signal:
        return "signal";
    }

    return "";
}

QString DataBaseManager::getManual_ColumnName(_MANUAL_COLUMN column)
{
    switch(column)
    {
    case _MANUAL_id:
        return "id";
    case _MANUAL_welder_id:
        return "welder_id";
    case _MANUAL_create_time:
        return "create_time";
    case _MANUAL_serial_number:
        return "serial_number";
    case _MANUAL_cycle_count:
        return "cycle_count";
    case _MANUAL_energy:
        return "energy";
    case _MANUAL_amplitude:
        return "amplitude";
    case _MANUAL_pressure:
        return "pressure";
    case _MANUAL_time:
        return "time";
    case _MANUAL_power:
        return "power";
    case _MANUAL_pre_height:
        return "pre_height";
    case _MANUAL_post_height:
        return "post_height";
    case _MANUAL_actual_force:
        return "actual_force";
    case _MANUAL_actual_degree:
        return "actual_degree";
    }

    return "";
}

QString DataBaseManager::getModel_ColumnName(_MODEL_COLUMN column)
{
    switch(column)
    {
    case _MODEL_id:
        return "id";
    case _MODEL_welder_id:
        return "welder_id";
    case _MODEL_create_time:
        return "create_time";
    case _MODEL_energy:
        return "energy";
    case _MODEL_amplitude:
        return "amplitude";
    case _MODEL_pressure:
        return "pressure";
    case _MODEL_time_alpha:
        return "time_alpha";
    case _MODEL_time_beta:
        return "time_beta";
    case _MODEL_power_alpha:
        return "power_alpha";
    case _MODEL_power_beta:
        return "power_beta";
    case _MODEL_pre_height_alpha:
        return "pre_height_alpha";
    case _MODEL_pre_height_beta:
        return "pre_height_beta";
    case _MODEL_post_height_alpha:
        return "post_height_alpha";
    case _MODEL_post_height_beta:
        return "post_height_beta";
    case _MODEL_force_alpha:
        return "force_alpha";
    case _MODEL_force_beta:
        return "force_beta";
    case _MODEL_residual_alpha:
        return "residual_alpha";
    case _MODEL_residual_beta:
        return "residual_beta";
    case _MODEL_current_sample_count:
        return "current_sample_count";
    }

    return "";
}

QString DataBaseManager::getProduction_ColumnName(_PRODUCTION_COLUMN column)
{
    switch(column)
    {
    case _PRODUCTION_id:
        return "id";
    case _PRODUCTION_welder_id:
        return "welder_id";
    case _PRODUCTION_model_id:
        return "model_id";
    case _PRODUCTION_create_time:
        return "create_time";
    case _PRODUCTION_serial_number:
        return "serial_number";
    case _PRODUCTION_cycle_count:
        return "cycle_count";
    case _PRODUCTION_batch_count:
        return "batch_count";
    case _PRODUCTION_energy:
        return "energy";
    case _PRODUCTION_amplitude:
        return "amplitude";
    case _PRODUCTION_pressure:
        return "pressure";
    case _PRODUCTION_time:
        return "time";
    case _PRODUCTION_power:
        return "power";
    case _PRODUCTION_pre_height:
        return "pre_height";
    case _PRODUCTION_post_height:
        return "post_height";
    case _PRODUCTION_force:
        return "force";
    case _PRODUCTION_residual:
        return "residual";
    case _PRODUCTION_good_rate:
        return "good_rate";
    case _PRODUCTION_good_subtotal_cycles:
        return "good_subtotal_cycles";
    case _PRODUCTION_suspect_subtotal_cycles:
        return "suspect_subtotal_cycles";
    case _PRODUCTION_not_definite_cycles:
        return "not_definite_cycles";
    }

    return "";
}

QString DataBaseManager::getSystem_ColumnName(_SYSTEM_COLUMN column)
{
    switch(column)
    {
    case _SYSTEM_id:
        return "id";
    case _SYSTEM_welder_id:
        return "welder_id";
    case _SYSTEM_single_fact_setting:
        return "single_fact_setting";
    case _SYSTEM_general_fact_setting:
        return "general_fact_setting";
    case _SYSTEM_other_fact_setting:
        return "other_fact_setting";
    case _SYSTEM_auto_model_limit:
        return "auto_model_limit";
    }

    return "";
}
