#include "TextDisplay.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Subject.h"

TextDisplay::TextDisplay(int numOfPlayers, int boardSize) : numOfPlayers{numOfPlayers}, boardSize{boardSize}, currPlayer{1} {
	for (int i = 0; i < boardSize; ++i) {
		std::vector<char> row_i;
		for (int j = 0; j < boardSize; ++j) {
			if (((i == 0) || (i == boardSize - 1)) && ((j == 3) || (j == 4))) {
				row_i.emplace_back('S');
			}
			else if (((i == 0) && (j < 3)) || ((i == 1) && (j > 2) && (j < 5))) {
				row_i.emplace_back('a' + j);
			}
			else if ((i == 0) && (j > 4)) {
				row_i.emplace_back('a' + j - 2);
			} 
			else if (((i == boardSize - 1) && (j < 3)) || ((i == 6) && (j > 2) && (j < 5))) {
				row_i.emplace_back('A' + j);
			}
			else if ((i == boardSize - 1) && (j < 3)) {
				row_i.emplace_back('A' + j - 2);
			}
			else row_i.emplace_back('.');
		}
		this->board.emplace_back(row_i);
	}

}

void TextDisplay::notify(Subject& whoNotified) {
	this->currPlayer = whoNotified.getCurrPlayer();
	this->players = whoNotified.getPlayers();
	std::vector<std::vector<Cell>> board = whoNotified.getBoard();
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			this->board[i][j] = board[i][j].cellText;
		}
	}
}

std::string TextDisplay::printPlayerStat (const Player &player, char first_link_name, bool is_curr) const{
	std::string stats = "";
	std::istringstream ss;
	int temp = player.getPlayerNum();
	ss >> temp;
	stats += "Player " + ss.str() + ": \n";
	temp = player.getNumOfData();
	ss >> temp;
	stats += "Downloaded: " + ss.str() + "D, ";
	temp = player.getNumOfVirus();
	ss >> temp;
	stats += ss.str() + "V" + "\n";
	temp = player.numOfUnusedAbilities();
	ss >> temp;
	stats += "Abilities: " + ss.str() + "\n";
	for (int i = 0; i < 8; ++i) {
		Link link = player.links[i];
		std::string s (1, first_link_name + i);
		stats += s;
		stats += ": ";
		if (is_curr){
			stats += link.linkDescription();
		}
		else {
			stats += (link.getIsVisible()) ? link.linkDescription() : "?";
		}
		if ((i == 3) || (i == 7)) stats += "\n";
		else stats += "   ";
	}
	return stats;
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
	if (td.numOfPlayers == 2) {
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
	}
	return out; //not sure how to print 4 players yet
}