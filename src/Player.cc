 #include "Player.h"

Player::Player(){}

Player::~Player(){}

void Player::setAbilityOrder(std::string order){}

void Player::setLinkOrder(std::string order){}

int Player::numOfUnusedAbilities() {
	int unused = 0;
	for (int i = 0; i < 5; ++i) {
		if (!this->abilities[i].isUsed) unused += 1;
	}
	return unused;
}
