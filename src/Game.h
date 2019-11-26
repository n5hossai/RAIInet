#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"

class Game : public Subject{
    private:
        std::vector<std::vector<Cell>> board;
        std::vector<Player> players;
        int boardSize;
        bool isGraphics;
        TextDisplay* td;
        GraphicDisplay* gd;
        int currPlay;
        int numOfPlayers;
        void battle(int op, Link& link1, Link& link2);
        void applyLinkBoost(char id);
        void applyPortal(char id, int r, int c);
        void applyStrengthen(char id);
        void applySand(int r, int c);
        void applyDownload(char id);
        void applyFirewall(int r, int c);
        void applyPolarize(char id);
        void applyScan(char id);
    public:
        Game(int numOfPlayers = 2);
        ~Game();
        void init(std::string abilities1, std::string abilities2, std::string links1, std::string links2);
        void move(char id, std::string direction);
        int getCurrPlayer() override;
        std::vector<Player> getPlayers() override;
        std::vector<std::vector<Cell>> getBoard() override;
};

#endif
