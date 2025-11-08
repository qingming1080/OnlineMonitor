#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include <QAbstractListModel>
#include <QMap>
// #include "DataBase/databasemanager.h"
///
/// \brief The NetworkModel class : 网络连接
///
class NetworkModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int     EthIndex             READ getEthIndex            WRITE setEthIndex           NOTIFY notifyEthIndexChanged FINAL)
    Q_PROPERTY(int     ConnectTypeId        READ getConnectTypeId       WRITE setConnectTypeId      NOTIFY notifyConnectTypeIdChanged FINAL)
    Q_PROPERTY(QString PortNumber           READ getPortNumber          WRITE setPortNumber         NOTIFY notifyPortNumberChanged FINAL)
    Q_PROPERTY(QString LocalIP              READ getLocalIP             WRITE setLocalIP            NOTIFY notifyLocalIPChanged FINAL)
    Q_PROPERTY(QString RemoteIP             READ getRemoteIP            WRITE setRemoteIP           NOTIFY notifyRemoteIPChanged FINAL)

public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        IdRole,
    };
public:
    static NetworkModel* getInstance();

    // QAbstractItemModel interface
public:
    int getEthIndex() const;
    void setEthIndex(const int &index);

    int getConnectTypeId() const;
    void setConnectTypeId(const int &typeId);

    QString getPortNumber() const;
    void setPortNumber(const QString &port);

    QString getLocalIP() const;
    void setLocalIP(const QString &ip);

    QString getRemoteIP() const;
    void setRemoteIP(const QString &ip);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(const int index) const;
    bool UpdateDatabase();
    bool InitListManager();
    bool UpdateWelderID();
    int GetModbusDeviceID();

private:
    explicit NetworkModel(QObject *parent = nullptr);
    int indexOfEthRole(const int value) const;
    void modelReset();

private:
    static constexpr int ETH1 = 0;
    static constexpr int ETH2 = 1;
    static constexpr int ETH3 = 2;
    static constexpr int ETH4 = 3;
    static constexpr int ETH5 = 4;
    struct NETWORK_MANAGER
    {
        int Type;           // 类型  0_Server  1_Client
        int Protocol;       // 协议  0_TCP/IP  1_OPCUA
        QString LocalIP;    // 本地IP
        int LocalPort;      // 本地端口
        QString RemoteIP;   // 远程IP
        int ServerPort;     // 服务器端口
        QString User;       // 用户
		int WelderId;		// WelderID
		int ModbusDeviceId; // ModbusDeviceID
	};

    static NetworkModel* m_ptrInstance;
    int m_iCurrentWelderId;
    QList<QVariantMap> m_listETHPort; // List of key-value pairs m_listETHPort;
    QMap<int, NETWORK_MANAGER> m_listManager;
    int m_iCurrentEthIndex;
	int m_iConnectTypeId;
    int m_iServerPort;
    QString m_strLocalIP;
    QString m_strRemoteIP;
signals:
    void notifyEthIndexChanged();
    void notifyPortNumberChanged();
    void notifyLocalIPChanged();
    void notifyRemoteIPChanged();
    void notifyConnectTypeIdChanged();

public slots:
    void NotifySelectedDeviceIndexChanged(int welderID);
};
#endif // NETWORKMODEL_H
