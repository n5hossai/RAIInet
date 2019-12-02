#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Game.h"
#include "TextDisplay.h"
#include "Graphics.h"

using namespace std;

int main(int argc, const char* argv[]){
    int numOfPlayers = 2; //Only support 2 player from command line rn
    int initPlayer = 1; // Begin with player 1

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

    std::vector<std::string> abilities;
    abilities.push_back(ability1);
    abilities.push_back(ability2);
    std::vector<std::string> links;
    links.push_back(link1);
    links.push_back(link2);
    Game* game = new Game(abilities, links, hasGraphics, numOfPlayers, initPlayer);

    // start the diaplays
    TextDisplay* td = new TextDisplay( numOfPlayers, initPlayer, game->players);
    game->attach(td);
    if (hasGraphics){
      Graphics* graphics = new Graphics(numOfPlayers, initPlayer, td->players);
      td->attach(graphics);
    }

    cout << *td;
    string command;
    bool usedAbilityOnTurn = false;
    while(cin >> command){
      if(command == "abilities"){
       cout << game->getAbilityStatus();
       continue;
      }
      else if(command == "board"){
       cout << *td;
       continue;
      }
      else if(command == "ability" ){
        if (usedAbilityOnTurn) {
          cout<< "ONLY 1 ABILITY ALLOWED PER TURN: PLEASE EXECUTE A MOVE"<<endl;
        }
        else {
          try{
            int ab;
            cin>>ab;
            game->applyAbility(ab);
            usedAbilityOnTurn = true;
            cout << *td;
            if(game->getGameWon()){
              break;
            }
          }catch(const exception& ex){
            cout<<ex.what()<<" PLEASE TRY AGAIN"<<endl;
          }
       }
         continue;
      }
      else if(command == "move"){
        try{
          char id;
          string dir;
          cin >> id >> dir;
          game->applyMove(id,dir);
          game->togglePlayer();
          usedAbilityOnTurn = false;
          cout << *td;
          if(game->getGameWon()){
              break;
            }
        }
        catch(const exception& ex){
            cout<<ex.what()<<" PLEASE TRY AGAIN"<<endl;
            continue;
          }
      }
      else if(command == "quit"){
        cout<<"GAME TERMINATED";
       break;
      }

    }

    if(game->getGameWon()){
      cout<<"CONGRATUALTIONS PLAYER "<< game->getWinner()<< ": YOU ARE THE RAIINET CHAMPION!!!" << endl;
      game->notifyObservers();
    }
}