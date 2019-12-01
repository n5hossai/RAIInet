#include "Graphics.h"
#include <sstream>
#include "Subject.h"

//configurations
int windowWidth = 580;
int windowHeight = 880;
int cellSize = 60;
int scoreWidth = 480;
int scoreHeight = 100;
int boardLength = 480;
int padding = 50;
int thickness = 3;

int player1Color = Xwindow::Green;
int player2Color = Xwindow::Yellow;
int FirewallColor = Xwindow::Red;
int highlight = Xwindow::Red;

Graphics::Graphics(int numOfPlayers, int initPlayer, std::vector<shared_ptr<Player>> players){
	this->numOfPlayers = numOfPlayers;
	this->currPlayer = initPlayer;
	this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;
	this->players = players;

	//draw the window
	w.drawRectangle(0, 0, windowWidth, windowHeight);

	//draw the scoreboard
	w.fillRectangle(padding-thickness, padding - thickness, scoreWidth + thickness*2, scoreHeight + thickness*2, Xwindow::Black);
	w.fillRectangle(padding + thickness, padding + thickness, scoreWidth/2 - thickness*2, scoreHeight - thickness*2, Xwindow::White);
	w.fillRectangle(padding + scoreWidth/2 + thickness, padding + thickness, scoreWidth/2 - thickness*2, scoreHeight - thickness*2, Xwindow::White);

	//display score in the scoreboard:  (STRING COLOR IS NOT WORKING)
	for (int i = 0; i < numOfPlayers; ++i) {
		std::stringstream ss;
		ss << players[i]->getPlayerNum();
		std::string score = "Player " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 30 + thickness, score);

		ss << players[i]->getNumOfData();
		score = "Number Of Data Downloaded: " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 50 + thickness, score);

		ss << players[i]->getNumOfVirus();
		score = "Number Of Virus Downloaded: " + ss.str();
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 70 + thickness, score);
	}

	//draw the play board
	std::string player1 = "Player 1";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + padding + 30,  player1);

	w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness+2, boardLength + thickness*2, Xwindow::Black);

	std::string player2 = "Player 2";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + boardLength + padding*2 + 30,  player2);

	//fill in the links
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			bool empty= true;
			for (int k = 0; k < numOfPlayers; ++k) {
				if (((players[k]->SSCells[0]->row == i) && (players[k]->SSCells[0]->col == j)) 
					|| ((players[k]->SSCells[1]->row == i) && (players[k]->SSCells[1]->col == j))) {
					empty = false;
					w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
					std::string server = "S";
					w.drawString(25 + padding + j* cellSize + thickness, 30 + scoreHeight + padding*2 + i*cellSize + thickness,  server);
					break;
				}
				for (int t = 0; t < 8; ++t) {
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {
						empty = false;
						if (k == 0) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, player1Color);
						}
						else if (k == 1) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, player2Color);
						}
						std::string description = players[k]->links[t]->linkDescription();
						std::string name = std::string(1, players[k]->links[t]->getId()) + ":";
						w.drawString(25+padding+col*cellSize+thickness, 20+scoreHeight+padding*2+row*cellSize+thickness, name);
						if ((currPlayer == k + 1) || players[k]->links[t]->getIsVisible()) {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, description);
						}
						else {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, "?"); 
						}
						break;
					}
				}
			}
			if (empty) {
				w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
			};
		}
	}

	//highlight the opponent edge for curr player
	if (currPlayer == 1) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness, thickness*2, highlight);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness, thickness*2, highlight);

	}
}

void Graphics::notify(Subject& whoNotified){
	this->currPlayer = whoNotified.getCurrPlayer();
	this->players = whoNotified.getPlayers();
	
	//update the score board
	w.fillRectangle(padding + thickness, padding + thickness, scoreWidth/2 - thickness*2, scoreHeight - thickness*2, Xwindow::White);
	w.fillRectangle(padding + scoreWidth/2 + thickness, padding + thickness, scoreWidth/2 - thickness*2, scoreHeight - thickness*2, Xwindow::White);
	
	for (int i = 0; i < numOfPlayers; ++i) {
		std::stringstream ss;
		ss << players[i]->getPlayerNum();
		std::string score = "Player " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 30 + thickness, score);

		ss << players[i]->getNumOfData();
		score = "Number Of Data Downloaded: " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 50 + thickness, score);

		ss << players[i]->getNumOfVirus();
		score = "Number Of Virus Downloaded: " + ss.str();
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 70 + thickness, score);
	}

	//update the play board:
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			bool empty= true;
			for (int k = 0; k < numOfPlayers; ++k) {
				if (((players[k]->SSCells[0]->row == i) && (players[k]->SSCells[0]->col == j)) 
					|| ((players[k]->SSCells[1]->row == i) && (players[k]->SSCells[1]->col == j))) {
					empty = false;
					w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
					std::string server = "S";
					w.drawString(25 + padding + j * cellSize + thickness, 30 + scoreHeight + padding*2 + i*cellSize + thickness,  server);
					break;
				}
				int numOfFW = players[k]->fwCells.size();
				for (int t = 0; t < numOfFW; ++t) {
					if ((players[k]->fwCells[t]->row == i) && (players[k]->fwCells[t]->col == j)) {
						empty = false;
						w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness, cellSize/2-thickness, cellSize-thickness*2,FirewallColor);
						w.fillRectangle(padding+j*cellSize+cellSize/2, scoreHeight+padding*2+i*cellSize+thickness, cellSize/2-thickness, cellSize-thickness*2,player1Color); //TOCHANGE
						break;
					}
				}
				for (int t = 0; t < 8; ++t) {
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {
						if (players[k]->links[t]->getIsDownloaded()) break;
						if (k == 0) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, player1Color);
						}
						else if (k == 1) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, player2Color);
						}
						std::string description = players[k]->links[t]->linkDescription();
						std::string name = std::string(1,players[k]->links[t]->getId()) + ":";
						w.drawString(25+padding+col*cellSize+thickness, 20+scoreHeight+padding*2+row*cellSize+thickness, name);
						if ((currPlayer == k + 1) || players[k]->links[t]->getIsVisible()) {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, description);
						}
						else {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, "?"); 
						}
						empty = false;
						break;
					}
				}
			}
			if (empty) {
				w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
			};
		}
	}

	//highlight the opponent edge for curr player
	if (currPlayer == 1) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness, thickness*2, Xwindow::Black);
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness*2, thickness*2, highlight);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness*2, thickness*2, Xwindow::Black);
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness, thickness*2, highlight);

	}
}