#include "Subject.h"
#include "Observer.h"

void Subject::attach (Observer* o){
	this->observers.emplace_back(o);
}

void Subject::notifyObservers() {
	for (unsigned int i = 0; i < observers.size(); ++i) {
		observers[i]->notify(*this);
	}
}