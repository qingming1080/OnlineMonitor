#include "message.h"


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

    return m_data.at(index.row());
}

void Message::addMessage(QString message)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back(message);
}

Message::Message(QObject *parent)
    : QAbstractListModel{parent}
{

}
