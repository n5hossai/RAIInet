#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <memory>
#include "Game.h"
#include "TextDisplay.h"
#include "Graphics.h"

using namespace std;

bool isAbilitiesValid(string s) {
  int L = 0;
  int F = 0;
  int D = 0;
  int P = 0;
  int S = 0;
  int N = 0;
  int O = 0;
  int R = 0;
  for (unsigned int i = 0; i < s.size(); ++i){
      if (s[i] == 'L') L += 1;
      else if (s[i] == 'F') F += 1;
      else if (s[i] == 'D') D += 1;
      else if (s[i] == 'P') P += 1;
      else if (s[i] == 'S') S += 1;
      else if (s[i] == 'N') N += 1;
      else if (s[i] == 'O') O += 1;
      else if (s[i] == 'R') R += 1;
      else return false;
  }
  if (L > 2 || F > 2 || D > 2 || P > 2 || S > 2 || N > 2 || O > 2 || R > 2) return false;
  return true;
}

int main(int argc, const char* argv[]){
    int numOfPlayers = 2; //Only support 2 player from command line rn
    int initPlayer = 1; // Begin with player 1

    //Start Game
    //Initialize Game players default abilities LFDPS
    //Initialize Game players default links V1D4V3V2D3V4D2D1

    //Setting Command Line Argument Options
    string ability1 = "LFDSP";
    string ability2="LFDSP";
    string link1="V1V2V3V4D1D2D3D4";
    string link2="V1V2V3V4D1D2D3D4";
    bool hasGraphics = false;
    bool sleep = false;
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
        if (!isAbilitiesValid(ability1)) {
          cerr << "ERROR: INVALID ABILITIES ENTERED." << endl;
          return 1;
        }
      }
      else if(argument=="-ability2"){
        //Player 2 Ability already default initialize
        i++;
        istringstream optionReader(argv[i]);
        string abilityOrder;
        optionReader >> ability2;
        if (!isAbilitiesValid(ability2)) {
          cerr << "ERROR: INVALID ABILITIES ENTERED." << endl;
          return 1;
        }
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
      else if(argument == "-sleep") {
        sleep = true;
        continue;
      }
      else{
          cerr << "ERROR: INVALID COMMAND LINE ARGUMENT." << endl;
          return 1;
      }
    }

    std::vector<std::string> abilities;
    abilities.push_back(ability1);
    abilities.push_back(ability2);
    std::vector<std::string> links;
    links.push_back(link1);
    links.push_back(link2);
    Game game = Game(abilities, links, hasGraphics, numOfPlayers, initPlayer);

    // start the diaplays
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>(numOfPlayers, initPlayer, game.players);
    shared_ptr<Graphics> graphics;
    game.attach(td);
    if (hasGraphics){
      graphics=  make_shared<Graphics>(numOfPlayers, initPlayer, td->players);
      td->attach(graphics);
    }

    cout << *td;
    string command;
    string fileName;
    ifstream fs;
    bool usedAbilityOnTurn = false;
   
    
    while(fs >> command || cin >> command){
      if(command == "sequence"){
        fs.close();  
        fs.clear();
        cin>>fileName;
        fs.open(fileName);
        if(!fs.is_open()) cout << "FILE NOT FOUND ENTER SEQUENCE COMMAND AGAIN"<<endl;
      }else if(command == "abilities"){
       cout << game.getAbilityStatus();
       continue;
      }
      else if(command == "board"){
       cout << *td;
       continue;
      }
      else if(command == "ability" ){
        if (usedAbilityOnTurn) {
          cout<< "ONLY 1 ABILITY ALLOWED PER TURN: PLEASE EXECUTE A MOVE"<<endl;
          continue;
        }
        else {
          try{
            int ab;
            string s;
            if (cin >> s) {
              istringstream ss{s};
              if(ss >> ab && ab < 6 && ab > 0) {
                game.applyAbility(ab);
                usedAbilityOnTurn = true;
                cout << *td;
                if(game.getGameWon()){
                  break;
                }
              }
              else {
                cout << "PLEASE ENTER A NUMBER IN RANGE 1-5." <<endl;
                continue;
              }
            }
            else {
              if (fs >> ab && ab < 6 && ab > 0) {
                game.applyAbility(ab);
                usedAbilityOnTurn = true;
                cout << *td;
                if(game.getGameWon()){
                  break;
                }
              }
              else {
                cout << "PLEASE ENTER A NUMBER IN RANGE 1-5." <<endl;
                continue;
              }
            }
          }catch(const exception& ex){
            cout<<ex.what()<<" PLEASE TRY AGAIN"<<endl;
            continue;
          }
       }
      }
      else if(command == "move"){
        try{
          char id;
          string dir;
          if (!(fs >>id >> dir|| cin >> id >> dir)) {
            cout << "PLEASE ENTER AN ID AND A DIRECTION." << endl;
            continue;
          }
          game.applyMove(id,dir);
          if (sleep) {
            std::chrono::milliseconds timespan(1000);
            std::this_thread::sleep_for(timespan);
          }
          game.togglePlayer();
          usedAbilityOnTurn = false;
          cout << *td;
          if(game.getGameWon()){
              break;
            }
        }
        catch(const exception& ex){
            cout<<ex.what()<<" PLEASE TRY AGAIN"<<endl;
            continue;
          }
      }
      else if(command == "quit"){
        cout<<"GAME TERMINATED" << endl;
        break;
      }
      else {
        cout << "COMMAND NOT RECOGNIZED. PLEASE TRY AGAIN." << endl;
        continue;
      }
    }

    //decide if game has won
    if(game.getGameWon()){
      cout<<"CONGRATUALTIONS PLAYER "<< game.getWinner()<< ": YOU ARE THE RAIINET CHAMPION!!!" << endl;
      game.notifyObservers();
      std::chrono::milliseconds timespan(1000); // or whatever
      std::this_thread::sleep_for(timespan);
    }

    //free memory
    for (int i = 0; i < 2; ++i) {
      game.players[i]->links.clear();
      game.players[i]->abilities.clear();
      game.players[i]->downloaded.clear();
    }
    game.players.clear();
    game.clearOb();
    td->clearOb();
    return 0;
}