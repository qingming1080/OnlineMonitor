#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "define.h"
#include "modbus/hbmodbusclient.h"
///
/// \brief The Manual class : manual
/// 暴露添加一行接口，暴露数据库保存接口
class Manual : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int welderID READ welderID WRITE setWelderID NOTIFY welderIDChanged)
public:

    explicit Manual(int welderID = 0,HBModbusClient* modbusClient= nullptr,QObject *parent = nullptr);
    ~Manual();

    Q_INVOKABLE int welderID() const;
    Q_INVOKABLE void setWelderID(int id);

    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);

    Q_INVOKABLE void save();
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void loadData();

    Q_INVOKABLE void startReading();
    Q_INVOKABLE void stopReading();

private slots:
    void onNewManualData(const _Manual_Data& data);
    void flushPendingData();


signals:
    void welderIDChanged();


private:
    int m_welderID;

    HBModbusClient* m_modbusClient;

    QList<_Manual_Data> m_data;


    QList<_Manual_Data> m_pendingData;

    QTimer m_flushTimer;

};

#endif // MANUAL_H
