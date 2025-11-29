#ifndef WELDERTYPEMODEL_H
#define WELDERTYPEMODEL_H

#include <QAbstractListModel>

class WelderTypeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int WelderTypeIndex    READ getWelderTypeIndex   WRITE setWelderTypeIndex  NOTIFY notifyWelderTypeIndexChanged FINAL)
public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
public:
    static WelderTypeModel* getInstance();
    int getWelderTypeIndex() const;
    void setWelderTypeIndex(const int &index);
    int indexOfValueRole(const int value) const;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    Q_INVOKABLE QVariant get(int index) const;
signals:
    void notifyWelderTypeIndexChanged();

private:
    explicit WelderTypeModel(QObject *parent = nullptr);

private:
    static WelderTypeModel* m_ptrInstance;
    QList<QVariantMap> m_listWelderTypes; // List of key-value pairs m_listWelderTypes;
     int m_iCurrentWelderTypeIndex;
};

#endif // WELDERTYPEMODEL_H
