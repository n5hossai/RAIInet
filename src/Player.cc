
 #include "Player.h"
 #include <iostream>
 using namespace std;

Player::Player(string abilityorder, string linkorder, int number): playerNumber{number} {
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
    return links[0]->getId();
}

void Player::setAbilities(string order){
    abilities.clear();
    if(order.size() > 5){
        throw "Invalid Abilities List";
    }
    for (unsigned int i = 0; i<order.size(); i++) {
        abilities.emplace_back(make_shared<Ability>(order[i],i+1));
    }
   //We Shall assume invalid arguments not allowed, I am not checking for >2 Abilities
}

void Player::setLinkLists(string order){
    links.clear();
    if(order.size() > 16){
        throw "Invalid Links List";
    }
    char a = (playerNumber == 1)?'a':'A';
    for (unsigned int i = 0; i<order.size(); i=i+2) {
        shared_ptr<Link> sp = make_shared<Link>((char)(a + i),order[i],order[i+1]-'0');
        links.emplace_back(sp);
        knownLinks.emplace_back(sp);
    }

    // set up row and col numbers for each link
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
    }
}

void Player::useAbility(string name) {
    int index_to_delete;
    for (int i = 0; i < unusedAbilities; ++i) {
        if (abilities[i]->getAbilityName() == name) {
            index_to_delete = i;
            break;
        }
    }
    shared_ptr<Ability> used = abilities[index_to_delete];
    usedAbilities.emplace_back(used);
    abilities.erase(abilities.begin() + index_to_delete);
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
