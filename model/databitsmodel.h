#ifndef DATABITSMODEL_H
#define DATABITSMODEL_H

#include <QAbstractListModel>

class DataBitsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int DataBitsIndex READ getDataBitsIndex  WRITE setDataBitsIndex NOTIFY notifyDataBitsIndexChanged FINAL)
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static DataBitsModel* getInstance();
    int getDataBitsIndex() const;
    void setDataBitsIndex(const int &index);
    int indexOfValueRole(const int value) const;
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;
signals:
    void notifyDataBitsIndexChanged();
private:
    explicit DataBitsModel(QObject *parent = nullptr);

private:
    static DataBitsModel* m_ptrInstance;
    QList<QVariantMap> m_listDataBits; // List of key-value pairs m_listDataBits;
    int m_iCurrentDataBitsIndex;
};

#endif // DATABITSMODEL_H
