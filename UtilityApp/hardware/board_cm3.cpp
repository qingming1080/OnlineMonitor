#include "board_cm3.h"
Board_CM3* Board_CM3::_Board = nullptr;

Board_CM3 *Board_CM3::GetInstance()
{
    return (_Board != nullptr) ? _Board : (_Board = new Board_CM3());
}

Board_CM3::~Board_CM3()
{
#ifdef RASPBERRY
    bcm2835_close();
#endif
}

bool Board_CM3::GetBoardStatus() const
{
    return m_IsBoardAvaiable;
}

Board_CM3::Board_CM3(QObject *parent)
    : QObject{parent}
{
#ifdef RASPBERRY
    if(bcm2835_init() == 0)
        m_IsBoardAvaiable = false;
    else
        m_IsBoardAvaiable = true;
#else
    m_IsBoardAvaiable = true;
#endif
}
