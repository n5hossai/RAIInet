#include "Ability.h"
#include <iostream>

Ability::Ability(char code, int id) : ID{id} {
    try{
    switch (code)
        {
            case 'L':   
                name = Abilities::LinkBoost;
                break;
            case 'F':   
                name = Abilities::Firewall;
                break;
            case 'D':   
                name = Abilities::Download;
                break;
            case 'P':   
                name = Abilities::Polarize;
                break;
            case 'S':   
                name = Abilities::Scan;
                break;
            case 'N':   
                name = Abilities::Sand;
                break;
            case 'O':   
                name = Abilities::Portal;
                break;
            case 'R':   
                name = Abilities::Strengthen;
                break;
            default:    throw(code);
        }
    }catch(char e){
        std::cout << "Invalid Ability";
    }
    isUsed = false;
}

Ability::~Ability(){

}

int Ability::getAbilityID() {
    return this->ID;
}

std::string Ability::getAbilityName(){
    
        switch (name)
        {
            case LinkBoost:   return "LinkBoost";
            case Firewall:   return "Firewall";
            case Download: return "Download";
            case Polarize:   return "Polarize";
            case Scan: return "Scan";
            case Sand:   return "Sand";
            case Portal: return "Portal";
            case Strengthen: return "Strengthen";
        }
        return "";
    
}

bool Ability::getIsUsed(){
    return isUsed;
}

void Ability::useAbility(){
	if (isUsed) throw "cannot use this ability";
	else isUsed = !isUsed;
}
