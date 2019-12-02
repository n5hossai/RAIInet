#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Observer.h"
#include "window.h"
#include "Player.h"
#include <vector>
#include <memory>

class Graphics : public Observer {
	Xwindow w;
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<shared_ptr<Player>> players;
public:
	bool hasWonGame = false;
	int whoWon = 0;
    Graphics(int numOfPlayers, int initPlayer, std::vector<shared_ptr<Player>> players);
    ~Graphics() = default;
    void notify(Subject &whoNotified) override;
};

#endif