#ifndef RS232MODEL_H
#define RS232MODEL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The RS232Model class : RS232
///
class RS232Model : public QAbstractListModel
{
    Q_OBJECT
public:
    static RS232Model* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getDataByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setRS232Data(int id, int column, QVariant data);

private:
    explicit RS232Model(QObject *parent = nullptr);

private:
    static RS232Model* s_pRS232Model;

    QList<_RS232_Data> m_data;
};

#endif // RS232MODEL_H
