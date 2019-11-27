#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

class Cell;
class Player{
    private:
       std::vector<Link> links; 
       
       int numOfDataDld;
       int numOfVirusDld;
       std::vector <Cell*> fwCells;
    public:
        std::vector<Ability> abilities; 
        Player( std::string abilityOrder, std::string linkOrder, int p = 1);
        ~Player();
        void setAbilityOrder(std::string order);
        void setLinkOrder(int p,std::string order);
};

#endif