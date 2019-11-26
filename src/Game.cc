#include "Game.h"

int Game::getCurrPlayer() {
	return this->currPlay;
}

std::vector<Player> Game::getPlayers() {
	return this->players;
}

std::vector<std::vector<Cell>> Game::getBoard() {
	return this->board;
}