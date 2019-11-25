#ifndef ABILITY_H
#define ABILITY_H
#include <string>

enum Abilities {LinkBoost = 'L', Firewall = 'F', Download = 'D', Polarize = 'P', Scan = 'S', Sand = 'N', Portal = 'O', Strengthen = 'R'} ;
struct Ability{
        Abilities name;
        bool isUsed;
        Ability(char code);
        std::string getAbilityName(); 
        void UseAbility();
        
};

#endif