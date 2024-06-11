#ifndef WELDRESULTS_H
#define WELDRESULTS_H

#include <QObject>

///
/// \brief The WeldResults class : 焊接结果
///
class WeldResults : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double power        READ power      WRITE setPower      NOTIFY powerChanged)        // 功率
    Q_PROPERTY(double time         READ time       WRITE setTime       NOTIFY timeChanged)         // 时间
    Q_PROPERTY(double energy       READ energy     WRITE setEnergy     NOTIFY energyChanged)       // 能量
    Q_PROPERTY(double heightPre    READ heightPre  WRITE setHeightPre  NOTIFY heightPreChanged)    // 焊前高度
    Q_PROPERTY(double heightPost   READ heightPost WRITE setHeightPost NOTIFY heightPostChanged)   // 焊后高度
public:
    explicit WeldResults(QObject *parent = nullptr);

    /// 已暴露属性
    Q_INVOKABLE double power() const;
    Q_INVOKABLE void setPower(double newPower);
    Q_INVOKABLE double time() const;
    Q_INVOKABLE void setTime(double newTime);
    Q_INVOKABLE double energy() const;
    Q_INVOKABLE void setEnergy(double newEnergy);
    Q_INVOKABLE double heightPre() const;
    Q_INVOKABLE void setHeightPre(double newHeightPre);
    Q_INVOKABLE double heightPost() const;
    Q_INVOKABLE void setHeightPost(double newHeightPost);

signals:

    void powerChanged();
    void timeChanged();
    void energyChanged();
    void heightPreChanged();
    void heightPostChanged();

private:
    // 功率
    double m_power;
    // 时间
    double m_time;
    // 能量
    double m_energy;
    // 焊前高度
    double m_heightPre;
    // 焊后高度
    double m_heightPost;
};

#endif // WELDRESULTS_H
