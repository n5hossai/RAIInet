#include "Link.h"
#include <sstream>

Link::Link(char id, int type, int strength){}

Link::~Link(){}

int Link::getRow(){}

int Link::getCol(){}

char Link::getId(){}

int Link::getType(){}

int Link::getStrength(){}

bool Link::getIsLinkBoosted(){}

bool Link::getIsVisible(){
	return this->isVisible;
}

bool Link::getIsDownloaded(){}

std::string Link::linkDescription(){
	std::string s = "";
	std::istringstream ss{s};
	s += (this->type) ? "V" : "D";
	ss >> this->strength;
	s += ss;
	return s;
}

void Link::toggleType(){
	this->type = !this->type;
}

void Link::polarize(){
	this->toggleType();
}

void Link::scan(){
	this->isVisible = true;
}

void Link::linkBoost(){
	this->isLinkBoosted = true;
}

void Link::strengthen(){
	this->strength += 1;
}