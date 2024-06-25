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
