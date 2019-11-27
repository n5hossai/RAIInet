#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
<<<<<<< HEAD
#include "TextDisplay.h"
//#include "Graphics.h"
#include "Subject.h"

using namespace std;

class Game : public Subject{

    private:        
        int boardSize = 8;
        bool isGraphics;
        TextDisplay* td;
        //Graphics* graphics;
    public:
        vector<vector<Cell>> board;
        vector<Player> players;
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

        Game(string abilities1, string abilities2, string links1, string links2, bool hasGraphics);
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

        //override Subject class public methods
        int getCurrPlayer() override;
        vector<Player> getPlayers() override;
        vector<vector<Cell>> getBoard() override;
};

#endif
