#include "Link.h"
#include <sstream>

Link::Link(char id, int type, int strength):
    id{id}, type{type}, strength{strength} {}

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

int Link::getMoveFactor() const
{
    return this->moveFactor;
}

int Link::getOwnedBy() const
{
    return this->ownedBy;
}

//setters:
void Link::setRow(int row_)
{
    if (getIsDownloaded()) return;
    this->row = row_;
}
void Link::setCol(int col_)
{
    if (getIsDownloaded()) return;
    this->col = col_;
}
void Link::setId(char id_)
{
    if (getIsDownloaded()) return;
    this->id = id_;
}
void Link::setType(int type_)
{
    if (getIsDownloaded()) return;
    this->type = type_;
}
void Link::setStrength(int strength_)
{
    if (getIsDownloaded()) return;
    this->strength = strength_;
}
void Link::setIsLinkBoosted(bool boolean_)
{
    if (getIsDownloaded()) return;
    this->isLinkBoosted = boolean_;
    this->moveFactor++;
}
void Link::setIsVisible(bool boolean_)
{
    if (getIsDownloaded()) return;
    this->isVisible = boolean_;
}
void Link::setIsDownloaded(bool boolean_)
{
    if (getIsDownloaded()) return;
    this->isDownloaded = boolean_;
}

void Link::setOwnedBy(int player_)
{
    if (getIsDownloaded()) return;
    this->ownedBy = player_;
}
// functions:
std::string Link::linkDescription(){
    std::string s = "";
    std::stringstream ss{s};
    s += (this->type) ? "V" : "D";
    ss << this->strength;
    s += ss.str();
    return s;
}
