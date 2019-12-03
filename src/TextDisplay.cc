#include "TextDisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Subject.h"
#include "Cell.h"

TextDisplay::TextDisplay(int numOfPlayers, int initPlayer, std::vector<shared_ptr<Player>> players) {
	this->numOfPlayers = numOfPlayers;
	this->currPlayer = initPlayer;
	this->boardSize = (numOfPlayers == 2) ? 8 : 10;	
	this->players = players;

	for (int i = 0; i < boardSize; ++i) {
		std::vector<char> row_i;
		for (int j = 0; j < boardSize; ++j) {
			bool empty= true;
			for (int k = 0; k < numOfPlayers; ++k) { 
				if (((players[k]->SSCells[0]->row == i) && (players[k]->SSCells[0]->col == j)) 
					|| ((players[k]->SSCells[1]->row == i) && (players[k]->SSCells[1]->col == j))) {
					empty = false;
					row_i.emplace_back('S');
					break;
				}
				for (int t = 0; t < 8; ++t) {
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {
						empty = false;
						row_i.emplace_back(players[k]->links[t]->getId());
						break;
					}
				}
			}
			if (empty) {
				row_i.emplace_back('.');
			};
		}
		this->board.emplace_back(row_i);
	}
}

void TextDisplay::notify(Subject& whoNotified) {
	this->currPlayer = whoNotified.getCurrPlayer();
	this->players = whoNotified.getPlayers();
	this->whoWon = whoNotified.getWinner();
	this->hasWonGame = whoNotified.getGameWon();

	if (hasWonGame) {
		notifyObservers();
		for (int i = 0; i < 2; ++i) {
			this->players[i]->links.clear();
			this->players[i]->abilities.clear();
			this->players[i]->downloaded.clear();
		}
		this->players.clear();
		return;
	}
	std::vector<std::vector<Cell>> board = whoNotified.getBoard();
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			if (board[i][j].isFireWall) {
				this->board[i][j] = 'x' + board[i][j].fireWallOwner - 1;  //"w", "x","y","z" represent firewalls
			}
			else this->board[i][j] = board[i][j].text;
		}
	}
	notifyObservers();
}

std::string TextDisplay::printPlayerStat (shared_ptr<Player> player, char first_link_name, bool is_curr) const{
	std::string stats = "";
	std::stringstream ss;
	int temp = player->getPlayerNum();
	ss << temp;
	stats += "Player " + ss.str() + ": \n";

	temp = player->getNumOfData();
	ss.str(std::string());
	ss << temp;
	stats += "Downloaded: " + ss.str() + "D, ";

	temp = player->getNumOfVirus();
	ss.str(std::string());
	ss << temp;
	stats += ss.str() + "V" + "\n";

	temp = player->numOfUnusedAbilities();
	ss.str(std::string());
	ss << temp;
	stats += "Abilities: " + ss.str() + "\n";

	for (int i = 0; i < 8; ++i) {
		std::string s (1, first_link_name + i);
		stats += s;
		stats += ": ";

		if (is_curr){
			stats += player->links[i]->linkDescription();
		}
		else {
			stats += (player->links[i]->getIsVisible()) ? player->links[i]->linkDescription() : "?";
		}

		if ((i == 3) || (i == 7)) stats += "\n";
		else stats += "   ";
	}
	return stats;
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
	out << td.printPlayerStat(td.players[0], 'a', (td.currPlayer == 1));
	out << "========" << std::endl;
	for (int i = 0; i < td.boardSize; ++i) {
		for (int j = 0; j < td.boardSize; ++j) {
			out << td.board[i][j];
		}
		out << std::endl;
	}
	out << "========" << std::endl;
	out << td.printPlayerStat(td.players[1], 'A', (td.currPlayer == 2));
	
	//not sure how to print 4 players yet
	// else {
	// 	out << td.printPlayerStat(td.players[2], 'A', (td.currPlayer == 3));
	// 	out << td.printPlayerStat(td.players[3], 'A', (td.currPlayer == 4));
	// }
	return out; 
}

//override Subject class public methods
int TextDisplay::getCurrPlayer() {
	return this->currPlayer;
}

std::vector<shared_ptr<Player>> TextDisplay::getPlayers() {
	return this->players;
}

// ONLY HERE IN ORDER TO COMPILE. SHOULE NOT BE USED!!!
std::vector<std::vector<Cell>> TextDisplay::getBoard(){
	std::vector<std::vector<Cell>> v;
	return v;
}

bool TextDisplay::getGameWon() const {
	return this->hasWonGame;
}

int TextDisplay::getWinner() const {
	return this->whoWon;
}