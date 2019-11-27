#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
//#include "TextDisplay.h"
//#include "Gaphics.h"

using namespace std;

class Game{
    private:        
        int boardSize;
        bool isGraphics;
        //TextDisplay* td;
        //Graphics* graphics;
    public:
        vector<vector <Cell>> board;
        vector<shared_ptr<Player>> players;
        int numOfPlayers = 2;
        int currPlay = 1;
        void battle(int op, Link& link1, Link& link2);
        void applyLinkBoost(char id);
        void applyPortal(char id, int r, int c);
        void applyStrengthen(char id);
        int applySand(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyDownload(char id);
        int applyFirewall(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyPolarize(char id);
        void applyScan(char id);
    
        Game(vector<string> abilities, vector<string> links, bool hasGraphics);
        ~Game();
        void move(char id, string direction);

        //getters
        int getBoardSize() const;
        bool getIsGraphics() const;
        //setters
        void setBoardSize(int size);
        void setIsGraphics(bool boolean_);
        void togglePlayer();
        string getAbilityStatus();
};

#endif
