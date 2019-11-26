#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

class Player{
    private:
        int playerNumber; 
        std::vector<Ability> abilities;
        int numOfDataDld;
        int numOfVirusDld;
        std::vector <Cell*> fwCells;
    public:
        std::vector<Link> links;
        Player();
        ~Player();
        void setAbilityOrder(std::string order);
        void setLinkOrder(std::string order);
        int numOfUnusedAbilities() const;
        int getPlayerNum() const;
        int getNumOfData() const;
        int getNumOfVirus() const;
};

#endif