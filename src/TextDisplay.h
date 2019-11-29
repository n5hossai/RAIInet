#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <vector>
#include <iostream>
#include <memory>
#include "Observer.h"
#include "Player.h"

class TextDisplay : public Observer {
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<std::vector<char>> board;
	std::vector<shared_ptr<Player>> players;
	std::string printPlayerStat (shared_ptr<Player> player, char first_link_name, bool is_curr) const;
public:
	TextDisplay(std::vector<shared_ptr<Player>> players, int numOfPlayers, int initPlayer);
	void notify(Subject& whoNotified);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif