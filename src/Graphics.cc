#include "Graphics.h"

Graphics::Graphics(std::vector<shared_ptr<Player>> players, int numOfPlayers, int initPlayer){
	this->numOfPlayers = numOfPlayers;
	this->currPlayer = initPlayer;
	this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;
	this->players = players;

	int scoreBoard
	// pasted from Naymul's graphicsdemo
	int i = Xwindow::Black;
    w.fillRectangle(180, 255, 490, 490, i);

    for (int x = 0; x < 8; ++x)
    {
      const int dim = 50; // square of each small block
      const int clr = Xwindow::White;
      const int side = 10;
      const int strt1 = 180;
      const int strt2 = 255;
      for (int y = 0; y < 8; ++y)
      {
        w.fillRectangle((strt1 + (side * (x + 1)) + (x * dim)), (strt2 + (side * (y + 1)) + (y * dim)), dim, dim, clr);
      }
    }

}