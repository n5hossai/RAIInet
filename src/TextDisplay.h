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
	std::vector<shared_ptr<Player>> players;
	std::string printPlayerStat (shared_ptr<Player> player, char first_link_name, bool is_curr) const;
public:
	TextDisplay(vector<string> abilities, vector<string> links, int numOfPlayers = 2);
	void notify(Subject& whoNotified);
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif