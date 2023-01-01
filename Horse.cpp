#include "Horse.h"

void Horse::setHorseParam(int horseNo,
                          std::string horseName, int odds, bool didWin){
    m_HorseNo = horseNo;
    m_HorseName = horseName;
    m_Odds = odds;
    m_DidWin = didWin;

}

