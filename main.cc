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
    Game* game = new Game();
    for(int i = 1 ; i < argc ; i++){
        string argument;
        istringstream argReader(argv[i]);
        argReader >> argument;
      if(argument=="-ability1"){
        //Player 1 Ability already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string abilityOrder;
        optionReader >> abilityOrder;
        game->p1.setAbilityOrder(abilityOrder);
        continue;
      }
      else if(argument=="-ability2"){
        //Player 2 Ability already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string abilityOrder;
        optionReader >> abilityOrder;
        game->p2.setAbilityOrder(abilityOrder);
        continue;
      }
      else if(argument=="-link1"){
        //Player 1 Link already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string linkOrder;
        optionReader >> linkOrder;
        game->p1.setLinkOrder(linkOrder);
        continue;
      }
      else if(argument=="-link2"){
        //Player 2 Link already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string linkOrder;
        optionReader >> linkOrder;
        game->p2.setLinkOrder(linkOrder);
        continue;
      }
      else if(argument=="-graphics"){
        //Game default graphic display option is false
        game->setGraphicsDisplay(true);
        continue;
      }
      else{
          cerr << "ERROR: INVALID COMMAND LINE ARGUMENT";
          continue;
      }
    }
    game->setPlayerLinks();
    game->printBoard();
    game->togglePlayer();
    game->printBoard();
    
}