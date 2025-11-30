#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <QMutex>
#define BUZZER_GPIO 12
#define CTR_DO0     17
#define CTR_DO1     18
#define CTR_DO2     22
#define CTR_DO3     23
#define CTR_DO4     24
#define CTR_DO5     25
#define CTR_DO6     26
#define CTR_DO7     27

#define DI0         5
#define DI1         6
#define DI2         4
#define DI3         13

#define LED1        36
#define LED2        37
#define LED3        38
#define LED4        39
#define KEY_RESET   40

class GPIO : public QObject
{
    Q_OBJECT
public:
    enum LEVEL{
        LOW = 0,
        HIGHT
    };

    enum DEVICE_INDEX
    {
        DEV_0 = 0,
        DEV_1,
        DEV_2,
        DEV_3
    };

    enum INPUT
    {
        RESET_IO_0      = DI0,
        RESET_IO_1      = DI1,
        RESET_IO_2      = DI2,
        RESET_IO_3      = DI3,
        RESET_BUTTON    = KEY_RESET
    };

    enum OUTPUT
    {
        BUZZER          = BUZZER_GPIO,
        SUSPECT_IO_0    = CTR_DO0,
        REJECT_IO_0     = CTR_DO1,

        SUSPECT_IO_1    = CTR_DO2,
        REJECT_IO_1     = CTR_DO3,

        SUSPECT_IO_2    = CTR_DO4,
        REJECT_IO_2     = CTR_DO5,

        SUSPECT_IO_3    = CTR_DO6,
        REJECT_IO_3     = CTR_DO7,
        ALARM           = LED1,
        READY           = LED2,
        PILOT_RUN       = LED3,
        LEARNING        = LED4
    };
    static GPIO*   GetInstance();
    int SetSuspect(const int iDev, const int iLevel);
    int SetReject(const int iDev, const int iLevel);
    static int SetPilotRun(const int iLevel);
    static int SetLearning(const int iLevel);
    static int SetReady(const int iLevel);
    static int SetAlarm(const int iLevel);
    static int SetBuzzer(const int iLevel);
    int GetReset(const int iDev) const;
    static int GetResetButton();

private:
    static constexpr int TOTAL_INPUT = 5;
    static constexpr int TOTAL_OUTPUT = 13;
    static unsigned int m_arrayInput[TOTAL_INPUT];
    static unsigned int m_arrayOutput[TOTAL_OUTPUT];

    static GPIO* _gpio;
    static QMutex  m_Mutex;

    bool m_IsBoardAvaiable;

    explicit GPIO(QObject *parent = nullptr);

signals:
};

#endif // GPIO_H
