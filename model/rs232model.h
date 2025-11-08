#ifndef RS232MODEL_H
#define RS232MODEL_H

#include <QAbstractListModel>

class RS232Model : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int     ComIndex             READ getComIndex            WRITE setComIndex            NOTIFY notifyComIndexChanged FINAL)
    Q_PROPERTY(int     ConnectTypeId        READ getConnectTypeId       WRITE setConnectTypeId       NOTIFY notifyConnectTypeIdChanged FINAL)

    Q_PROPERTY(int     BaudRate            READ getBaudRate            WRITE setBaudRate            NOTIFY notifyBaudRateChanged FINAL)
    Q_PROPERTY(int     DataBits            READ getDataBits            WRITE setDataBits            NOTIFY notifyDataBitsChanged FINAL)
    Q_PROPERTY(int     ParityBits          READ getParityBits          WRITE setParityBits          NOTIFY notifyParityBitsChanged FINAL)
    Q_PROPERTY(int     StopBits            READ getStopBits            WRITE setStopBits            NOTIFY notifyStopBitsChanged FINAL)
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        IdRole
    };
public:
    static RS232Model* getInstance();

    // QAbstractItemModel interface
public:
    int getComIndex() const;
    void setComIndex(const int &index);
    int getConnectTypeId() const;
    void setConnectTypeId(const int &typeId);
    int getBaudRate() const;
    void setBaudRate(const int &baudRate);
    int getDataBits() const;
    void setDataBits(const int &dataBits);
    int getParityBits() const;
    void setParityBits(const int &parityBits);
    int getStopBits() const;
    void setStopBits(const int &stopBits);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(const int index) const;
    bool UpdateDatabase();
    bool InitListManager();
    bool UpdateWelderID();
    int GetModbusDeviceID();

private:
    explicit RS232Model(QObject *parent = nullptr);
    int indexOfComRole(const int value) const;
    void modelReset();

private:
    static constexpr int COM1 = 0;
    static constexpr int COM2 = 1;
	struct RS232_MANAGER
	{
		QString Port;   //
        int BaudRate;   //
        int DataBit;    //
        int ParityBit;  //
        int StopBit;    //
		int WelderId;		// WelderID
		int ModbusDeviceId; // ModbusDeviceID
	};

    static RS232Model* m_ptrInstance;
    int m_iCurrentWelderId;
    QList<QVariantMap> m_listComPort; // List of key-value pairs m_listComPort;
    QMap<int, RS232_MANAGER> m_listManager;
	int m_iCurrentComIndex;
	int m_iConnectTypeId;
	int m_iCurrentBaudRate;
	int m_iCurrentDataBits;
	int m_iCurrentParityBits;
	int m_iCurrentStopBits;
signals:
    void notifyComIndexChanged();
    void notifyConnectTypeIdChanged();
    void notifyBaudRateChanged();
    void notifyDataBitsChanged();
    void notifyParityBitsChanged();
    void notifyStopBitsChanged();

private slots:
    void NotifySelectedDeviceIndexChanged(int welderID);
};
#endif // RS232MODEL_H
