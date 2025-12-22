#ifndef COMMON_H
#define COMMON_H
#include <QString>
#include <QMap>
#include <QVector>
class Common
{
public:
    enum DEVICE_PROTOCOL_TYPE
    {
        VG_TCP = 0,
        TC_RS232,
        DP2000X_TCP,
        DP2000X_RS232
    };

    struct QUAL_WINDOW
    {
        int Min;
        int Max;
    };
    struct WELD_SETTING
    {
        union {
            struct
            {
                unsigned short WeldMode:    4;  // 0 = Energy, 1 = Time, 2 = Height, 3 = Height with Energy Comp
                unsigned short Unused:      9;
                unsigned short FlagPStep:   1;  // Flag for Power Stepping
                unsigned short FlagTStep:   1;  // Flag for Time Stepping
                unsigned short FlagEStep:   1;  // Flag for Energy Stepping
            } ModeFlags;
            unsigned short ModeWord;
        } MODE_FLAGS;
        unsigned short Energy;                  // Energy in Joules
        unsigned short Width;                   // Width in mm/100
        unsigned short WPressure;               // Pressure in PSI
        unsigned short TPressure;               // Pressure in PSI
        unsigned short Amplitude;               // Amplitude in microns
        QUAL_WINDOW Time;
        QUAL_WINDOW Power;
        QUAL_WINDOW Preheight;
        QUAL_WINDOW PostHeight;
        unsigned short ABDelay;
        unsigned short ABDuration;
        QString PresetName;
    };

    struct WELD_RESULT
    {
        int CycleCount;    // Preset Count;
        int Energy;         // Energy in Joules
        int Width;          // Width in 1/100mm's
        int Time;           // Time in 5 millisecond counts
        int Power;          // Peak Power in Watts
        int Preheight;      // Last Preheight that sonics fired
        int Amplitude;      // Amplitude in microns
        int PostHeight;     // Height after weld - Post Height in 1/100mm's
        int Amplitude2;     // Value of Amp 2 received from controller
        int PPHeight;       // Pre-height before sonics fired
        int WPressure;      // Weld Pressure, Uses Transducer if IN
        int TPressure;      // Weld Trigger Pressure
        int AlarmFlag;      // To Store Error
        QVector<int> PowerGraph;       //
        QVector<int> HeightGraph;
    };

    enum ALARM_FAULT_BITS
    {
        NONE_FAULT     = 0,
        OVERLOAD_FAULT = 0x01,
        TIME_FAULT = 0x02,
        POWER_FAULT = 0x04,
        HEIGHT_FAULT = 0x08,

        TIME_MIN_FAULT = 0x10,
        POWER_MIN_FAULT = 0x20,
        HEIGHT_MIN_FAULT = 0x40,

        TIME_MAX_FAULT = 0x100,
        POWER_MAX_FAULT = 0x200,
        HEIGHT_MAX_FAULT = 0x400
    };

    enum WELD_MODE
    {
        ENERGY_MODE = 0,
        TIME_MODE,
        HEIGHT_MODE,
        ENERGY_WITH_HEIGHT_MODE
    };

protected:
    WELD_RESULT     m_stWeldResult;
    WELD_SETTING    m_stWeldSetting;
    QMap<int, int> m_mapQuality;
    QMap<int, int> m_mapWeldData;
    static constexpr char NONE_ALARM[2]         = "-"; //NO ALARM
    static constexpr char OVERLOAD_ALARM[2]     = "O"; //Overlaod Alarm
    static constexpr char TIME_ALARM[2]         = "T"; //Time limit Alarm
    static constexpr char POWER_ALARM[2]        = "P"; //Power limit Alarm
    static constexpr char HEIGHT_ALARM[2]       = "H"; //Height limit Alarm
public:
    Common();
    virtual ~Common();
public:
    virtual int ParseWeldResult(QString weldResult) = 0;
    int SetWeldSetting(const Common::WELD_SETTING* _setting);
    void GetWeldSetting(Common::WELD_SETTING* _setting) const;
    void GetWeldResult(Common::WELD_RESULT* _result) const;
};

#endif // COMMON_H
