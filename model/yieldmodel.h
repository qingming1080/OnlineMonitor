#ifndef YIELDMODEL_H
#define YIELDMODEL_H

#include <QAbstractListModel>

///
/// \brief The YieldModel class : 生产模型
///
class YieldModel : public QAbstractListModel
{
    Q_OBJECT
    enum _YIELDMODEL_ROLE{
        isSelect = 0,   // 是否选中
        index,          // 序号
        time,           // 焊接时间
        power,          // 功率
        energy,         // 能量
        date,           // 日期
        pull,           // 拉力
        rest            // 残留度
    };

    struct _YieldModel_Data{
        bool isSelect;      // 是否选中
        int index;          // 序号
        double time;        // 焊接时间
        double power;       // 功率
        double energy;      // 能量
        QString date;       // 日期
        double pull;        // 拉力
        double rest;        // 残留度
    };

public:
    explicit YieldModel();

protected:
    // QML获取列表数量
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    Q_INVOKABLE virtual QHash<int, QByteArray> roleNames() const override;
    // QML设置数据
    Q_INVOKABLE virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
    // QML插入节点
    Q_INVOKABLE void addRow(int row);
    // QML删除节点
    Q_INVOKABLE void removeRow(int row);

private:
    QList<_YieldModel_Data>  m_data;
};

#endif // YIELDMODEL_H
