#include <iostream>
#include <sstream>
#include "Horse.h"
#include "Inventory.h"

using namespace std;

std::vector<Horse *> horseVector;
std::vector<Inventory *> inventoryVector;

void PrintHorseMenu();
void PrintInventoryMenu();
void SetWinnerHorse(int horseNo);
void Restock();
void BetPayout(int horseNo, int betAmount);
int TotalInventoryAmount();
void PrintInvalidCommand(std::string str);
bool isStringNumber(std::string str);
bool DidHorseWon(int horseNo);
std::string getHorseName(int horseNo);
int getHorseOdds(int horseNo);
void ProcessPayout(int payout);
void PrintMenu();
int FindNoOfBills(int denomination, int NoOfBills);

const int INITIAL_INVENTORY = 10;
const int DID_WIN_FALSE = 0;

int main()
{
    horseVector.push_back(new Horse{1,"That Darn Gray Cat",5,DID_WIN_FALSE});
    horseVector.push_back(new Horse{2,"Fort Utopia",10,DID_WIN_FALSE});
    horseVector.push_back(new Horse{3,"Count Sheep",9,DID_WIN_FALSE});
    horseVector.push_back(new Horse{4,"Ms Traitour",4,DID_WIN_FALSE});
    horseVector.push_back(new Horse{5,"Real Princess",3,DID_WIN_FALSE});
    horseVector.push_back(new Horse{6,"Pa Kettle",5,DID_WIN_FALSE});
    horseVector.push_back(new Horse{7,"Gin Stinger",6,DID_WIN_FALSE});
    //Set Horse No 1 as Winning Horse
    SetWinnerHorse(1);


    inventoryVector.push_back(new Inventory{1,INITIAL_INVENTORY});
    inventoryVector.push_back(new Inventory{5,INITIAL_INVENTORY});
    inventoryVector.push_back(new Inventory{10,INITIAL_INVENTORY});
    inventoryVector.push_back(new Inventory{20,INITIAL_INVENTORY});
    inventoryVector.push_back(new Inventory{100,INITIAL_INVENTORY});
    inventoryVector.push_back(new Inventory{500,INITIAL_INVENTORY});




    do{
        PrintMenu();
        std::string inputStr;
        getline(cin,inputStr);
        std::stringstream ss(inputStr);

        std::vector<std::string> inputStringsVector;
        std::string tempStr;
        while(getline(ss,tempStr,' ')){
            inputStringsVector.push_back(tempStr);
        }


        if(inputStringsVector.size() == 1)
        {
            if(inputStringsVector[0].size()==1){
                if(inputStringsVector[0].at(0)=='R' || inputStringsVector[0].at(0)=='r'){
                    Restock();
                }
                else if(inputStringsVector[0].at(0)=='Q' || inputStringsVector[0].at(0)=='q'){
                    break;
                }
                else{
                    PrintInvalidCommand(inputStr);
                }

            }
            else{
                PrintInvalidCommand(inputStr);
            }
        }
        else if(inputStringsVector.size() == 2)
        {
            if(isStringNumber(inputStringsVector[0]) ){
                //if first string is a number, then check for valid horse no
                int HorseNum= stoi(inputStringsVector[0]);
                if(HorseNum >=1 && HorseNum<=7){
                    //check for bet amount: whether it is a string or a number
                    if(isStringNumber((inputStringsVector[1]))){
                        //check bet amount with available funds
                        int betAmount = stoi(inputStringsVector[1]);
                        BetPayout(HorseNum, betAmount);

                    }
                    else{
                        std::cout<<"Invalid Bet: "<<inputStringsVector[1]<<std::endl;
                    }
                }
                else{
                    std::cout<<"Invalid Horse Number: "<<HorseNum<<std::endl;
                }
            }
            else if(inputStringsVector[0].size()==1){
                if(inputStringsVector[0].at(0)=='W' || inputStringsVector[0].at(0)=='w'){
                    if(isStringNumber(inputStringsVector[1])){
                        //if its a no, convert it to int & check horseno
                        int HorseNum = stoi(inputStringsVector[1]);
                        if(HorseNum>=1 && HorseNum<=7){
                            SetWinnerHorse(HorseNum);
                        }
                        else{
                            std::cout<<"Invalid Horse Number: "<<HorseNum<<std::endl;
                        }
                    }
                    else{
                        PrintInvalidCommand(inputStr);
                    }

                }
                else{
                    PrintInvalidCommand(inputStr);
                }
            }
            else{
                PrintInvalidCommand(inputStr);
            }


        }
        else
        {
            PrintInvalidCommand(inputStr);
        }



    }while(1);

    return 0;
}



void PrintHorseMenu(){


    for(auto it:horseVector){
        std::cout<<it->getHorseNo()<<","<<it->getHorseName()<<","
                <<it->getHorseOdd()<<","<<it->getDidWinString()<<std::endl;
    }
}

void PrintInventoryMenu(){
    for(auto it:inventoryVector){
        std::cout<<"$"<<it->getDenomination()<<","<<it->getInventory()<<endl;
    }
}

void SetWinnerHorse(int horseNo){


    for(size_t i=0; i<horseVector.size();i++)
        horseVector[i]->setWinningHorse(false);
    horseVector[horseNo - 1]->setWinningHorse(true);

}

void BetPayout(int horseNo, int betAmount){
    int payout =0;

    if(DidHorseWon(horseNo)){
        payout = betAmount * getHorseOdds(horseNo);
        //If horse won, check for fund sufficiency
        if(payout<=TotalInventoryAmount()){
            std::cout<<"Payout: "<<getHorseName(horseNo)<<",$"<<payout<<std::endl;
            std::cout<<"Dispensing:"<<std::endl;
            // Process Payout
            ProcessPayout(payout);
        }
        else{
            std::cout<<"Insufficient Funds: "<<payout<<std::endl;
        }
    }
    else {
        std::cout<<"No Payout: "<<getHorseName(horseNo)<<std::endl;
    }


}

void ProcessPayout(int payout){
    int tempPayout = payout;
    std::vector<std::string> payoutString;

    for(int i= (int)(inventoryVector.size()-1); i>=0;i--){
        int denomination = inventoryVector[i]->getDenomination();

        int bills = tempPayout/denomination;

        int noOfBills = FindNoOfBills(denomination,bills);
        std::string tempStr = "$"+ to_string(denomination)+","+ to_string(noOfBills);

        payoutString.push_back(tempStr);
        tempPayout  = (tempPayout - (noOfBills)*(denomination));

    }



    for(int i = (int)(payoutString.size() - 1); i>=0; i--)
    {
        std::cout<<payoutString[i]<<std::endl;
    }

}

int FindNoOfBills(int denomination, int NoOfBills){

    for(int i=0;i<(int)inventoryVector.size();i++)
    {
        if(inventoryVector[i]->getDenomination() == denomination){
            int availableAmount = inventoryVector[i]->getInventory();
            if( availableAmount <=0){
                return 0;
            }
            else if(availableAmount >= NoOfBills){
                inventoryVector[i]->reduceInventory(NoOfBills);
                return NoOfBills;
            }
            else if(availableAmount <= NoOfBills){
                inventoryVector[i]->reduceInventory(availableAmount);
                return availableAmount;
            }
        }
    }

    return 0;
}


void Restock(){
    for(auto it:inventoryVector){
        it->setInventory(10);
    }
}

int TotalInventoryAmount(){
    int totalAmount =0;
    for(auto it:inventoryVector){
        totalAmount += (it->getDenomination()) * (it->getInventory()) ;
    }
    return totalAmount;
}


bool DidHorseWon(int horseNo){

    for(auto it:horseVector){
        if(it->getHorseNo()==horseNo)
        {
            if(it->getDidWin())
                return true;
        }
    }
    return false;
}

int getHorseOdds(int horseNo){
    for(auto it:horseVector){
        if(it->getHorseNo()==horseNo)
        {
            return it->getHorseOdd();
        }
    }
    return -1;
}

std::string getHorseName(int horseNo){
    for(auto it:horseVector){
        if(it->getHorseNo()==horseNo)
        {
            return it->getHorseName();
        }
    }
    return "";
}



void PrintInvalidCommand(std::string str){
    std::cout<<"Invalid Command: "<<str<<endl;
}

bool isStringNumber(std::string str){
    for(auto c:str){
        if(isdigit(c)==0)
            return false;
    }
    return true;
}

void PrintMenu(){
    std::cout<<"Inventory:"<<std::endl;
    PrintInventoryMenu();
    std::cout<<"Horses:"<<std::endl;
    PrintHorseMenu();
}
