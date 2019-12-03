#ifndef GAME_H
#define GAME_H
#include <vector>
#include <memory>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include "Subject.h"

using namespace std;

class Game : public Subject{
    private:        
        int boardSize;
        bool isGraphics;
        int numOfPlayers;
        int currPlayer;
        void generalMove(char id, int curRow, int curCol, int newRow, int newCol,bool ignoreFirewall = false);
        void generalDownload(int linkOwner, char toDownloadLink, int toDownloadPlayer);
        bool gameWon;
        int gameWinner;
        void wonGame();
    public:
        vector<vector <Cell>> board;
        vector<shared_ptr<Player>> players;

        void applyAbility(int ab);
        void applyLinkBoost(char id);
        void applyPortal(char id, int r, int c);
        void applyStrengthen(char id);
        void applySand(int r, int c); // returning 0 means ability cast failed, 1 means successful
        void applyDownload(char id);
        void applyFirewall(int r, int c); // returning 0 means ability cast failed, 1 means successful
        void applyPolarize(char id);
        void applyScan(char id);
        Game(vector<string> abilities, vector<string> links, bool hasGraphics, int numOfPlayers, int currPlayer);
        ~Game();
        void applyMove(char id, string direction);
        

        //getters
        int getCurrPlayer() const;
        int getNumOfPlayers() const;
        int getBoardSize() const;
        bool getIsGraphics() const;
        int getWinner() const override;
        bool getGameWon() const override;
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
