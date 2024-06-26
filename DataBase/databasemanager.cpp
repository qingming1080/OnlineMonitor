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
        data.welder_type     = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_welder_type).toString();
        data.productionBacth = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_production_bacth).toInt();
        data.modelSample     = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_model_sample).toInt();
        data.lowerLimit      = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_lower_limit).toInt();
        data.heightOption    = query.value(_CONFIGURATION_COLUMN::_CONFIGURATION_height_option).toInt();

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
    QString execStr = QString("INSERT INTO %1 values(:id,:name,:type,:productionBacth,:modelSample,:lowerLimit,:heightOption)").arg(CONFIGURATION_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.welder_id);
    query.bindValue(":name", data.welder_name);
    query.bindValue(":type", data.welder_type);
    query.bindValue(":productionBacth", data.productionBacth);
    query.bindValue(":modelSample", data.modelSample);
    query.bindValue(":lowerLimit", data.lowerLimit);
    query.bindValue(":heightOption", data.heightOption);

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
        data.localIP        = query.value(_NETWORK_COLUMN::_NETWORK_local_ip).toString();
        data.localPort      = query.value(_NETWORK_COLUMN::_NETWORK_local_port).toInt();
        data.remoteIP       = query.value(_NETWORK_COLUMN::_NETWORK_remote_ip).toString();
        data.serverPort     = query.value(_NETWORK_COLUMN::_NETWORK_server_port).toInt();
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
    QString execStr = QString("INSERT INTO %1 values(:id, :type, :protocol, :localIP, :localPort, :remoteIP, :serverPort, :user)").arg(NETWORK_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":type", data.type);
    query.bindValue(":protocol", data.protocol);
    query.bindValue(":localIP", data.localIP);
    query.bindValue(":localPort", data.localPort);
    query.bindValue(":remoteIP", data.remoteIP);
    query.bindValue(":serverPort", data.serverPort);
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
    QString execStr = QString("INSERT INTO %1 values(:id, :port, :baud_rate, :data_bit, :parity_bit, :stop_bit)").arg(RS232_TABLENAME);

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
        data.siganl     = query.value(_IO_COLUMN::_IO_signal).toInt();

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
    QString execStr = QString("INSERT INTO %1 values(:id,:welder_id,:pin,:available,:siganl)").arg(IO_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":pin", data.pin);
    query.bindValue(":available", data.available);
    query.bindValue(":siganl", data.siganl);

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
        data.id              = query.value(_MODEL_COLUMN::_MODEL_id).toInt();
        data.welder_id       = query.value(_MODEL_COLUMN::_MODEL_welder_id).toInt();
        data.energy          = query.value(_MODEL_COLUMN::_MODEL_energy).toInt();
        data.amplitude       = query.value(_MODEL_COLUMN::_MODEL_amplitude).toInt();
        data.pressure        = query.value(_MODEL_COLUMN::_MODEL_pressure).toInt();
        data.welder_time     = query.value(_MODEL_COLUMN::_MODEL_welder_time).toDateTime();
        data.serial_number   = query.value(_MODEL_COLUMN::_MODEL_serial_number).toInt();
        data.power           = query.value(_MODEL_COLUMN::_MODEL_power).toInt();
        data.create_time     = query.value(_MODEL_COLUMN::_MODEL_create_time).toDateTime();
        data.tensile_force   = query.value(_MODEL_COLUMN::_MODEL_tensile_force).toInt();
        data.residual_degree = query.value(_MODEL_COLUMN::_MODEL_residual_degree).toInt();

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
    QString execStr = QString("INSERT INTO %1 values(:id,:welder_id,:energy,:amplitude,:pressure"
                              ",:welder_time,:serial_number,:power,:create_time,:tensile_force,:residual_degree)").arg(MODEL_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", data.id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":energy", data.energy);
    query.bindValue(":amplitude", data.amplitude);
    query.bindValue(":pressure", data.pressure);
    query.bindValue(":welder_time", data.welder_time);
    query.bindValue(":serial_number", data.serial_number);
    query.bindValue(":power", data.power);
    query.bindValue(":create_time", data.create_time);
    query.bindValue(":tensile_force", data.tensile_force);
    query.bindValue(":residual_degree", data.residual_degree);

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
        data.batch_id                = query.value(_PRODUCTION_COLUMN::_PRODUCTION_batch_id).toInt();
        data.welder_id               = query.value(_PRODUCTION_COLUMN::_PRODUCTION_welder_id).toInt();
        data.power                   = query.value(_PRODUCTION_COLUMN::_PRODUCTION_power).toInt();
        data.welder_time             = query.value(_PRODUCTION_COLUMN::_PRODUCTION_welder_time).toDateTime();
        data.energy                  = query.value(_PRODUCTION_COLUMN::_PRODUCTION_energy).toInt();
        data.pre_height              = query.value(_PRODUCTION_COLUMN::_PRODUCTION_pre_height).toInt();
        data.post_height             = query.value(_PRODUCTION_COLUMN::_PRODUCTION_post_height).toInt();
        data.create_time             = query.value(_PRODUCTION_COLUMN::_PRODUCTION_create_time).toDateTime();
        data.good_rate               = query.value(_PRODUCTION_COLUMN::_PRODUCTION_good_rate).toDouble();
        data.counting_total_cycles   = query.value(_PRODUCTION_COLUMN::_PRODUCTION_counting_total_cycles).toInt();
        data.good_subtotal_cycles    = query.value(_PRODUCTION_COLUMN::_PRODUCTION_good_subtotal_cycles).toInt();
        data.suspect_subtotal_cycles = query.value(_PRODUCTION_COLUMN::_PRODUCTION_suspect_subtotal_cycles).toInt();
        data.not_definite_cycles     = query.value(_PRODUCTION_COLUMN::_PRODUCTION_not_definite_cycles).toInt();

        list.push_back(data);
    }

    return list;
}

bool DataBaseManager::removeProductionRow(int id)
{
    QSqlQuery query;

    // %1_表格名称 %2_ID字段名称
    QString execStr = QString("DELETE FROM %1 WHERE %2=:id")
                          .arg(PRODUCTION_TABLENAME, getProduction_ColumnName(_PRODUCTION_batch_id));

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":id", id);

    return query.exec();
}

bool DataBaseManager::insertProductionRow(_Production_Data data)
{
    QSqlQuery query;
    // %1_表格名称
    QString execStr = QString("INSERT INTO %1 values(:batch_id,:welder_id,:power,:welder_time,:energy"
                              ",:pre_height,:post_height,:create_time,:good_rate,:counting_total_cycles,:good_subtotal_cycles"
                              ",:suspect_subtotal_cycles,:not_definite_cycles)").arg(PRODUCTION_TABLENAME);

    // 绑定属性
    query.prepare(execStr);
    query.bindValue(":batch_id", data.batch_id);
    query.bindValue(":welder_id", data.welder_id);
    query.bindValue(":power", data.power);
    query.bindValue(":welder_time", data.welder_time);
    query.bindValue(":energy", data.energy);
    query.bindValue(":pre_height", data.pre_height);
    query.bindValue(":post_height", data.post_height);
    query.bindValue(":create_time", data.create_time);
    query.bindValue(":good_rate", data.good_rate);
    query.bindValue(":counting_total_cycles", data.counting_total_cycles);
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

QString DataBaseManager::getModel_ColumnName(_MODEL_COLUMN column)
{
    switch(column)
    {
    case _MODEL_id:
        return "id";
    case _MODEL_welder_id:
        return "welder_id";
    case _MODEL_energy:
        return "energy";
    case _MODEL_amplitude:
        return "amplitude";
    case _MODEL_pressure:
        return "pressure";
    case _MODEL_welder_time:
        return "welder_time";
    case _MODEL_serial_number:
        return "serial_number";
    case _MODEL_power:
        return "power";
    case _MODEL_create_time:
        return "create_time";
    case _MODEL_tensile_force:
        return "tensile_force";
    case _MODEL_residual_degree:
        return "residual_degree";
    }

    return "";
}

QString DataBaseManager::getProduction_ColumnName(_PRODUCTION_COLUMN column)
{
    switch(column)
    {
    case _PRODUCTION_batch_id:
        return "batch_id";
    case _PRODUCTION_welder_id:
        return "welder_id";
    case _PRODUCTION_power:
        return "power";
    case _PRODUCTION_welder_time:
        return "welder_time";
    case _PRODUCTION_energy:
        return "energy";
    case _PRODUCTION_pre_height:
        return "pre_height";
    case _PRODUCTION_post_height:
        return "post_height";
    case _PRODUCTION_create_time:
        return "create_time";
    case _PRODUCTION_good_rate:
        return "good_rate";
    case _PRODUCTION_counting_total_cycles:
        return "counting_total_cycles";
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
