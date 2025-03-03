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
    return m_data.size();
}

QVariant Message::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == 0)
        return m_data.at(index.row()).welderID;
    else if(role == 1)
        return m_data.at(index.row()).messageType;
    else if(role == 2)
        return m_data.at(index.row()).time;

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

// void Message::addMessage(int welderID, QmlEnum::MESSAGE state)
// {
//     beginInsertRows(QModelIndex(), rowCount(), rowCount());
//     Message_Data data{welderID, state, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")};
//     m_data.push_back(data);
//     endInsertRows();

//     // 只保留三十条信息，删除多余短暂消息
//     for(int i = 0; i < m_data.size() && m_data.size() >= 30; ++i)
//     {
//         if(m_data.at(i).messageType == QmlEnum::MESSAGE_suspicious
//             || m_data.at(i).messageType == QmlEnum::MESSAGE_defective
//             || m_data.at(i).messageType == QmlEnum::MESSAGE_studyOver
//             || m_data.at(i).messageType == QmlEnum::MESSAGE_touchSuccess)
//         {
//             beginRemoveRows(QModelIndex(), i, i);
//             m_data.removeAt(i);
//             endRemoveRows();
//             i--;
//         }
//     }
// }

void Message::addMessage(int welderID, QmlEnum::MESSAGE state)
{
    beginInsertRows(QModelIndex(), 0, 0);  // 插入新行到第一行
    Message_Data data{welderID, state, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")};
    m_data.insert(0, data);  // 插入到 m_data 的开头
    endInsertRows();

    // 只保留三十条信息，删除多余短暂消息
    for(int i = 0; i < m_data.size() && m_data.size() > 30; ++i)
    {
        if(m_data.at(i).messageType == QmlEnum::MESSAGE_suspicious
            || m_data.at(i).messageType == QmlEnum::MESSAGE_defective
            || m_data.at(i).messageType == QmlEnum::MESSAGE_studyOver
            || m_data.at(i).messageType == QmlEnum::MESSAGE_touchSuccess)
        {
            beginRemoveRows(QModelIndex(), i, i);
            m_data.removeAt(i);
            endRemoveRows();
            i--;  // 删除一条记录后，需要调整索引
        }
    }
}


Message::Message(QObject *parent)
    : QAbstractListModel{parent}
{
    addMessage(1,QmlEnum::MESSAGE_suspicious);
    addMessage(1,QmlEnum::MESSAGE_suspicious);
    addMessage(1,QmlEnum::MESSAGE_suspicious);
}
