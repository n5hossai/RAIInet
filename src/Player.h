
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include "Ability.h"
#include "Link.h"
#include "Cell.h"

using namespace std;

struct Cell;
class Player{
    private:
        int numOfDataDld = 0;
        int numOfVirusDld = 0;
        int playerNumber; // actualy player number, starting from 1
        int unusedAbilities;
    public:
        vector <Cell*> fwCells;
        vector <Cell*> SSCells;
        vector<shared_ptr<Ability>> abilities;
        vector<shared_ptr<Link>> links;
        vector<shared_ptr<Link>> downloaded;
        Player(std::string abilityOrder, std::string linkOrder, int number);
        ~Player();
        char getFirstId();
        bool hasAbility(string name);
        void setAbilities(string order);
        void setLinks(string order);
        void useAbility(int i);
        int numOfUnusedAbilities() ;
        int getPlayerNum() ;
        int getNumOfData() ;
        int getNumOfVirus() ;
        void dataDownload() ;
        void virusDownload() ;
};


#endif