#include "Cell.h"

Cell::Cell(int row, int col){}

Cell::~Cell(){}

int Cell::getRow(){}

int Cell::getCol(){}

void Cell::setCellText(char text){}

char Cell::getCellText(){
	return this->cellText;
}

bool Cell::isEdge(){}

int Cell::getEdgeOfPlayer(){}

bool Cell::getIsServerPort(){}

bool Cell::getHasFireWall(){}

int Cell::getWhoBuiltFireWall(){}