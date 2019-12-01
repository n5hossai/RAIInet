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
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 30 + thickness, score, Xwindow::Black);

		ss << players[i]->getNumOfData();
		score = "Number Of Data Downloaded: " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 50 + thickness, score, Xwindow::Black);

		ss << players[i]->getNumOfVirus();
		score = "Number Of Virus Downloaded: " + ss.str();
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 70 + thickness, score, Xwindow::Black);
	}

	//draw the play board and server port
	std::string player1 = "Player 1";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + padding + 30,  player1);

	w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness+2, boardLength + thickness*2, Xwindow::Black);
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			w.fillRectangle(padding + i * cellSize + thickness, scoreHeight + padding*2 + j*cellSize + thickness, cellSize - thickness*2, cellSize- thickness*2, Xwindow::White);
			if (((j == 0) || (j == boardSize - 1)) && ((i == 3) || (i == 4))) {
				std::string server = "S";
				w.drawString(25 + padding + i * cellSize + thickness, 30 + scoreHeight + padding*2 + j*cellSize + thickness,  server);
			}
		}
	}

	std::string player2 = "Player 2";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + boardLength + padding*2 + 30,  player2);

	//highlight the opponent edge for curr player
	if (currPlayer == 1) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness*2, thickness*2, Xwindow::Red);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness*2, thickness*2, Xwindow::Red);

	}

	//fill in the links
	for (int i = 0; i < boardSize; ++i) {  //row
		for (int j = 0; j < boardSize; ++j) {  //col
			if (((i == 0) || (i == boardSize - 1)) && ((j == 3) || (j == 4))) continue;
			bool foundLink= false;
			for (int k = 0; k < numOfPlayers; ++k) { //players look
				for (int t = 0; t < 8; ++t) { //links loop
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {
						foundLink = true;
						if (k == 0) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::Green);
						}
						else if (k == 1) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::Yellow);
						}
						std::string description = players[k]->links[t]->linkDescription();
						std::string name = string(1, players[k]->getFirstId() + t) + ":";
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
			if (!foundLink) {
				w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
			};
		}
	}
}

void Graphics::notify(Subject& whoNotified){
	this->currPlayer = whoNotified.getCurrPlayer();
	this->players = whoNotified.getPlayers();
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
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 30 + thickness, score, Xwindow::Black);

		ss << players[i]->getNumOfData();
		score = "Number Of Data Downloaded: " + ss.str();
		ss.str(std::string());
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 50 + thickness, score, Xwindow::Black);

		ss << players[i]->getNumOfVirus();
		score = "Number Of Virus Downloaded: " + ss.str();
		w.drawString(10 + padding + i*scoreWidth/2 + thickness, padding + 70 + thickness, score, Xwindow::Black);
	}

	for (int i = 0; i < boardSize; ++i) {  //row
		for (int j = 0; j < boardSize; ++j) {  //col
			if (((i == 0) || (i == boardSize - 1)) && ((j == 3) || (j == 4))) continue;
			bool foundLink= false;
			for (int k = 0; k < numOfPlayers; ++k) { //players loop
				for (int t = 0; t < 8; ++t) { //links loop
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {
						if (players[k]->links[t]->getIsDownloaded()) break;
						if (k == 0) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::Green);
						}
						else if (k == 1) {
							w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::Yellow);
						}
						std::string description = players[k]->links[t]->linkDescription();
						std::string name = string(1, players[k]->getFirstId() + t) + ":";
						w.drawString(25+padding+col*cellSize+thickness, 20+scoreHeight+padding*2+row*cellSize+thickness, name);
						if ((currPlayer == k + 1) || players[k]->links[t]->getIsVisible()) {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, description);
						}
						else {
							w.drawString(25+padding+col*cellSize+thickness, 40+scoreHeight+padding*2+row*cellSize+thickness, "?"); 
						}
						foundLink = true;
						break;
					}
				}
			}
			if (!foundLink) {
				w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
			};
			if (whoNotified.getBoard()[i][j].isFireWall){
				w.fillRectangle(padding+i*cellSize+thickness, scoreHeight+padding*2+j*cellSize+thickness, cellSize-thickness*2, cellSize-thickness*2,Xwindow::Red);
				stringstream ss;
				ss << whoNotified.getBoard()[i][j].fireWallOwner;
				w.drawString(15+padding+i*cellSize+thickness, 30+scoreHeight+padding*2+j*cellSize+thickness, +"FW: " +ss.str());

			}
		}
	}

	//highlight the opponent edge for curr player
	if (currPlayer == 1) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness*2, thickness*2, Xwindow::Black);
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness*2, thickness*2, Xwindow::Red);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 + boardLength - thickness, boardLength + thickness*2, thickness*2, Xwindow::Black);
		w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness*2, thickness*2, Xwindow::Red);

	}
}