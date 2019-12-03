#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "Cell.h"

class Player;
class Observer;
class Subject {
	std::vector<std::shared_ptr<Observer>> observers;
	public:
	void attach (std::shared_ptr<Observer> o);
	void clearOb();
	void notifyObservers();
	virtual int getCurrPlayer() = 0;
	virtual std::vector<shared_ptr<Player>> getPlayers() = 0;
	virtual std::vector<std::vector<Cell>> getBoard() = 0;
	virtual bool getGameWon() const = 0;
	virtual int getWinner() const = 0;
};
#endif