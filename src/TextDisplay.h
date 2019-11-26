#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <vector>
#include <iostream>
#include "Observer.h"
#include "Player.h"

class TextDisplay : public Observer {
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<std::vector<char>> board;
	std::vector<Player> players;
	std::string printPlayerStat (const Player &player, char first_link_name, bool is_curr) const;
public:
	TextDisplay(int numOfPlayers = 2, int boardSize = 8);
	void notify(Subject& whoNotified);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif