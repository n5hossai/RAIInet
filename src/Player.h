#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

class Player{
    private:
       std::vector<Link> links; 
       std::vector<Ability> abilities; 
       int numOfDataDld;
       int numOfVirusDld;
       std::vector <Cell*> fwCells;
    public:
        Player();
        ~Player();
        void setAbilityOrder(std::string order);
        void setLinkOrder(std::string order);
};

#endif