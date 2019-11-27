
#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include "TextDisplay.h"
#include "Graphics.h"
#include "Subject.h"

class Game : public Subject{
    private:        
        int boardSize;
        bool isGraphics;
        TextDisplay* td;
        GraphicDisplay* gd;
    public:
        std::vector<std::vector <Cell> > board;
        std::vector<Player> players;
        int numOfPlayers = 2;
        int currPlay;
        void battle(int op, Link& link1, Link& link2);
        void applyLinkBoost(char id);
        void applyPortal(char id, int r, int c);
        void applyStrengthen(char id);
        int applySand(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyDownload(char id);
        int applyFirewall(int r, int c, int p); // returning 0 means ability cast failed, 1 means successful
        void applyPolarize(char id);
        void applyScan(char id);

        Game(std::string abilities1, std::string abilities2, std::string links1, std::string links2, bool hasGraphics);
        ~Game();
        void move(char id, std::string direction);

        //getters
        int getBoardSize() const;
        bool getIsGraphics() const;
        //setters
        void setBoardSize(int size);
        void setIsGraphics(bool boolean_);
        void togglePlayer();
        std::string getAbilityStatus();

        //override Subject class public methods
        int getCurrPlayer() override;
        std::vector<Player> getPlayers() override;
        std::vector<std::vector<Cell>> getBoard() override;
};

#endif
