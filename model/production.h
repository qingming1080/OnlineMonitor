#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QObject>

class Production : public QObject
{
    Q_OBJECT
    /// 2024/04/07  实时良率暴露
    // 实时良率
    Q_PROPERTY(int  goodRate                    READ goodRate            WRITE setGoodRate            NOTIFY goodRateChanged)
    // 合格
    Q_PROPERTY(int  goodCycles                  READ goodCycles          WRITE setGoodCycles          NOTIFY goodCyclesChanged)
    // 可疑
    Q_PROPERTY(int  suspectCycles               READ suspectCycles       WRITE setSuspectCycles       NOTIFY suspectCyclesChanged)
    // 次品
    // Q_PROPERTY(int              notDefinite                 READ notDefinite         WRITE setNotDefinite         NOTIFY notDefiniteChanged)

    /// 2024/04/07  焊接结果暴露
    // 焊接结果:功率
    Q_PROPERTY(int  power                       READ power               WRITE setPower               NOTIFY powerChanged)
    // 焊接结果:时间
    Q_PROPERTY(int  time                        READ time                WRITE setTime                NOTIFY timeChanged)
    // 焊接结果:能量
    Q_PROPERTY(int  energy                      READ energy              WRITE setEnergy              NOTIFY energyChanged)
    // 焊接结果:焊前高度
    Q_PROPERTY(int  heightPre                   READ heightPre           WRITE setHeightPre           NOTIFY heightPreChanged)
    // 焊接结果:焊后高度
    Q_PROPERTY(int  heightPost                  READ heightPost          WRITE setHeightPost          NOTIFY heightPostChanged)
public:
    explicit Production(int welderID = 0, QObject *parent = nullptr);

    Q_INVOKABLE int goodRate() const;
    Q_INVOKABLE void setGoodRate(int newGoodRate);

    Q_INVOKABLE int goodCycles() const;
    Q_INVOKABLE void setGoodCycles(int newGoodCycles);

    Q_INVOKABLE int suspectCycles() const;
    Q_INVOKABLE void setSuspectCycles(int newSuspectCycles);

    Q_INVOKABLE int  power() const;
    Q_INVOKABLE void setPower(int  newPower);

    Q_INVOKABLE int  time() const;
    Q_INVOKABLE void setTime(int  newTime);

    Q_INVOKABLE int  energy() const;
    Q_INVOKABLE void setEnergy(int  newEnergy);

    Q_INVOKABLE int  heightPre() const;
    Q_INVOKABLE void setHeightPre(int  newHeightPre);

    Q_INVOKABLE int  heightPost() const;
    Q_INVOKABLE void setHeightPost(int  newHeightPost);

private:
    int m_WelderID;
    int  m_power{0};
    int  m_time{0};
    int  m_energy{0};
    // int m_heightPre{0};
    // int m_heightPost{0};
    int  m_heightPre{0};
    int  m_heightPost{0};
    int m_goodRate{0};
    int m_goodCycles{0};
    int m_suspectCycles{0};

signals:
    void goodRateChanged();

    void goodCyclesChanged();

    void suspectCyclesChanged();

    void powerChanged();

    void timeChanged();

    void energyChanged();

    void heightPreChanged();

    void heightPostChanged();
};

#endif // PRODUCTION_H
