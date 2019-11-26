#include "Game.h"
#include "Cell.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

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
void Game::getIsGraphics(bool boolean_)
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
            string err_st = "Player" + to_string(board[r][c].fireWallOwner + 1) + " already owns a firewall here";
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
}