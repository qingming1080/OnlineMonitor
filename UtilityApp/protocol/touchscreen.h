#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "common.h"

class TouchScreen : public Common
{
private:
    void ParseResultString2Data(const QString strData);
    void Parse1stString2Data(QString strFirst);
    void Parse2ndString2Data(QString strSecond);
    void Parse3rdString2Data(QString strThird);
    void Parse4thString2Data(QString strFourth);
    void Parse5thString2Data(QString strFifth);
    void Parse6thString2Data(QString strSixth);


public:
    TouchScreen();
    virtual int ParseWeldResult(QString weldResult) override;
};

#endif // TOUCHSCREEN_H
