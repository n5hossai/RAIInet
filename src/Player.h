
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
        int playerNumber;  // actualy player number, starting from 1
    public:
        std::vector<Ability> abilities;
        std::vector<Link> links; 
        Player(std::string abilityOrder, std::string linkOrder);
        ~Player();
        void setAbilities(std::string order);
        void setLinks(std::string order);
        int numOfUnusedAbilities() const;
        int getPlayerNum() const;
        int getNumOfData() const;
        int getNumOfVirus() const;
};


#endif