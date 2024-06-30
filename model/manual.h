#ifndef MANUAL_H
#define MANUAL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The Manual class : manual
///
class Manual : public QAbstractListModel
{
    Q_OBJECT
public:
    static Manual* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getManualDataByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setManualData(int id, _MANUAL_COLUMN column, QVariant data);

private:
    explicit Manual(QObject *parent = nullptr);

private:
    static Manual* s_pManual;

    QList<_Manual_Data> m_data;
};

#endif // MANUAL_H
