#include <iostream>
#include "window.h"
#include <string>
#include <vector>
#include "graphicsdemo.h"

using namespace std;

// int coor::getCellX(coor cel) const
// {
//   return cel.x;
// }
// int coor::getCellY(coor cel) const
// {
//   return cel.y;
// }

int main()
{
  string com;
  Xwindow w;
  do
  {

    // cout << to_string(coors[5][1].y) << endl;
    // cout << to_string(c51.x) << endl;
    // cout << to_string(c51.x) << endl;

    

    // vector<vector<string>> links{{p1a, p1b, p1c, p1d, p1e, p1f, p1g, p1h},
    //                                  {p2A, p2B, p2C, p2D, p2E, p2F, p2G, p2H}};

    // (links_str[0][0]) = com;
    // p1a = links_str[0][0];

    // cout << links_str[0][0] + "blaa" << endl;

    //*************DO NOT TOUCH BELOW THIS: *********//
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

    // For server ports:
    w.drawString(c03.x, c03.y, " S ");
    w.drawString(c04.x, c04.y, " S ");
    w.drawString(c73.x, c73.y, " S ");
    w.drawString(c74.x, c74.y, " S ");

    w.drawString(c55.x, c55.y, com);

    // w.drawString(c00.x, c00.y, "T");

    // w.drawString(c51.x, c51.y, "P");
    // // cout << to_string(c77.x) <<" " << to_string(c77.y) << endl;
    // w.drawString(c77.x, c77.y, "L");
    // cout << to_string(c77.x) <<" " << to_string(c77.y) << endl;

    //for player 1:
    w.drawString(400, 20, "PLAYER 1"); // player name

    w.drawString(20, 30, "Downloaded: ");
    w.drawString(85, 30, P1DownData);   // download name p1
    w.drawString(100, 30, P1DownComma); // download comma p1
    w.drawString(120, 30, P1DownVirus); // download virus p1

    w.drawString(20, 45, "Abilities: ");
    w.drawString(75, 45, P1Abilites); // abilities p1

    w.drawString(20, 60, "a: ");
    w.drawString(40, 60, p1a);
    w.drawString(80, 60, "b: ");
    w.drawString(100, 60, p1b);
    w.drawString(140, 60, "c: ");
    w.drawString(160, 60, p1c);
    w.drawString(200, 60, "d: ");
    w.drawString(220, 60, p1d);

    w.drawString(20, 75, "e: ");
    w.drawString(40, 75, p1e);
    w.drawString(80, 75, "f: ");
    w.drawString(100, 75, p1f);
    w.drawString(140, 75, "g: ");
    w.drawString(160, 75, p1g);
    w.drawString(200, 75, "h: ");
    w.drawString(220, 75, p1h);

    // for player 2
    w.drawString(400, 795, "PLAYER 2"); // player name

    w.drawString(20, 805, "Downloaded: ");
    w.drawString(85, 805, P2DownData);   // download name p2
    w.drawString(100, 805, P2DownComma); // download comma p2
    w.drawString(120, 805, P2DownVirus); // download virus p2

    w.drawString(20, 820, "Abilities: ");
    w.drawString(75, 820, P2Abilites); // abilities p2

    w.drawString(20, 835, "A: ");
    w.drawString(40, 835, p2A);
    w.drawString(80, 835, "B: ");
    w.drawString(100, 835, p2B);
    w.drawString(140, 835, "C: ");
    w.drawString(160, 835, p2C);
    w.drawString(200, 835, "D: ");
    w.drawString(220, 835, p2D);

    w.drawString(20, 850, "E: ");
    w.drawString(40, 850, p2E);
    w.drawString(80, 850, "F: ");
    w.drawString(100, 850, p2F);
    w.drawString(140, 850, "G: ");
    w.drawString(160, 850, p2G);
    w.drawString(200, 850, "H: ");
    w.drawString(220, 850, p2H);
    //******************************************************************//
    // CODE     BELOW   THIS    LINE

    //w.showAvailableFonts();
    

  }while(cin>>com);
}
