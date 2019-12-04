#include "Graphics.h"
#include <sstream>
#include <vector>
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

//define colors used in graphics
std::vector<int> playersColor {Xwindow::Green, Xwindow::Orange};
int FirewallColor = Xwindow::Red;
int highlight = Xwindow::Yellow;

Graphics::Graphics(int numOfPlayers, int initPlayer, std::vector<shared_ptr<Player>> players){
	this->numOfPlayers = numOfPlayers;
	this->currPlayer = initPlayer;
	this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;
	this->players = players;

	//draw the window
	w.fillRectangle(0, 0, windowWidth, windowHeight, Xwindow::White);

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

	//draw players' headers and highlight the curr player
	if (currPlayer == 1) {
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + padding + 20, 60,20 ,highlight);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + boardLength + padding*2 + 20, 60,20, highlight);

	}
	std::string player1 = "Player 1";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + padding + 30,  player1);

	std::string player2 = "Player 2";
	w.drawString(padding + boardLength/2 - 25, scoreHeight + boardLength + padding*2 + 30,  player2);



	//draw the board and fill in the links
	w.fillRectangle(padding - thickness, scoreHeight + padding*2 - thickness, boardLength + thickness+2, boardLength + thickness*2, Xwindow::Black);

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
						w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
						w.fillCircle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2,playersColor[k]);
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
}

void Graphics::notify(Subject& whoNotified){
	this->currPlayer = whoNotified.getCurrPlayer();
	this->players = whoNotified.getPlayers();
	this->hasWonGame = whoNotified.getGameWon();
	this->whoWon = whoNotified.getWinner();

	//if the game is over
	if (hasWonGame) {
		w.fillRectangle(0, 0, windowWidth, windowHeight, Xwindow::White);
		stringstream ss;
		ss << whoWon;
		std::string msg = "CONGRATUALTIONS PLAYER " + ss.str()+ ": YOU ARE THE RAIINET CHAMPION!!!";
		w.drawString(70, windowHeight/2, msg);
		for (int i = 0; i < 2; ++i) {
			this->players[i]->links.clear();
			this->players[i]->abilities.clear();
			this->players[i]->downloaded.clear();
		}
		this->players.clear();
		return;
	}
	
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

	//highlight curr player
	std::string player1 = "Player 1";
	std::string player2 = "Player 2";
	if (currPlayer == 1) {
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + padding + 20, 60,20 ,highlight);
		w.drawString(padding + boardLength/2 - 25, scoreHeight + padding + 30,  player1);
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + boardLength + padding*2 + 20, 60,20, Xwindow::White);
		w.drawString(padding + boardLength/2 - 25, scoreHeight + boardLength + padding*2 + 30,  player2);
	}
	else if (currPlayer == 2) {
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + boardLength + padding*2 + 20, 60,20, highlight);
		w.drawString(padding + boardLength/2 - 25, scoreHeight + boardLength + padding*2 + 30,  player2);
		w.fillRectangle(padding + boardLength/2 - 30, scoreHeight + padding + 20, 60,20 ,Xwindow::White);
		w.drawString(padding + boardLength/2 - 25, scoreHeight + padding + 30,  player1);

	}

	// draw downloded links for each player:
	for (int k = 0; k < numOfPlayers; ++k) {
		int y_data = padding + boardLength/2 - 65;
		int y_virus = padding + boardLength/2 + 35;
		for (unsigned int i = 0; i < players[k]->downloaded.size(); ++i) {
			int x = (k == 0) ? (padding + scoreHeight + thickness + 10) : (padding*2 + scoreHeight + boardLength +thickness + 10); //won't work for 4 players
			std::string description = players[k]->downloaded[i]->linkDescription();
			// if the link is data
			if(!players[k]->downloaded[i]->getType()) {
				w.fillCircle(y_data,x,cellSize/2,playersColor[players[k]->downloaded[i]->getOwnedBy() - 1]);
				w.drawString(y_data + 10,x + 20,description);
				y_data -= cellSize/2 +10;
				
			}
			//if the link is virus
			else {
				w.fillCircle(y_virus, x,cellSize/2,playersColor[players[k]->downloaded[i]->getOwnedBy() - 1]);
				w.drawString(y_virus + 10,x + 20,description);
				y_virus += cellSize/2 + 10;
			}
		}
	}
	//update the play board:
	for (int i = 0; i < boardSize; ++i) {
		for (int j = 0; j < boardSize; ++j) {
			bool empty= true;
			bool hasFW = false;

			for (int k = 0; k < numOfPlayers; ++k) {
				// find server ports
				if (((players[k]->SSCells[0]->row == i) && (players[k]->SSCells[0]->col == j)) 
					|| ((players[k]->SSCells[1]->row == i) && (players[k]->SSCells[1]->col == j))) {
					empty = false;
					w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
					std::string server = "S";
					w.drawString(25 + padding + j * cellSize + thickness, 30 + scoreHeight + padding*2 + i*cellSize + thickness,  server);
					break;
				}

				//find firewalls
				int numOfFW = players[k]->fwCells.size();
				for (int t = 0; t < numOfFW; ++t) {
					if ((players[k]->fwCells[t]->row == i) && (players[k]->fwCells[t]->col == j)) {
						empty = false;
						hasFW = true;
						w.fillRectangle(padding+j*cellSize+thickness, scoreHeight+padding*2+i*cellSize+thickness, cellSize-thickness*2, cellSize-thickness*2,playersColor[k]);
						w.fillRectangle(padding+j*cellSize+thickness*2, scoreHeight+padding*2+i*cellSize+thickness*2, cellSize-thickness*4, cellSize-thickness*4,FirewallColor);
					}
				}
			}

			for (int k = 0; k < numOfPlayers; ++k) {
				for (int t = 0; t < 8; ++t) {
					int row = players[k]->links[t]->getRow();
					int col = players[k]->links[t]->getCol();
					if ((row == i) && (col == j)) {

						//skip downloaded links
						if (players[k]->links[t]->getIsDownloaded()) {
							continue;
						}

						empty = false;
						// only color the background white if there is no firewall on this cell
						if (!hasFW) w.fillRectangle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2, cellSize-thickness*2, Xwindow::White);
						w.fillCircle(padding+col*cellSize+thickness, scoreHeight+padding*2+row*cellSize+thickness,cellSize-thickness*2,playersColor[k]);
						std::string description = players[k]->links[t]->linkDescription();
						std::string name = std::string(1,players[k]->links[t]->getId()) + ":";
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
}
