#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "DataBase/databasemanager.h"
#include "modbus/hbmodbusclient.h"
///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Manual(int welderID = 0, QObject *parent = nullptr);
    ~Manual();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;

    Q_INVOKABLE void saveData();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();
    void AppendNewRecordComming(const int welderId, const HBModbusClient::MODBUS_WELD_RESULT &data);

private slots:

signals:

private:
    int m_welderID;
    QList<DataBaseManager::DB_MANUAL> m_listManualRecords;

    bool CalibrateModel();

};

#endif // MANUAL_H
