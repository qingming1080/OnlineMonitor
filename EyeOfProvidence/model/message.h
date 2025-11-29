#ifndef MESSAGE_H
#define MESSAGE_H

#include <QAbstractListModel>

class MESSAGE_ENUM : public QObject
{
    Q_OBJECT
public:
    enum MESSAGE_TYPE
    {
        SUSPICIOUS              = 0, // 出现可疑品
        DEFECTIVE               = 1, // 出现次品
        DEVICE_DISCONNECTED     = 2, // 未连接
        YIELD_LOWER_LIMIT       = 3, // 良率下降至下限值
        DEFECTIVE_OFTEN         = 4, // 频繁出现次品
        SUSPICIOUS_OFTEN        = 5, // 频繁出现可疑品
        LEARNING_UPPER_LIMIT    = 6, // 自动学习次数超过上限值
        LEARNING_COMPLETED      = 7, // 自动学习已完成
        MODEL_ESTABLISHED       = 8, // 创建模型已完成
        DEVICE_CONNECTED        = 9, //设备已连接
    };
    Q_ENUM(MESSAGE_TYPE)

public:
    explicit MESSAGE_ENUM(QObject *parent = nullptr){Q_UNUSED(parent)}
};


class Message : public QAbstractListModel
{
    Q_OBJECT
    struct MESSAGE_DATA
    {
        int WelderID;
        MESSAGE_ENUM::MESSAGE_TYPE MessageType;
        QString TimeStamp;
    };

public:
    static Message* getInstance();


    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    ///
    /// \brief addMessage : 添加报警信息
    /// \param welderID : 设备号
    /// \param state : 产品状态
    ///
    Q_INVOKABLE void addMessage(int welderID, MESSAGE_ENUM::MESSAGE_TYPE type);

private:
    explicit Message(QObject *parent = nullptr);

private:
    static Message* s_pMessage;

    QList<MESSAGE_DATA> m_MessageData;
};

#endif // MESSAGE_H
