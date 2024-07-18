#ifndef MESSAGE_H
#define MESSAGE_H

#include <QAbstractListModel>
#include <QTimer>
#include <QDateTime>

class Message : public QAbstractListModel
{
    Q_OBJECT
public:
    static Message* getInstance();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

private:
    explicit Message(QObject *parent = nullptr);

    void onUpdate();

private:
    static Message* s_pMessage;

    QTimer* m_timer;

    QList<QString> m_data;
};

#endif // MESSAGE_H
