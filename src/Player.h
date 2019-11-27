
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
        char getFirstId();
        void setAbilities(std::string order);
        void setLinks(std::string order);
        bool hasAbility(std::string name);
        void useAbility(std::string name);
        int numOfUnusedAbilities() ;
        int getPlayerNum() ;
        int getNumOfData() ;
        int getNumOfVirus() ;
};


#endif