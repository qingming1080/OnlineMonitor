#ifndef TCPIP2___X_H
#define TCPIP2___X_H

#include <QObject>
#include "common.h"

class TcpIp2000x : public Common
{
private:
#pragma pack(push, 1)
    struct BYTE_2000X_PROTOCOL
    {
        unsigned char   DLE;
        unsigned char   STX;
        unsigned short  CNT;
        unsigned short  FUN;
        unsigned int    CycleCount;
        unsigned short  Hour;
        unsigned char   Minute;
        unsigned char   Second;
        unsigned short  Year;
        unsigned char   Month;
        unsigned char   Day;
        unsigned int    ActualWeldTime;
        unsigned int    TotalEnergy;
        unsigned int    ActualDistance;
        unsigned int    ActualWeldCollapse;
        unsigned int    ActualTotalCollapse;
        unsigned int    ActualStartFrequency;
        unsigned int    ActualEndFrequency;
        unsigned int    FrequencyChange;
        unsigned int    FrequencyMinimum;
        unsigned int    FrequencyMaximum;
        unsigned int    ActualVelocity;
        unsigned int    TriggerDistance;
        unsigned int    RejectPartAlarms;
        unsigned int    SuspectPartAlarms;
        unsigned int    NoCycleAlarms;
        unsigned int    OverloadAlarms;
        unsigned int    EquipmentFailureAlarms;
        unsigned int    CycleModifiedAlarms;
        unsigned char   PresetNumber;
        unsigned char   Language;
        unsigned char   Units;
        unsigned char   PresetLimitsChanged;
        unsigned int    NoteAlarms;
        unsigned int    ActualAmplitudeStart;
        unsigned int    ActualAmplitudeEnd;
        unsigned char   WeldMode;
        unsigned char   PowerSupplyControlFlag;
        unsigned short  PeakPower;
        unsigned short  WeldPressure;
        unsigned short  WeldForceMaximum;
        unsigned short  HoldForceMaximum;
        unsigned int    TotalCycleTime;
        // unsigned short  TriggerForce;
        unsigned short  Checksum;
        unsigned char   DLE2;
        unsigned char   ETX;
        unsigned char   END;
    };
#pragma pack(pop)

    enum OVERLOAD_DEFINITION
    {
        TEST_OVERLOAD = 0,
        PRETRIGGER_OVERLOAD,
        SEEK_OVERLOAD,
        POWER_SUPPLY_OVERLOAD,
        CONT_POWER_LIMIT,
        AFTERBURST_OVERLOAD,
        PRE_WELD_SEEK_OVERLOAD,
        POST_WELD_SEEK_OVERLOAD
    };

    enum NO_CYCLE_ALARM_DEFINITION
    {
        UPPER_LIMIT_TIMEOUT = 0,
        UNDEFINED_1,
        TRIGGER_BEFORE_PRETRIGGER,
        TRIGGER_TIMEOUT,
        UNDEFINED_2,
        LLS_ABORT_BEFORE_TRS,
        EXTERNAL_CYCLE_ABORT,
        MISSING_PART_ABORT,
        ABS_BEFORE_TRIGGER,
        AMP_STEP_BEFORE_TRIGGER,
        F_STEP_BEFORE_TRIGGER,
        GROUND_DETECTE_CUTOFF,
    };

    static_assert(sizeof(BYTE_2000X_PROTOCOL) == 125, "BYTE_2000X_PROTOCOL size must be 125 bytes");

    BYTE_2000X_PROTOCOL m_byte2000xProtocol;

    int validateProtocol(const QString strWeldResult);

    int parseProtocol();
public:
    TcpIp2000x();
    virtual int ParseWeldResult(QString weldResult) override;
};

#endif // TCPIP2___X_H
