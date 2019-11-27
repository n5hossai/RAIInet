#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Game.h"

using namespace std;

int main(int argc, const char* argv[]){
    //Start Game
    //Initialize Game players default abilities LFDPS
    //Initialize Game players default links V1D4V3V2D3V4D2D1

    //Setting Command Line Argument Options
    string ability1 = "LFDPS";
    string ability2="LFDPS";
    string link1="V1V2V3V4D1D2D3D4";
    string link2="V1V2V3V4D1D2D3D4";
    bool hasGraphics = false;
    for(int i = 1 ; i < argc ; i++){
        string argument;
        istringstream argReader(argv[i]);
        argReader >> argument;
      if(argument=="-ability1"){
        //Player 1 Ability already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string abilityOrder;
        optionReader >> ability1;
        continue;
      }
      else if(argument=="-ability2"){
        //Player 2 Ability already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string abilityOrder;
        optionReader >> ability2;
        continue;
      }
      else if(argument=="-link1"){
        //Player 2 Link already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string linkOrder;
        optionReader >> link1;
        continue;
      }
      else if(argument=="-link2"){
        //Player 2 Link already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string linkOrder;
        optionReader >> link2;
        continue;
      }
      else if(argument=="-graphics"){
        //Game default graphic display option is false
        hasGraphics=true;
        continue;
      }
      else{
          cerr << "ERROR: INVALID COMMAND LINE ARGUMENT";
          continue;
      }
    }

    Game* game = new Game(ability1,ability2,link1,link2,hasGraphics);
    string command;
    while(cin >> command){
      if(command == "ability"){
       game->players[game->currPlay - 1].printAbilities();
       continue;
      }
      else if(command == "board"){
       //game->printBoard();
       continue;
      }
      else if(command == "move"){
        //executemove
        game->togglePlayer();
      }
      else if(command == "quit"){
        cout<<"GAME TERMINATED";
       break;
      }

    }
    
}