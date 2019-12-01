#ifndef ABILITY_H
#define ABILITY_H
#include <string>

enum Abilities {LinkBoost = 0, Firewall, Download, Polarize , Scan , Sand , Portal , Strengthen } ;
class Ability{
    private:
    	int ID;
        Abilities name;
        bool isUsed;
    public:
        Ability(char code, int id);
        ~Ability();
        int getAbilityID();
        std::string getAbilityName(); 
        bool getIsUsed();
        void useAbility();
        
};

#endif
