#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <QAbstractListModel>

///
/// \brief The SystemInformation class : 系统信息
///
class SystemInformation : public QAbstractListModel
{
    Q_OBJECT
    enum SYSTEMINFORMATION_ROLE{
        _Date = 0,      // 日期时间     dateTime
        _Information    // 信息         information
    };
    struct _SystemInformation_Data{
        QString dateTime{};       // 日期时间
        QString information{};    // 信息
        _SystemInformation_Data(QString time, QString outInfor){
            dateTime = time;
            information = outInfor;
        }
    };

public:
    SystemInformation();

    ///
    /// \brief addRow : 添加一行信息
    /// \param time : 日期时间
    /// \param information : 信息
    ///
    void addRow(QDateTime time, QString information);

signals:
    void sigAddRow(QString time, QString information);

protected:
    // QML获取列表数量
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QML获取列表数据
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // QML获取列名
    virtual QHash<int, QByteArray> roleNames() const override;

private:


private:

    QList<_SystemInformation_Data> m_data;
};

#endif // SYSTEMINFORMATION_H
