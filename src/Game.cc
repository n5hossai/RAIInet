#include "Game.h"
#include "Cell.h"

#include "Player.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

Game::Game(std::string abilities1, std::string abilities2, std::string links1, std::string links2, bool hasGraphics){
Player p1(abilities1,links1,1);
Player p2(abilities2,links2,2);
players.clear();
players.push_back(p1);
players.push_back(p2);
setIsGraphics(hasGraphics);
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

void Game::setIsGraphics(bool boolean_)

{
    this->isGraphics = boolean_;
}

int Game::applyFirewall(int r, int c, int p)
{
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
            return 1;
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return 0;
    }
}

int Game::applySand(int r, int c, int p)
{
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
            return 1;
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return 0;
    }
}


void Game::applyPolarize(char id)
{

    if ((id >= 'a') && (id <= 'h'))
    {
        bool tmp= (players[0]).links[id - 'a'].getType();
        (players[0]).links[id - 'a'].setType(!tmp);
    }
    else if ((id >= 'A') && (id <= 'H'))
    {
        bool tmp= (players[1]).links[id - 'A'].getType();
        (players[1]).links[id - 'A'].setType(!tmp);
    }
}

void Game::applyScan(char id)
{
    if ((id >= 'a') && (id <= 'h'))
    {
        (players[0]).links[id - 'a'].setIsVisible(true);
    }

    else if ((id >= 'A') && (id <= 'H'))
    {
        (players[1]).links[id - 'A'].setIsVisible(true);
    }

}

void Game::applyStrengthen(char id)
{
    if ((id >= 'a') && (id <= 'h'))
    {
        int tmp_strength = (players[0]).links[id - 'a'].getStrength();
        if (tmp_strength <=3)
        {
            (players[0]).links[id - 'a'].setStrength(tmp_strength + 1);
        }
        
    }

    else if ((id >= 'A') && (id <= 'H'))
    {
         int tmp_strength = (players[1]).links[id - 'A'].getStrength();
        if (tmp_strength <=3)
        {
            (players[1]).links[id - 'A'].setStrength(tmp_strength + 1);
        }
    }
}


void Game::applyLinkBoost(char id)
{
    if ((id >= 'a') && (id <= 'h'))
    {
        (players[0]).links[id - 'a'].setIsLinkBoosted(true);
    }

    else if ((id >= 'A') && (id <= 'H'))
    {
        (players[1]).links[id - 'A'].setIsLinkBoosted(true);
    }

string Game::getAbilityStatus(){
    string builder;
    for(int i = 0 ; i < 5; i++){
            builder += "["+ to_string(i+1)+"] "+ players[currPlay].abilities[i].getAbilityName() +  (players[currPlay].abilities[i].getIsUsed() ?" USED" : "") + "\n";

    }
    return builder;
}

int Game::getCurrPlayer() {
	return this->currPlay;
}

std::vector<Player> Game::getPlayers() {
	return this->players;
}

std::vector<std::vector<Cell>> Game::getBoard() {
	return this->board;

}