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
    bool isServerPort;
    int whoseServerPort;
    bool isFireWall;
    int fireWallOwner;
    bool isEmpty= true;
    bool isEdge;
    Cell(int row, int col);
};

#endif
