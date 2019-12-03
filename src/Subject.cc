#include "Subject.h"
#include "Observer.h"

void Subject::attach (std::shared_ptr<Observer> o){
	this->observers.emplace_back(o);
}

void Subject::clearOb(){
	for (unsigned int i = 0; i < observers.size(); ++i) {
		this->observers.pop_back();
	}
}

void Subject::notifyObservers() {
	for (unsigned int i = 0; i < observers.size(); ++i) {
		observers[i]->notify(*this);
	}
}