#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include "define.h"

///
/// \brief The Model class : model
///
class Model : public QAbstractListModel
{
    Q_OBJECT
public:
    static Model* getInstance();

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getModelDataByWelderID(int welderID, int role) const;
    Q_INVOKABLE void setModelData(int id, _MODEL_COLUMN column, QVariant data);

    Q_INVOKABLE void save();

private:
    explicit Model(QObject *parent = nullptr);

private:
    static Model* s_pModel;

    QList<_Model_Data> m_data;
};

#endif // MODEL_H
