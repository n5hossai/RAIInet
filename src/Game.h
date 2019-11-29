#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include "TextDisplay.h"
//#include "Graphics.h"
#include "Subject.h"

using namespace std;

class Game : public Subject{
    private:        
        int boardSize;
        bool isGraphics;
        int numOfPlayers;
        int currPlayer;
    public:
        vector<vector <Cell>> board;
        vector<shared_ptr<Player>> players;
        TextDisplay* td;
        //Graphics* graphics;

        void battle(int op, Link& link1, Link& link2);
        void applyLinkBoost(char id);
        void applyPortal(char id, int r, int c);
        void applyStrengthen(char id);
        void applySand(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyDownload(char id);
        void applyFirewall(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyPolarize(char id);
        void applyScan(char id);
        Game(vector<string> abilities, vector<string> links, bool hasGraphics, int numOfPlayers, int currPlayer);
        ~Game();
        void move(char id, string direction);

        //getters
        int getCurrPlayer() const;
        int getNumOfPlayers() const;
        int getBoardSize() const;
        bool getIsGraphics() const;
        //setters
        void setBoardSize(int size);
        void setIsGraphics(bool boolean_);
        void togglePlayer();
        string getAbilityStatus();

        //override Subject class public methods
        int getCurrPlayer() override;
        vector<shared_ptr<Player>> getPlayers() override;
        vector<vector<Cell>> getBoard() override;
};

#endif
