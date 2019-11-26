#ifndef Ability_H
#define Ability_H

enum AbilityName {LinkBooster, Firewall, Download, Polarize, Scan} ;// add new abilities

class Ability{
    private:
       
    public:
    Ability(char code);
    AbilityName name;
};

#endif