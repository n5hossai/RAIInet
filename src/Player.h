
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

class Cell;
class Player{
    private:
        int numOfDataDld;
        int numOfVirusDld;
        std::vector <Cell*> fwCells;
        int playerNumber;
    public:
        std::vector<Ability> abilities;
        std::vector<Link> links; 
        Player( std::string abilityOrder, std::string linkOrder, int p = 1);
        ~Player();
        void setAbilityOrder(std::string order);
        void setLinkOrder(int p,std::string order);
        int numOfUnusedAbilities() const;
        int getPlayerNum() const;
        int getNumOfData() const;
        int getNumOfVirus() const;
};


#endif