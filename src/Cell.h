#ifndef CELL_H
#define CELL_H
#include <string>

class Cell{
    private:
        int row;
        int col;
        char cellText;
        bool isServerPort;
        bool hasFireWall;
        int whoBuiltFirewall; 
        int edgeOfPlayer();
    public:
        Cell(int row, int col);
        ~Cell();
        int getRow();
        int getCol();
        void setCellText(char text);
        char getCellText();
        bool isEdge();
        int getEdgeOfPlayer();
        bool getIsServerPort();
        bool getHasFireWall();
        int getWhoBuiltFireWall();
};

#endif