#include "Game.h"
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game(vector<string> abilities, vector<string> links, bool hasGraphics, int numOfPlayers, int initPlayer){
    this->numOfPlayers = numOfPlayers;
    this->currPlayer = initPlayer;
    this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;

    for (int i = 0; i < boardSize; ++i) {
        vector<Cell> row_i;
        for (int j = 0; j < boardSize; ++j) {
            row_i.emplace_back(Cell(i, j));
        }
        board.emplace_back(row_i);
    }
    for (int i = 0; i < numOfPlayers; ++i) {
        players.emplace_back(make_shared<Player>(abilities[i], links[i], i+1));
    }
    setIsGraphics(hasGraphics);
}

Game::~Game(){}

void Game::battle(int op, Link& link1, Link& link2){
    
}

//TODO:check if ability is available FOR ALL ABILITIES
//TODO:check if meets the condition of using abilities
void Game::applyAbility(int ab){
    if(players[currPlayer-1]->abilities[ab-1]->getIsUsed()) return;
    string ability = players[currPlayer-1]->abilities[ab-1]->getAbilityName();
    if(ability == "LinkBoost"){
        char id;
        cin >> id;
        applyLinkBoost(id);
    }else if(ability == "Firewall"){
        int r,c;
        cin >> r >> c;
        applyFirewall(r,c,currPlayer);
    }else if(ability == "Download"){
        char id;
        cin >> id;
        applyDownload(id);
    }else if(ability == "Polarize"){
        char id;
        cin >> id;
        applyDownload(id);
    }else if(ability == "Scan"){
        char id;
        cin >> id;
        applyScan(id);
    }else if(ability == "Sand"){
        int r,c;
        cin >> r >> c;
        applySand(r,c,currPlayer);
    }else if(ability == "Portal"){
        char id;
        int r,c;
        cin >> id >> r >> c;
        applyPortal(id,r,c);
    }else if(ability == "Strengthen"){
        char id;
        cin >> id;
        applyStrengthen(id);
    }
    players[currPlayer-1]->useAbility(ab-1);
}
void Game::applyLinkBoost(char id)
{   
    if (!players[currPlayer - 1]->hasAbility("LinkBoost")) return;
    if (players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsLinkBoosted()) return;
    players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsLinkBoosted(true);
}

void Game::applyPortal(char id, int r, int c){
    if (!players[currPlayer - 1]->hasAbility("Portal")) return;
    //...
}

void Game::applyStrengthen(char id)
{
    if (!players[currPlayer - 1]->hasAbility("Strengthen")) return;
    int tmp_strength = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getStrength();
    if (tmp_strength <=3)
    {
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setStrength(tmp_strength + 1);
    }
}

void Game::applyFirewall(int r, int c, int p)
{
    if (!players[currPlayer - 1]->hasAbility("Firewall")) return;
    try
    {
        if (((r == 0) || (r == 7)) && ((c == 3) || (c == 4)))
        {
            string err_st = "Cannot apply Firewall on top of Server Port";
            throw err_st;
        }
        else if (board[r][c].isFireWall)
        {

            string err_st = "Player" + to_string(board[r][c].fireWallOwner) + " already owns a firewall here";

            throw err_st;
        }
        else if ((!board[r][c].isFireWall) && (!board[r][c].isEmpty))
        {
            string err_st = "Place firewall on an empty cell";
            throw err_st;
        }
        else if ((!board[r][c].isFireWall) && (board[r][c].isEmpty))
        {
            board[r][c].isFireWall = true; //NOTE: i did not change the text as that would be handled in textdisplay
            board[r][c].fireWallOwner = p; //      to check if the cell is a firewall.
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return;
    }
}

void Game::applySand(int r, int c, int p)
{
    if (!players[currPlayer - 1]->hasAbility("Sand")) return;
    try
    {
        if (!board[r][c].isFireWall)
        {
            string err_st = "There is no firewall to be sanded";
            throw err_st;
        }
        else if ((board[r][c].isFireWall) && (board[r][c].fireWallOwner != p))
        {
            board[r][c].isFireWall = false;
            board[r][c].fireWallOwner = 0;
        }
    }
    catch (string err_statement)
    {
        cout << err_statement << endl;
        return;
    }
}

void Game::applyDownload(char id){
    if (!players[currPlayer - 1]->hasAbility("Download")) return;
    //...
}

void Game::applyPolarize(char id)
{
    if (!players[currPlayer - 1]->hasAbility("Polarize")) return;
    bool tmp= players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getType();
    players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setType(!tmp);
}

void Game::applyScan(char id)
{   
    if (!players[currPlayer - 1]->hasAbility("Scan")) return;
    (players[currPlayer - 1])->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);

}

void Game::move(char id, string direction){
    
    int moveFactor = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsLinkBoosted() ? 2 : 1;
    //move on ur own link not allowed
    //INVALID MOVE is link downloaded
    int curRow = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getRow();
    int curCol = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getCol();
    int newRow = curRow;
    int newCol = curCol;
    if(direction=="up"){
        newRow=curRow-moveFactor;
    }else if(direction =="right"){
        newCol = curCol+moveFactor;
    }else if(direction =="down"){
        newRow = curRow +moveFactor;
    }else if(direction =="left"){
        newCol = curCol-moveFactor;
    }

    if(board[newRow][newCol].isServerPort && board[newRow][newCol].whoseServerPort!=currPlayer){
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsDownloaded(true);
        int linkType = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getType();
        linkType == 0 ? players[board[newRow][newCol].whoseServerPort - 1]->dataDownload() : players[board[newRow][newCol].whoseServerPort - 1]->virusDownload();
        
            board[curRow][curCol].text = '.';
            
        
        board[curRow][curCol].isEmpty =true;
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(-1);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(-1);
    }else if(board[newRow][newCol].isFireWall && board[newRow][newCol].fireWallOwner!=currPlayer){
        
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);
        
        int linkType = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getType();
        
        if(linkType == 1){
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsDownloaded(true);
        players[currPlayer - 1]->virusDownload();
        }
        
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(-1);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(-1);
            
        
    //Move onto firewall remember to handle if someone already there
    }else if((currPlayer==2 && newRow<0) || (currPlayer==1 && newRow>7)){
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsDownloaded(true);
        int linkType = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getType();
        linkType == 0 ? players[currPlayer - 1]->dataDownload() : players[currPlayer - 1]->virusDownload();
      
            board[curRow][curCol].text = '.';
            
        
        board[curRow][curCol].isEmpty =true;
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(-1);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(-1);
    }else if(board[newRow][newCol].isEmpty && board[newRow][newCol].text == '.'){
        
       
            board[curRow][curCol].text = '.';
        
        
            board[curRow][curCol].isEmpty =true;

        if(board[newRow][newCol].text == '.'){
            board[newRow][newCol].text = id;
            
        }
        board[newRow][newCol].isEmpty =false;
        
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);

    }else if(!board[newRow][newCol].isEmpty && isalpha(board[newRow][newCol].text) 
                && !(board[newRow][newCol].text >= players[currPlayer - 1]->getFirstId()
                && board[newRow][newCol].text <= players[currPlayer - 1]->links[boardSize - 1]->getId())){
        //wont work for 4 player
        int otherPlayer = currPlayer ==1?2:1;
        char otherId = board[newRow][newCol].text;
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);
        players[otherPlayer - 1]->links[otherId - players[otherPlayer - 1]->getFirstId()]->setIsVisible(true);
        int myStrength = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getStrength();
        int yourStrength = players[otherPlayer - 1]->links[otherId - players[otherPlayer - 1]->getFirstId()]->getStrength();
        int winner;
        int loser;
        winner = myStrength>=yourStrength ? currPlayer : otherPlayer;
        loser = myStrength<yourStrength ? currPlayer : otherPlayer;
        int winnerID = myStrength>=yourStrength ? id : otherId;
        int loserID = myStrength<yourStrength ? id : otherId;
        players[loser - 1]->links[loserID - players[loser - 1]->getFirstId()]->setIsDownloaded(true);
        int linkType = players[loser - 1]->links[loserID - players[loser - 1]->getFirstId()]->getType();
        linkType == 0 ? players[winner - 1]->dataDownload() : players[winner - 1]->virusDownload();
        
            board[curRow][curCol].text = '.';
            
        
        board[curRow][curCol].isEmpty =true;
        board[newRow][newCol].text = winnerID;
        board[newRow][newCol].isEmpty =false;
        players[winner - 1]->links[winnerID - players[winner - 1]->getFirstId()]->setRow(newRow);
        players[winner - 1]->links[winnerID - players[winner - 1]->getFirstId()]->setCol(newCol);

    }
    notifyObservers();

}


//getters
int Game::getBoardSize() const
{
    return this->boardSize;
}
bool Game::getIsGraphics() const
{
    return this->isGraphics;
}

//setters
void Game::setBoardSize(int size)
{
    this->boardSize = size;
}

void Game::setIsGraphics(bool boolean_)
{
    this->isGraphics = boolean_;
}

void Game::togglePlayer(){
    if (currPlayer == 1) currPlayer = 2;
    else currPlayer = 1;
    this->notifyObservers();
}

string Game::getAbilityStatus(){
    string builder;
    for(int i = 0 ; i < 5; i++){
            stringstream ss;
            ss << i+1;
            builder += "["+ ss.str()+"] ";
            builder += players[currPlayer - 1]->abilities[i]->getAbilityName();
            builder += (players[currPlayer - 1]->abilities[i]->getIsUsed()) ?" USED" : "";
            builder += "\n";
    }
    return builder;
}

//override Subject class public methods
int Game::getCurrPlayer() {
	return this->currPlayer;
}

vector<shared_ptr<Player>> Game::getPlayers() {
	return this->players;
}

vector<vector<Cell>> Game::getBoard() {
	return this->board;

} 
