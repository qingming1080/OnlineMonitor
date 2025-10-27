#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "define.h"
#include "modbus/hbmodbusclient.h"
#include "DataBase/databasemanager.h"
///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int welderID READ welderID WRITE setWelderID NOTIFY welderIDChanged)

public:

    explicit Manual(int welderID = 0, QObject *parent = nullptr);
    ~Manual();

    Q_INVOKABLE int welderID() const;
    Q_INVOKABLE void setWelderID(int id);

    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Q_INVOKABLE void save();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();

    Q_INVOKABLE void startReading();
    Q_INVOKABLE void stopReading();

private slots:

signals:
    void welderIDChanged();

private:
    int m_welderID;

    QList<DataBaseManager::DB_MANUAL> m_listRawData;
    QList<DataBaseManager::DB_MANUAL> m_listManualData;
    HBModbusClient *m_modbusClient = nullptr;

    //TODO need to be removed
    int m_nextSerial = 1;

    bool CalibrateModel();

};

#endif // MANUAL_H
