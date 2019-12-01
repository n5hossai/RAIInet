#include "Game.h"
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game(vector<string> abilities, vector<string> links, bool hasGraphics, int numOfPlayers, int initPlayer){
    this->numOfPlayers = numOfPlayers;
    this->currPlayer = initPlayer;
    this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;

    for (int i = 0; i < boardSize; ++i) {
        vector<Cell> row_i;
        for (int j = 0; j < boardSize; ++j) {
            row_i.emplace_back(Cell(i, j));
        }
        board.emplace_back(row_i);
    }
    for (int i = 0; i < numOfPlayers; ++i) {
        players.push_back(make_shared<Player>(abilities[i], links[i], i+1));
    }
    setIsGraphics(hasGraphics);
}

Game::~Game(){}

void Game::battle(int op, Link& link1, Link& link2){
    
}

//TODO:check if ability is available FOR ALL ABILITIES
//TODO:check if meets the condition of using abilities
void Game::applyLinkBoost(char id)
{   
    if (!players[currPlayer - 1]->hasAbility("LinkBoost")) return;
    if (players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsLinkBoosted()) return;
    players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsLinkBoosted(true);
    players[currPlayer - 1]->useAbility("LinkBoost");
    this->notifyObservers();
}

void Game::applyPortal(char id, int r, int c){
    if (!players[currPlayer - 1]->hasAbility("Portal")) return;
    //...
    players[currPlayer - 1]->useAbility("Portal");
}

void Game::applyStrengthen(char id)
{
    if (!players[currPlayer - 1]->hasAbility("Strengthen")) return;
    int tmp_strength = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getStrength();
    if (tmp_strength <=3)
    {
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setStrength(tmp_strength + 1);
        players[currPlayer - 1]->useAbility("Strengthen");
    }
    this->notifyObservers();
}

void Game::applyFirewall(int r, int c)
{
    if (!players[currPlayer - 1]->hasAbility("Firewall")) return;
    try
    {
        if (((r == 0) || (r == 7)) && ((c == 3) || (c == 4)))
        {
            string err_st = "Cannot apply Firewall on top of Server Port";
            throw err_st;
        }
        else if (board[r][c].isFireWall)
        {

            string err_st = "Player" + to_string(board[r][c].fireWallOwner) + " already owns a firewall here";

            throw err_st;
        }
        else if ((!board[r][c].isFireWall) && (!board[r][c].isEmpty))
        {
            string err_st = "Place firewall on an empty cell";
            throw err_st;
        }
        else if ((!board[r][c].isFireWall) && (board[r][c].isEmpty))
        {
            board[r][c].isFireWall = true; //NOTE: i did not change the text as that would be handled in textdisplay
            board[r][c].fireWallOwner = currPlayer; //      to check if the cell is a firewall.
            players[currPlayer - 1]->useAbility("Firewall");
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return;
    }
    this->notifyObservers();
}

void Game::applySand(int r, int c)
{
    if (!players[currPlayer - 1]->hasAbility("Sand")) return;
    try
    {
        if (!board[r][c].isFireWall)
        {
            string err_st = "There is no firewall to be sanded";
            throw err_st;
        }
        else if ((board[r][c].isFireWall) && (board[r][c].fireWallOwner != currPlayer))
        {
            board[r][c].isFireWall = false;
            board[r][c].fireWallOwner = 0;
            players[currPlayer - 1]->useAbility("Sand");
        }
        else throw "you cannot sand your own firewall";
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return;
    }
    this->notifyObservers();
}

void Game::applyDownload(char id){
    if (!players[currPlayer - 1]->hasAbility("Download")) return;
    //...
    players[currPlayer - 1]->useAbility("Download");
}

void Game::applyPolarize(char id)
{
    if (!players[currPlayer - 1]->hasAbility("Polarize")) return;
    if ((id >= 'a') && (id <= 'h'))
    {
        bool tmp= players[0]->links[id - 'a']->getType();
        players[0]->links[id - 'a']->setType(!tmp);
    }
    else if ((id >= 'A') && (id <= 'H'))
    {
        bool tmp= players[1]->links[id - 'A']->getType();
        players[1]->links[id - 'A']->setType(!tmp);
    }
    players[currPlayer - 1]->useAbility("Polarize");
    this->notifyObservers();
}

void Game::applyScan(char id)
{   
    if (!players[currPlayer - 1]->hasAbility("Scan")) return;
    if ((id >= 'a') && (id <= 'h'))
    {
        if(players[0]->links[id - 'a']->getIsVisible()) return;
        players[0]->links[id - 'a']->setIsVisible(true);
    }

    else if ((id >= 'A') && (id <= 'H'))
    {
        if(players[1]->links[id - 'A']->getIsVisible()) return;
        players[1]->links[id - 'A']->setIsVisible(true);
    };
    players[currPlayer - 1]->useAbility("Scan");
    this->notifyObservers();
}

void Game::move(char id, string direction){
}

//getters
int Game::getBoardSize() const
{
    return this->boardSize;
}
bool Game::getIsGraphics() const
{
    return this->isGraphics;
}

//setters
void Game::setBoardSize(int size)
{
    this->boardSize = size;
}

void Game::setIsGraphics(bool boolean_)
{
    this->isGraphics = boolean_;
}

void Game::togglePlayer(){
    if (currPlayer == 1) currPlayer = 2;
    else currPlayer = 1;
    this->notifyObservers();
}

string Game::getAbilityStatus(){
    string builder;
    for(int i = 0 ; i < 5; i++){
            stringstream ss;
            ss << i+1;
            builder += "["+ ss.str()+"] ";
            builder += players[currPlayer - 1]->abilities[i]->getAbilityName();
            builder += (players[currPlayer - 1]->abilities[i]->getIsUsed()) ?" USED" : "";
            builder += "\n";
    }
    return builder;
}

//override Subject class public methods
int Game::getCurrPlayer() {
	return this->currPlayer;
}

vector<shared_ptr<Player>> Game::getPlayers() {
	return this->players;
}

vector<vector<Cell>> Game::getBoard() {
	return this->board;

} 
