#include <string>
#include <vector>
#include <iostream>

class Horse{
    int m_HorseNo;
    std::string m_HorseName;
    int m_Odds;
    bool m_DidWin;

public:
    Horse(){}
    Horse(int horseNo,std::string horseName, int odds, bool didWin):
        m_HorseNo(horseNo), m_HorseName(horseName), m_Odds(odds), m_DidWin(didWin) {}
    void setHorseParam(int horseNo,std::string horseName, int odds, bool didWin);

    inline int getHorseNo(){return m_HorseNo;}
    inline std::string getHorseName() {return m_HorseName;}
    inline int getHorseOdd() {return m_Odds;}
    inline std::string getDidWinString() { return m_DidWin==0?"lost":"won";}
    inline bool getDidWin(){return m_DidWin;}


    inline void setWinningHorse(bool didWin) {m_DidWin = didWin; }


};




