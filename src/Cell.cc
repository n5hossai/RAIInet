#include "Cell.h"
using namespace std;

Cell::Cell(int row, int col) : row(row), col(col)
{
    
    if ((row == 0)  && ((col == 3) || (col == 4)))
    {
        this->text = 'S';
        this->isServerPort = true;
        this->whoseServerPort = 1; // for player 1
        this->isEmpty = true; // it is always empty, because the links gets downloaded anyway.

        this->isFireWall = false;
    }
    else if ((row == 7)  && ((col == 3) || (col == 4)))
    {
        this->text = 'S';
        this->isServerPort = true;
        this->whoseServerPort = 2; // for player 2
        this->isEmpty = true; // it is always empty, because the links gets downloaded anyway.

        this->isFireWall = false;
    }
    else
    {
        this->text = '.';
        this->isServerPort = false;
        this->whoseServerPort = 0; // NO ONE's serverport
    }

    if ((row == 0) || (row == 7))
    {
        this->isEdge = true;
    }
}
