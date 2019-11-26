#include "Link.h"

Link::Link(char id, int type, int strength) {}

Link::~Link() {}
//getters:
int Link::getRow() const
{
    return this->row;
}

int Link::getCol() const 
{
    return this->col;
}

char Link::getId() const 
{
    return this->id;
}

int Link::getType() const 
{
    return this->type;
}

int Link::getStrength() const 
{
    return this->strength;
}

bool Link::getIsLinkBoosted() const 
{
    return this->isLinkBoosted;
}

bool Link::getIsVisible() const 
{
    return this->isVisible;
}

bool Link::getIsDownloaded() const 
{
    return this->isDownloaded;
}

//setters:
void Link::setRow(int row_)
{
    this->row = row_;
}
void Link::setCol(int col_)
{
    this->col = col_;
}
void Link::getId(char id_)
{
    this->id = id_;
}
void Link::getType(int type_)
{
    this->type = type_;
}
void Link::setStrength(int strength_)
{
    this->strength = strength_;
}
void Link::setIsLinkBoosted(bool boolean_)
{
    this->isLinkBoosted = boolean_;
}
void Link::setIsVisible(bool boolean_)
{
    this->isVisible = boolean_;
}
void Link::setIsDownloaded(bool boolean_)
{
    this->isDownloaded = boolean_;
}

std::string linkDescription() {}

void Link::toggleType() {}

void Link::polarize() {}

void Link::scan() {}

void Link::linkBoost() {}

void Link::setStrength(int strength) {}