#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>
#include "define.h"

class History : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int deviceID READ deviceID WRITE setDeviceID NOTIFY deviceIDChanged)
    Q_PROPERTY(int finalResult READ finalResult WRITE setFinalResult NOTIFY finalResultChanged)
public:
    static History* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void setWelderID(int welderID = 0);

    Q_INVOKABLE int deviceID() const;
    Q_INVOKABLE void setDeviceID(int newDeviceID);

    Q_INVOKABLE int finalResult() const;
    Q_INVOKABLE void setFinalResult(int newFinalResult);

signals:
    void deviceIDChanged();

    void finalResultChanged();

private:
    explicit History(QObject *parent = nullptr);

private:
    static History* s_pHistory;

    QList<_Production_Data> m_data;

    // 生产历史设备号 零为全部
    int m_deviceID{0};
    // 产品状态 0_全部 1_合格 2_次品 3_可疑
    int m_finalResult{0};;
};

#endif // HISTORY_H
