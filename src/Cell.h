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
    bool isEmpty;
    bool isEdge;



    Cell(int row, int col);
    //getters:
    // int getRow() const;
    // int getCol() const;
    // char getText() const;
    // bool getIsServerPort() const;
    // int getWhoseServerPort() const;
    // bool getIsFireWall() const;
    // int getFireWallOwner() const;
    // bool getIsEmpty() const;
    // bool getIsEdge() const;
    //setters:
    // void setRow(int row_);
    // void setCol(int col_);
    // void setText(char text_);
    // void setIsServerPort(bool boolean_);
    // void setWhoseServerPort(int whoseServerPort_);
    // void setIsFireWall(bool boolean_);
    // void setFireWallOwner(int fireWallOwner_);
    // void setIsEmpty(bool boolean_);
    // void setIsEdge(bool boolean_);
};

#endif