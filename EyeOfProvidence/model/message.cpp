#include "message.h"
#include <QDateTime>

Message* Message::s_pMessage = nullptr;

Message *Message::getInstance()
{
    if(s_pMessage == nullptr)
        s_pMessage = new Message();

    return s_pMessage;
}

int Message::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_MessageData.size();
}

QVariant Message::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == 0)
        return m_MessageData.at(index.row()).WelderID;
    else if(role == 1)
        return m_MessageData.at(index.row()).MessageType;
    else if(role == 2)
        return m_MessageData.at(index.row()).TimeStamp;

    return QVariant();
}

QHash<int, QByteArray> Message::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[0] = "welderID";
    roles[1] = "messageType";
    roles[2] = "time";

    return roles;
}

void Message::addMessage(int welderID, MESSAGE_ENUM::MESSAGE_TYPE type)
{
    beginInsertRows(QModelIndex(), 0, 0);  // 插入新行到第一行
    MESSAGE_DATA data{welderID, type, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")};
    m_MessageData.prepend(data);  // 插入到 m_data 的开头
    endInsertRows();

    while(m_MessageData.size() > 30)
    {
        int lastIndex = m_MessageData.size() - 1;
        beginRemoveRows(QModelIndex(), lastIndex, lastIndex);
        m_MessageData.pop_back();
        endRemoveRows();
    }
}

void Message::clearMessages()
{
    if (m_MessageData.isEmpty())
        return;

    beginRemoveRows(QModelIndex(), 0, m_MessageData.size() - 1);
    m_MessageData.clear();
    endRemoveRows();
}

Message::Message(QObject *parent)
    : QAbstractListModel{parent}
{
}
