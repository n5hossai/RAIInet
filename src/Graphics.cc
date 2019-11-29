#include "Graphics.h"

Graphics::Graphics(std::vector<shared_ptr<Player>> players, int numOfPlayers, int initPlayer): 
numOfPlayers{numOfPlayers}, currPlayer{initPlayer}, boardSize{(numOfPlayers == 2) ? 8: 10} {
	this->players = players;
	
}