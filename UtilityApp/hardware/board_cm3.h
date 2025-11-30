#ifndef BOARD_CM3_H
#define BOARD_CM3_H

#include <QObject>
#ifdef RASPBERRY
#include <bcm2835.h>
#endif
class Board_CM3 : public QObject
{
    Q_OBJECT
public:
    static Board_CM3*   GetInstance();
    virtual             ~Board_CM3();
    bool                GetBoardStatus() const;
private:
    explicit            Board_CM3(QObject *parent = nullptr);
private:
    static              Board_CM3* _Board;
    bool                m_IsBoardAvaiable;

signals:

};

#endif // BOARD_CM3_H
