#include "Inventory.h"

int Inventory::reduceInventory(int inventory){
    if(m_Inventory - inventory >=0){
        m_Inventory = m_Inventory - inventory;
        return 1;
    }
    else
        return -1;
}
