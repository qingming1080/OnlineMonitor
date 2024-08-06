#ifndef MESSAGE_H
#define MESSAGE_H

#include <QAbstractListModel>
#include "qmlenum.h"

class Message : public QAbstractListModel
{
    Q_OBJECT
    struct Message_Data{
        int welderID;
        QmlEnum::MESSAGE messageType;
        QString time;
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
    Q_INVOKABLE void addMessage(int welderID, QmlEnum::MESSAGE state);
private:
    explicit Message(QObject *parent = nullptr);

private:
    static Message* s_pMessage;

    QList<Message_Data> m_data;
};

#endif // MESSAGE_H
