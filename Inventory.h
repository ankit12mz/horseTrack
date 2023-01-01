#include <vector>

class Inventory{
    int m_Denomination;
    int m_Inventory;

public:
    Inventory(){}
    Inventory(int denomination, int inventory):
        m_Denomination(denomination), m_Inventory(inventory){}

    inline int getDenomination(){return m_Denomination;}
    inline int getInventory(){return m_Inventory;}

    inline void setInventory(int inventory){ m_Inventory = inventory;}

    int reduceInventory(int inventory);

};
