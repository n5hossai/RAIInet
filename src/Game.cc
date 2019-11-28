#include "Game.h"
#include "Cell.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Game::Game(string abilities1, string abilities2, string links1, string links2, bool hasGraphics){
	for (int i = 0; i < boardSize; ++i) {
		vector<Cell> row_i;
		for (int j = 0; j < boardSize; ++j) {
			row_i.emplace_back(Cell(i, j));
		}
		board.emplace_back(row_i);
	}
	Player p1(abilities1,links1,1);
	Player p2(abilities2,links2,2);
	players.clear();
	players.push_back(p1);
	players.push_back(p2);
	setIsGraphics(hasGraphics);
}

Game::~Game(){}

void Game::battle(int op, Link& link1, Link& link2){
    
}

void Game::applyLinkBoost(char id)
{
    if (!players[currPlay - 1].hasAbility("LinkBoost")) return;
    if (players[currPlay - 1].links[id - players[currPlay - 1].getFirstId()].getIsLinkBoosted()) return;
    (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].setIsLinkBoosted(true);
    players[currPlay - 1].useAbility("LinkBoost");
}   

void Game::applyPortal(char id, int r, int c){
    if (!players[currPlay - 1].hasAbility("Portal")) return;
    //...
    players[currPlay - 1].useAbility("Portal");
}

void Game::applyStrengthen(char id)
{
    if (!players[currPlay - 1].hasAbility("Strengthen")) return;
    int tmp_strength = (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].getStrength();
    if (tmp_strength <=3)
    {
        (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].setStrength(tmp_strength + 1);
    }
    players[currPlay - 1].useAbility("Strengthen");
}

int Game::applyFirewall(int r, int c, int p)
{
    if (!players[currPlay - 1].hasAbility("Firewall")) return 0;
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
            board[r][c].fireWallOwner = p; //      to check if the cell is a firewall.
            players[currPlay - 1].useAbility("Firewall");
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return 0;
    }
    return 1;
}

int Game::applySand(int r, int c, int p)
{
    if (!players[currPlay - 1].hasAbility("Sand")) return 0;
    try
    {
        if (!board[r][c].isFireWall)
        {
            string err_st = "There is no firewall to be sanded";
            throw err_st;
        }
        else if ((board[r][c].isFireWall) && (board[r][c].fireWallOwner != p))
        {
            board[r][c].isFireWall = false;
            board[r][c].fireWallOwner = 0;
            players[currPlay - 1].useAbility("Sand");
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return 0;
    }
    return 1;
}

void Game::applyDownload(char id){
    if (!players[currPlay - 1].hasAbility("Download")) return;
    //...
    players[currPlay - 1].useAbility("Download");
}

void Game::applyPolarize(char id)
{
    if (!players[currPlay - 1].hasAbility("Polarize")) return;
    bool tmp= (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].getType();
    (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].setType(!tmp);
    players[currPlay - 1].useAbility("Polarize");
}

void Game::applyScan(char id)
{
    if (!players[currPlay - 1].hasAbility("Scan")) return;
    (players[currPlay - 1]).links[id - players[currPlay - 1].getFirstId()].setIsVisible(true);
    players[currPlay - 1].useAbility("Scan");
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
    if (currPlay == 1) currPlay = 2;
    else currPlay = 1;
}

string Game::getAbilityStatus(){
    string builder;
    for(int i = 0 ; i < 5; i++){
            builder += "["+ to_string(i+1)+"] "+ players[currPlay].abilities[i].getAbilityName() +  (players[currPlay].abilities[i].getIsUsed() ?" USED" : "") + "\n";

    }
    return builder;
}

//override Subject class public methods
int Game::getCurrPlayer() {
	return this->currPlay;
}

vector<Player> Game::getPlayers() {
	return this->players;
}

vector<vector<Cell>> Game::getBoard() {
	return this->board;

} 
