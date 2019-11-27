 #include "Player.h"
 #include <iostream>
 using namespace std;

Player::Player(string abilityorder, string linkorder,int p){
    setAbilityOrder(abilityorder);
    setLinkOrder(p,linkorder);
}

Player::~Player(){
    std::vector <Cell*> fwCells;
    for(int i=0; i< fwCells.size(); ++i){
        fwCells[i]->isFireWall = false;
        fwCells[i]->fireWallOwner = 0;
        delete fwCells[i];
    }
}

void Player::setAbilityOrder(std::string order){
    abilities.clear();
    if(order.size() > 5){
        throw "Invalid Abilities List";
    }
    for (int i = 0; i<order.size(); i++) {
        Ability newAbility(order[i]);
        abilities.push_back(newAbility);
    }
   //We Shall assume invalid arguments not allowed, I am not checking for >2 Abilities
}

void Player::setLinkOrder(int p,std::string order){
    links.clear();
    if(order.size() > 16){
        throw "Invalid Links List";
    }
    char a = p == 1?'a':'A';
    for (int i = 0; i<order.size(); i=i+2) {
        Link newLink((char)(a + i),order[i],order[i+1]-'0');
        links.push_back(newLink);
    }
}

