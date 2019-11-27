
 #include "Player.h"
 #include <iostream>
 using namespace std;

Player::Player(string abilityorder, string linkorder){
    setAbilities(abilityorder);
    setLinks(linkorder);
}

Player::~Player(){
    std::vector <Cell*> fwCells;
    for(unsigned int i=0; i< fwCells.size(); ++i){
        fwCells[i]->isFireWall = false;
        fwCells[i]->fireWallOwner = 0;
    }
}

char Player::getFirstId() {
    return links[0].getId();
}

void Player::setAbilities(std::string order){
    abilities.clear();
    if(order.size() > 5){
        throw "Invalid Abilities List";
    }
    for (unsigned int i = 0; i<order.size(); i++) {
        Ability newAbility(order[i]);
        abilities.push_back(newAbility);
    }
   //We Shall assume invalid arguments not allowed, I am not checking for >2 Abilities
}

void Player::setLinks(std::string order){
    links.clear();
    if(order.size() > 16){
        throw "Invalid Links List";
    }
    char a = (playerNumber == 1)?'a':'A';
    for (unsigned int i = 0; i<order.size(); i=i+2) {
        Link newLink((char)(a + i),order[i],order[i+1]-'0');
        links.push_back(newLink);
    }

    // set up row and col numbers for each link
    for (int i = 0; i < 8; ++i ) {
        links[i].setCol(i);
        if ((i != 3) && (i != 4)) {
            if (playerNumber == 1) links[i].setRow(0);
            else links[i].setRow(7);
        }
        else {
            if (playerNumber == 1) links[i].setRow(1);
            else links[i].setRow(6);
        }
    }
}

bool Player::hasAbility(std::string name) {
    for (int i = 0; i < unusedAbilities; ++i) {
        if (abilities[i].getAbilityName() == name) {
            return true;
        }
    }
    return false;
}

void Player::useAbility(std::string name) {
    for (int i = 0; i < unusedAbilities; ++i) {
        if (abilities[i].getAbilityName() == name) {
            abilities[i].UseAbility();
            break;
        }
    }
    unusedAbilities -= 1;
}

int Player::numOfUnusedAbilities() {
	return unusedAbilities;
}

int Player::getPlayerNum() {
	return this->playerNumber;
}

int Player::getNumOfData() {
	return this->numOfDataDld;
}

int Player::getNumOfVirus() {
	return this->numOfVirusDld;
}

