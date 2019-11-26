#include "Ability.h"
#include <iostream>
using namespace std;

Ability::Ability(char code){ // use try exception and add new abilities
    if(code == 'L'){
        name = LinkBooster;
    }
    else if(code == 'F'){
        name = Firewall;
    }
    else if(code == 'D'){
        name = Download;
    }
    else if(code == 'P'){
        name = Polarize;
    }
    else if(code == 'S'){
        name = Scan;
    }
    else{
        cerr << "ERROR: Invalid ability attempted to be set"<<endl;
    }
}