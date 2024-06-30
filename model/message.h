#ifndef MESSAGE_H
#define MESSAGE_H

#include <QAbstractListModel>

class Message : public QAbstractListModel
{
    Q_OBJECT
public:
    static Message* getInstance();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;

    void addMessage(QString message);

private:
    explicit Message(QObject *parent = nullptr);

private:
    static Message* s_pMessage;

    QList<QString> m_data;
};

#endif // MESSAGE_H
