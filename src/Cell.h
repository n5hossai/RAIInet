#ifndef CELL_H
#define CELL_H
#include <string>
#include "Player.h"
class Player;
struct Cell
{

    int row;
    int col;
    char text;
    bool isServerPort = false;
    int whoseServerPort = 0;
    bool isFireWall = false;
    int fireWallOwner = 0;
    bool isEmpty = true;
    bool isEdge = false;
    int whoseEdge = 0;



    Cell(int row, int col);
    
};

#endif