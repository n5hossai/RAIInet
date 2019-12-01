#include "Cell.h"
using namespace std;

Cell::Cell(int row, int col) : row(row), col(col)
{
    if ((row == 0)  && ((col == 3) || (col == 4)))
    {
        this->text = 'S';
        this->isServerPort = true;
        this->whoseServerPort = 1; // for player 1
    }
    else if ((row == 7)  && ((col == 3) || (col == 4)))
    {
        this->text = 'S';
        this->isServerPort = true;
        this->whoseServerPort = 2; // for player 2
    }
    else if (((row == 0) && (col < 3)) || ((row == 1) && (col > 2) && (col < 5)) || ((row == 0) && (col > 4))) 
    {
    	this->text = (char)('a' + col);
    	this->isEmpty = false;
    } 
    else if (((row == 7) && (col < 3)) || ((row == 6) && (col > 2) && (col < 5)) || ((row == 7) && (col > 4)))
    {
    	this->text = (char)('A' + col);
    	this->isEmpty = false;
    }
    else
    {
        this->text = '.';
    }

    if (row == 0)
    {
        this->isEdge = true;
        this->whoseEdge = 1;
    }
    else if (row == 7)
    {
    	this->isEdge = true;
    	this->whoseEdge = 2;
    }
}
