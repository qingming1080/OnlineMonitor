#ifndef VERSAGRAPHIC_H
#define VERSAGRAPHIC_H

#include "common.h"

class Versagraphic : public Common
{
private:
    void ParseResultString2Data(const QString strData);
public:
    Versagraphic();
    virtual int ParseWeldResult(QString weldResult) override;
};

#endif // VERSAGRAPHIC_H
