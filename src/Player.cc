
 #include "Player.h"
 #include <iostream>
 using namespace std;

Player::Player(string abilityOrder, string linkOrder, int number) :
playerNumber{number} {
    setAbilities(abilityOrder);
    setLinks(linkOrder);
    unusedAbilities = abilities.size();
}

Player::~Player(){
    vector <Cell*> fwCells;
    for(unsigned int i=0; i< fwCells.size(); ++i){
        fwCells[i]->isFireWall = false;
        fwCells[i]->fireWallOwner = 0;
    }
    for (int i = 0; i < 2; ++i) {
        SSCells[i]->isServerPort = false;
        SSCells[i]->whoseServerPort = 0;
    }
}

char Player::getFirstId() {
    return links[0]->getId();
}

void Player::setAbilities(string order){
    abilities.clear();
    if(order.size() > 5){
        throw "Invalid Abilities List";
    }
    for (unsigned int i = 0; i<order.size(); i++) {
        abilities.push_back(make_shared<Ability>(order[i],i+1));
    }
   //We Shall assume invalid arguments not allowed, I am not checking for >2 Abilities
}

void Player::setLinks(string order){
    links.clear();
    if(order.size() > 16){
        throw "Invalid Links List";
    }
    char a = (playerNumber == 1)?'a':'A';
    unsigned int j = 0;
    for (unsigned int i = 0; i<order.size(); i=i+2) {
        links.push_back(make_shared<Link>((char)(a + j),(order[i] == 'V') ? 1 : 0,order[i+1]-'0'));
        ++j;
    }

    // set up row and col numbers and ownedBy for each link
    for (int i = 0; i < 8; ++i ) {
        links[i]->setCol(i);
        if ((i != 3) && (i != 4)) {
            if (playerNumber == 1) links[i]->setRow(0);
            else links[i]->setRow(7);
        }
        else {
            if (playerNumber == 1) links[i]->setRow(1);
            else links[i]->setRow(6);
        }
        links[i]->setOwnedBy(playerNumber);
    }
}

bool Player::hasAbility(string name) {
    for (int i = 0; i < unusedAbilities; ++i) {
        if ((abilities[i]->getAbilityName() == name) && (!abilities[i]->getIsUsed())) {  //if the ability exists in the list and has not been used
            return true;
        }
    }
    return false;
}

void Player::useAbility(int i) {
        abilities[i]->useAbility();
        unusedAbilities -= 1;
}

int Player::numOfUnusedAbilities() {
    return this->unusedAbilities;
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

void Player::dataDownload() {
    numOfDataDld++;
}

void Player::virusDownload() {
    numOfVirusDld++;
}