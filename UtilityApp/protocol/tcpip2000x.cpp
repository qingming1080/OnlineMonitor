#include "tcpip2000x.h"
#include "../utility/utility.h"
#include <QDebug>
int TcpIp2000x::validateProtocol(const QString strWeldResult)
{
    QByteArray byteArray = strWeldResult.toLatin1();

    if (byteArray.size() < static_cast<int>(sizeof(BYTE_2000X_PROTOCOL)))
    {
        qWarning() << "Invalid payload size:" << byteArray.size();
        return -1;
    }

    memcpy(&m_byte2000xProtocol, byteArray.data(), sizeof(BYTE_2000X_PROTOCOL));
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    auto swap16 = [](unsigned short &value) {
        value = static_cast<unsigned short>((value >> 8) | (value << 8));
    };
    auto swap32 = [](unsigned int &value) {
        value = ((value & 0x000000FFU) << 24) |
                ((value & 0x0000FF00U) << 8)  |
                ((value & 0x00FF0000U) >> 8)  |
                ((value & 0xFF000000U) >> 24);
    };

    swap16(m_byte2000xProtocol.CNT);
    swap16(m_byte2000xProtocol.FUN);
    swap32(m_byte2000xProtocol.CycleCount);
    swap16(m_byte2000xProtocol.Hour);
    swap16(m_byte2000xProtocol.Year);
    swap32(m_byte2000xProtocol.ActualWeldTime);
    swap32(m_byte2000xProtocol.TotalEnergy);
    swap32(m_byte2000xProtocol.ActualDistance);
    swap32(m_byte2000xProtocol.ActualWeldCollapse);
    swap32(m_byte2000xProtocol.ActualTotalCollapse);
    swap32(m_byte2000xProtocol.ActualStartFrequency);
    swap32(m_byte2000xProtocol.ActualEndFrequency);
    swap32(m_byte2000xProtocol.FrequencyChange);
    swap32(m_byte2000xProtocol.FrequencyMinimum);
    swap32(m_byte2000xProtocol.FrequencyMaximum);
    swap32(m_byte2000xProtocol.ActualVelocity);
    swap32(m_byte2000xProtocol.TriggerDistance);
    swap32(m_byte2000xProtocol.RejectPartAlarms);
    swap32(m_byte2000xProtocol.SuspectPartAlarms);
    swap32(m_byte2000xProtocol.NoCycleAlarms);
    swap32(m_byte2000xProtocol.OverloadAlarms);
    swap32(m_byte2000xProtocol.EquipmentFailureAlarms);
    swap32(m_byte2000xProtocol.CycleModifiedAlarms);
    swap32(m_byte2000xProtocol.NoteAlarms);
    swap32(m_byte2000xProtocol.ActualAmplitudeStart);
    swap32(m_byte2000xProtocol.ActualAmplitudeEnd);
    swap16(m_byte2000xProtocol.PeakPower);
    swap16(m_byte2000xProtocol.WeldPressure);
    swap16(m_byte2000xProtocol.WeldForceMaximum);
    swap16(m_byte2000xProtocol.HoldForceMaximum);
    swap32(m_byte2000xProtocol.TotalCycleTime);
    swap16(m_byte2000xProtocol.Checksum);
#endif

    return 0;
}

int TcpIp2000x::parseProtocol()
{
    Utility *_Utility = Utility::GetInstance();
    double energyInJoules = m_byte2000xProtocol.TotalEnergy / 10.0; // Assuming TotalEnergy is in deci-Joules
    QString strEnergy = QString::number(energyInJoules, 'f', 1); // Convert to string with 1 decimal place
    double doubleTemp = _Utility->String2FormatedData(Utility::DINEnergy, strEnergy);
    m_stWeldResult.Energy = static_cast<int>(doubleTemp);
    m_stWeldSetting.Energy = static_cast<int>(doubleTemp);

    double amplitudeInMicrons = m_byte2000xProtocol.ActualAmplitudeStart / 1.0; // Assuming ActualAmplitudeStart is in percent
    QString strAmplitude = QString::number(amplitudeInMicrons, 'f', 0); // Convert to string with 0 decimal place
    doubleTemp = _Utility->String2FormatedData(Utility::DINAmplitude, strAmplitude);
    m_stWeldResult.Amplitude = static_cast<int>(doubleTemp);
    m_stWeldSetting.Amplitude = static_cast<int>(doubleTemp);

    double pressureInPSI = m_byte2000xProtocol.WeldPressure / 10.0; // Assuming WeldPressure is in psi
    QString strPressure = QString::number(pressureInPSI, 'f', 1); // Convert to string with 1 decimal place
    doubleTemp = _Utility->String2FormatedData(Utility::DINPressure, strPressure);
    m_stWeldResult.TPressure = static_cast<int>(doubleTemp);
    m_stWeldSetting.TPressure = static_cast<int>(doubleTemp);
    m_stWeldResult.WPressure = static_cast<int>(doubleTemp);
    m_stWeldSetting.WPressure = static_cast<int>(doubleTemp);

    m_stWeldResult.CycleCount = m_byte2000xProtocol.CycleCount;

    double actualDistanceInMicroMeter = m_byte2000xProtocol.ActualDistance * 25.4 / 10000;
    QString strActualDistance = QString::number(actualDistanceInMicroMeter, 'f', 2);
    doubleTemp = _Utility->String2FormatedData(Utility::DINActHgtNoUnit, strActualDistance);
    m_stWeldResult.PostHeight = static_cast<int>(doubleTemp);

    double actualTotalCollapseInMicroMeter = m_byte2000xProtocol.ActualTotalCollapse * 25.4 / 10000;
    QString strActualTotalCollapse = QString::number(actualTotalCollapseInMicroMeter, 'f', 2);
    doubleTemp = _Utility->String2FormatedData(Utility::DINActPreHgtNoUnit, strActualTotalCollapse);
    m_stWeldResult.Preheight = static_cast<int>(doubleTemp);

    double peakPowerInPercent = m_byte2000xProtocol.PeakPower / 10.0; // Assuming PeakPower is in deci-Watts
    QString strPeakPower = QString::number(peakPowerInPercent, 'f', 1);
    doubleTemp = _Utility->String2FormatedData(Utility::DINActPower, strPeakPower);
    m_stWeldResult.Power = static_cast<int>(doubleTemp);

    double actualWeldTimeInSeconds = m_byte2000xProtocol.ActualWeldTime / 1000.0; // Assuming ActualWeldTime is in milliseconds
    QString strActualWeldTime = QString::number(actualWeldTimeInSeconds, 'f', 3);
    doubleTemp = _Utility->String2FormatedData(Utility::DINActTime, strActualWeldTime);
    m_stWeldResult.Time = static_cast<int>(doubleTemp);

    m_stWeldResult.AlarmFlag = 0;
    return 0;
}

TcpIp2000x::TcpIp2000x()
{

}

int TcpIp2000x::ParseWeldResult(QString weldResult)
{
    if(validateProtocol(weldResult) == 0)
    {
        qDebug() << "Received Weld Result Parsed Successfully";
        qDebug()<< "    DLE: " << m_byte2000xProtocol.DLE
                << "    STX: " << m_byte2000xProtocol.STX
                << "    CNT: " << m_byte2000xProtocol.CNT
                << "    FUN: " << m_byte2000xProtocol.FUN;
        qDebug()<< "    CycleCount: " << m_byte2000xProtocol.CycleCount;
        qDebug()<< "    Date&Time: " << m_byte2000xProtocol.Year
                << "/" << m_byte2000xProtocol.Month
                << "/" << m_byte2000xProtocol.Day
                << " " << m_byte2000xProtocol.Hour
                << ":" << m_byte2000xProtocol.Minute
                << ":" << m_byte2000xProtocol.Second;
        qDebug()<< "Actual Result:";
        qDebug()<< "    ActualWeldTime: " << m_byte2000xProtocol.ActualWeldTime
                << "    TotalEnergy: " << m_byte2000xProtocol.TotalEnergy
                << "    ActualDistance: " << m_byte2000xProtocol.ActualDistance
                << "    ActualWeldCollapse: " << m_byte2000xProtocol.ActualWeldCollapse
                << "    ActualTotalCollapse: " << m_byte2000xProtocol.ActualTotalCollapse
                << "    ActualVelocity: " << m_byte2000xProtocol.ActualVelocity
                << "    TriggerDistance: " << m_byte2000xProtocol.TriggerDistance;
        qDebug()<< "    PeakPower: " << m_byte2000xProtocol.PeakPower
                << "    WeldPressure: " << m_byte2000xProtocol.WeldPressure
                << "    WeldForceMaximum: " << m_byte2000xProtocol.WeldForceMaximum
                << "    HoldForceMaximum: " << m_byte2000xProtocol.HoldForceMaximum
                << "    TotalCycleTime: " << m_byte2000xProtocol.TotalCycleTime;
        qDebug()<< "Frequency Information:";
        qDebug()<< "    ActualStartFrequency: " << m_byte2000xProtocol.ActualStartFrequency
                << "    ActualEndFrequency: " << m_byte2000xProtocol.ActualEndFrequency
                << "    FrequencyChange: " << m_byte2000xProtocol.FrequencyChange
                << "    FrequencyMinimum: " << m_byte2000xProtocol.FrequencyMinimum
                << "    FrequencyMaximum: " << m_byte2000xProtocol.FrequencyMaximum;
        qDebug()<< "Alarm:";
        qDebug()<< "    RejectPartAlarms: " << m_byte2000xProtocol.RejectPartAlarms
                << "    SuspectPartAlarms: " << m_byte2000xProtocol.SuspectPartAlarms
                << "    NoCycleAlarms: " << m_byte2000xProtocol.NoCycleAlarms
                << "    OverloadAlarms: " << m_byte2000xProtocol.OverloadAlarms
                << "    EquipmentFailureAlarms: " << m_byte2000xProtocol.EquipmentFailureAlarms
                << "    CycleModifiedAlarms: " << m_byte2000xProtocol.CycleModifiedAlarms
                << "    NoteAlarms: " << m_byte2000xProtocol.NoteAlarms;
        qDebug()<< "PresetNumber: " << m_byte2000xProtocol.PresetNumber
                << "    Language: " << m_byte2000xProtocol.Language
                << "    Units: " << m_byte2000xProtocol.Units
                 << "    PresetLimitsChanged: " << m_byte2000xProtocol.PresetLimitsChanged;
        qDebug()<< "Amplitude:";
        qDebug()<< "    ActualAmplitudeStart: " << m_byte2000xProtocol.ActualAmplitudeStart
                << "    ActualAmplitudeEnd: " << m_byte2000xProtocol.ActualAmplitudeEnd;
        qDebug()<< "WeldMode: " << m_byte2000xProtocol.WeldMode
                << "    PowerSupplyControlFlag: " << m_byte2000xProtocol.PowerSupplyControlFlag;

        qDebug()<< "    Checksum: " << m_byte2000xProtocol.Checksum
                << "    DLE2: " << m_byte2000xProtocol.DLE2
                << "    ETX: " << m_byte2000xProtocol.ETX
                << "    END: " << m_byte2000xProtocol.END;
    }
    else
        return -1;

    int iResult = parseProtocol();

    return iResult;
}
