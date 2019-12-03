#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <vector>
#include <iostream>
#include <memory>
#include "Observer.h"
#include "Subject.h"
#include "Player.h"

class TextDisplay : public Observer, public Subject{
	int numOfPlayers;
	int boardSize;
	int currPlayer;
	std::vector<std::vector<char>> board;
	std::string printPlayerStat (shared_ptr<Player> player, char first_link_name, bool is_curr) const;
public:
	bool hasWonGame = false;
	int whoWon = 0;
	std::vector<shared_ptr<Player>> players;
	TextDisplay(int numOfPlayers, int initPlayer, std::vector<shared_ptr<Player>> players);
	void notify(Subject& whoNotified) override;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

    int getCurrPlayer() override;
    std::vector<shared_ptr<Player>> getPlayers() override;
    std::vector<std::vector<Cell>> getBoard() override;
    bool getGameWon() const override;
    int getWinner() const override;
};

#endif