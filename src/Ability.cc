#include "Ability.h"
#include <iostream>

Ability::Ability(char code, int id) : ID{id} {
    try{
    switch (code)
        {
            case 'L':   
                name = LinkBoost;
                break;
            case 'F':   
                name = Firewall;
                break;
            case 'D':   
                name = Download;
                break;
            case 'P':   
                name = Polarize;
                break;
            case 'S':   
                name = Scan;
                break;
            case 'N':   
                name = Sand;
                break;
            case 'O':   
                name = Portal;
                break;
            case 'R':   
                name = Strengthen;
                break;
            default:    throw(code);
        }
    }catch(char e){
        std::cout << "Invalid Ability";
    }
    // isUsed = false;
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
    
}

// bool Ability::getIsUsed(){
//     return isUsed;
// }
