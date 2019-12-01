#ifndef ABILITY_H
#define ABILITY_H
#include <string>

enum Abilities {LinkBoost = 'L', Firewall = 'F', Download = 'D', Polarize = 'P', Scan = 'S', Sand = 'N', Portal = 'O', Strengthen = 'R'} ;
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
