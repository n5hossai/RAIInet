#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Subject {
	std::vector<Observer*> observers;
	public:
	void attach (Observer* o){this->observers.emplace_back(o);};
	void notifyObservers() {
	for (auto& ob: observers) {
		ob->notify(*this);
	}
	};
	virtual int getCurrPlayer() = 0;
	virtual std::vector<shared_ptr<Player>> getPlayers() = 0;
	virtual std::vector<std::vector<Cell>> getBoard() = 0;
};

#endif