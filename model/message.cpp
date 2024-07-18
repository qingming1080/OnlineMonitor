#include "message.h"
#include "DataBase/databasemanager.h"

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

QHash<int, QByteArray> Message::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[0] = "messegStr";

    return roles;
}

Message::Message(QObject *parent)
    : QAbstractListModel{parent}
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Message::onUpdate);
    m_timer->start(1000);
}

void Message::onUpdate()
{
    beginResetModel();
    m_data.append(DataBaseManager::getInstance()->getMessage(QDateTime::currentDateTime().addMonths(-1)));
    endResetModel();
}
