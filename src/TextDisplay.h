#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <stdlib>
#include <vector>
#include <iostream>
#include "Observer.h"

class TextDisplay : public observers{
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<std::vector<char>> board;
	std:vector<Player> players;
public:
	TextDisplay(int numOfPlayers = 2, int boardSize = 8);
	void notify(Subject& whoNotified);
	friend std::ostream& operator<< (std::ostrem& out, const TextDisplay& td);
}

#endif