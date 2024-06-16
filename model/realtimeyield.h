#ifndef REALTIMEYIELD_H
#define REALTIMEYIELD_H

#include <QObject>

///
/// \brief The RealTimeYield class : 实时良率
///
class RealTimeYield : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int passRate     READ passRate   WRITE setPassRate   NOTIFY passRateChanged)     // 实时良率(百分比)
    Q_PROPERTY(int passNum      READ passNum    WRITE setPassNum    NOTIFY passNumChanged)      // 合格
    Q_PROPERTY(int dubiousNum   READ dubiousNum WRITE setDubiousNum NOTIFY dubiousNumChanged)   // 可疑
    Q_PROPERTY(int rejectNum    READ rejectNum  WRITE setRejectNum  NOTIFY rejectNumChanged)    // 次品
    Q_PROPERTY(int sumNum       READ sumNum     WRITE setSumNum     NOTIFY sumNumChanged)       // 总数
public:
    explicit RealTimeYield(QObject *parent = nullptr);

    /// 已暴露属性
    Q_INVOKABLE int passRate() const;
    Q_INVOKABLE void setPassRate(int newPassRate);
    Q_INVOKABLE int passNum() const;
    Q_INVOKABLE void setPassNum(int newPassNum);
    Q_INVOKABLE int dubiousNum() const;
    Q_INVOKABLE void setDubiousNum(int newDubiousNum);
    Q_INVOKABLE int rejectNum() const;
    Q_INVOKABLE void setRejectNum(int newRejectNum);
    Q_INVOKABLE int sumNum() const;
    Q_INVOKABLE void setSumNum(int newSumNum);

signals:


    void passRateChanged();

    void passNumChanged();

    void dubiousNumChanged();

    void rejectNumChanged();

    void sumNumChanged();

private:
    // 实时良率(百分比)
    int m_passRate;
    // 合格
    int m_passNum;
    // 可疑
    int m_dubiousNum;
    // 次品
    int m_rejectNum;
    // 总是
    int m_sumNum;
};

#endif // REALTIMEYIELD_H
