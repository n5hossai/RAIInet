#include "Cell.h"
using namespace std;

Cell::Cell(int row, int col) : row(row), col(col)
{
    // text = '.';
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

//getters:
// int Cell::getRow() const
// {
//     return this->row;
// }
// int Cell::getCol() const
// {
//     return this->col;
// }
// char Cell::getText() const
// {
//     return this->text;
// }
// bool Cell::getIsServerPort() const
// {
//     return this->isServerPort;
// }
// int Cell::getWhoseServerPort() const
// {
//     return this->whoseServerPort;
// }
// bool Cell::getIsFireWall() const
// {
//     return this->isFireWall;
// }
// int Cell::getFireWallOwner() const
// {
//     return this->fireWallOwner;
// }
// bool Cell::getIsEmpty() const
// {
//     return this->isEmpty;
// }
// bool Cell::getIsEdge() const
// {
//     return this->isEdge;
// }

// //setters:
// void Cell::setText(char text_)
// {
//     this->text = text_;
// }

// void Cell::setIsServerPort(bool boolean_)
// {
//     this->isServerPort = boolean_;
// }
// void Cell::setWhoseServerPort(int whoseServerPort_)
// {
//     this->whoseServerPort = whoseServerPort_;
// }

// void Cell::setRow(int row_)
// {
//     this->row = row_;
// }

// void Cell::setCol(int col_)
// {
//     this->col = col_;
// }

// void Cell::setText(char text_)
// {
//     this->text = text_;
// }

// void Cell::setIsServerPort(bool boolean_)
// {
//     this->isServerPort = boolean_;
// }
// void Cell::setIsFireWall(bool boolean_)
// {
//     this->isFireWall = boolean_;
// }
// void Cell::setFireWallOwner(int fireWallOwner_)
// {
//     this->fireWallOwner = fireWallOwner_;
// }
// void Cell::setIsEmpty(bool boolean_)
// {
//     this->isEmpty = boolean_;
// }
// void Cell::setIsEdge(bool boolean_)
// {
//     this->isEmpty = boolean_;
// }