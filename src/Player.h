
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

using namespace std;

class Cell;
class Player{
    private:
        int numOfDataDld = 0;
        int numOfVirusDld = 0;
        vector <Cell*> fwCells;
        int playerNumber; // actualy player number, starting from 1
        int unusedAbilities;
    public:
        vector<shared_ptr<Ability>> abilities;
        vector<shared_ptr<Link>> links; 
        Player(std::string abilityOrder, std::string linkOrder, int number);
        ~Player();
        char getFirstId();
        bool hasAbility(string name);
        void setAbilities(string order);
        void setLinks(string order);
        void useAbility(string name);
        int numOfUnusedAbilities() ;
        int getPlayerNum() ;
        int getNumOfData() ;
        int getNumOfVirus() ;
};


#endif