#ifndef WELDPARAM_H
#define WELDPARAM_H

#include <QObject>

///
/// \brief The WeldParam class : 焊接参数
///
class WeldParam : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double energy    READ energy     WRITE setEnergy     NOTIFY energyChanged)       // 压力
    Q_PROPERTY(double amplitude READ amplitude  WRITE setAmplitude  NOTIFY amplitudeChanged)    // 振幅
    Q_PROPERTY(double pressure  READ pressure   WRITE setPressure   NOTIFY pressureChanged)     // 能量
public:
    explicit WeldParam(QObject *parent = nullptr);

    Q_INVOKABLE double energy() const;
    Q_INVOKABLE void setEnergy(double newEnergy);

    Q_INVOKABLE double amplitude() const;
    Q_INVOKABLE void setAmplitude(double newAmplitude);

    Q_INVOKABLE double pressure() const;
    Q_INVOKABLE void setPressure(double newPressure);

signals:

    void energyChanged();

    void amplitudeChanged();

    void pressureChanged();

private:
    double m_energy;        // 能量
    double m_amplitude;     // 振幅
    double m_pressure;      // 压力

};

#endif // WELDPARAM_H
