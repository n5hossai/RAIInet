#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Observer.h"
#include "window.h"
#include "Player.h"
#include <vector>
#include <memory>

class Graphics : public Observer {
	Xwindow theDisplay;
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<shared_ptr<Player>> players;
public:
    Graphics(std::vector<shared_ptr<Player>> players, int numOfPlayers, int initPlayer);
    ~Graphics() = default;
    void notify(Subject &whoNotified) override;
};

#endif