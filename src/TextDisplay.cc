#include "TextDisplay.h"
#include <string>
#include <sstream>
#include <iostream>

TextDisplay::TextDisplay(int numOfPlayers, int boardSize) : boardSize{boardSize}, numOfPlayers{numOfPlayers}, currPlayer{1} {
	for (int i = 0; i < boardSize; ++i) {
		std::vec<char> row_i;
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
	this->currPlayer = whoNotified.currPlay;
	this->players = whoNotified.players;
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			this->board[i][j] = whoNotified.board[i][j].cellText;
		}
	}
}

std::string printPlayerStat (const Player& player, char first_link_name, bool is_curr) {
	std::string stats = "";
	stringstream ss;
	ss >> player.playerNumber;
	stats += "Player " + ss.str() + ": \n";
	ss >> player.numOfPlayers;
	stats += "Downloaded: " + ss.str() + "D, ";
	ss >> player.numOfVirusDld;
	stats += ss.str() + "V" + "\n";
	ss >> player.numOfUnusedAbilities();
	stats += "Abilities: " + ss.str() + "\n";
	for (int i = 0; i < 8; ++i) {
		string s (1, first_link_name + i);
		stats += s;
		stats += ": ";
		if (is_curr){
			stats += player.links[i].linkDescription();
		}
		else {
			stats += (player.links[i].isVisible) ? player.links[i].linkDescription() : "?";
		}
		if ((i == 3) || (i == 7)) stats += "\n";
		else stats += "   ";
	}
	return stats;
}

std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
	int currPlayer = td.currPlayer;
	if (td.numOfPlayers == 2) {
		out << printPlayerStat(player[0], 'a', (currPlayer == 1));
		out << "========" << std::endl;
		for (int i = 0; i < td.boardSize; ++i) {
			for (int j = 0; j < td.boardSize; ++j) {
				out << td.board[i][j];
			}
			out << std::endl;
		}
		out << "========" << std::endl;
		out << printPlayerStat(player[1], 'A', (currPlayer == 2));
	}
	else return out; //not sure how to print 4 players yet
}