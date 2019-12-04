#include "Game.h"
#include "Cell.h"
#include "Player.h"
#include "Link.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

Game::Game(vector<string> abilities, vector<string> links, bool hasGraphics, int numOfPlayers, int initPlayer){
    this->numOfPlayers = numOfPlayers;
    this->currPlayer = initPlayer;
    this->boardSize = (numOfPlayers == 2) ? 8 : 10 ;
    this->gameWon = false;
    this->gameWinner = 0;
    for (int i = 0; i < boardSize; ++i) {
        vector<Cell> row_i;
        for (int j = 0; j < boardSize; ++j) {
            row_i.emplace_back(Cell(i, j));
        }
        board.emplace_back(row_i);
    }
    for (int i = 0; i < numOfPlayers; ++i) {
        players.push_back(make_shared<Player>(abilities[i], links[i], i+1));
    }
    players[0]->SSCells.push_back(&board[0][3]);
    players[0]->SSCells.push_back(&board[0][4]);
    players[1]->SSCells.push_back(&board[7][3]);
    players[1]->SSCells.push_back(&board[7][4]);
    setIsGraphics(hasGraphics);
}

Game::~Game(){}

int whoseLink(char id){
    if(id>='a'&& id<='h'){
        return 1;
    }else if(id>='A'&& id<='H'){
        return 2;
    }
    return 0;
}

//TODO:check if ability is available FOR ALL ABILITIES
//TODO:check if meets the condition of using abilities
void Game::applyAbility(int ab){
    if(players[currPlayer-1]->abilities[ab-1]->getIsUsed()) throw runtime_error("CHECK YOUR ABILITY STATUS AND TRY AGAIN, CANNOT USE ABILITY.");
    string ability = players[currPlayer-1]->abilities[ab-1]->getAbilityName();
    try{
        if(ability == "LinkBoost"){
            char id;
            if (cin >> id && ((('a'<=id) && (id<='h')) || (('A'<=id) && (id <= 'H')))) applyLinkBoost(id);
            else throw runtime_error("PLEASE ENTER A LINK ID.");
        }else if(ability == "Firewall"){
            int r,c;
            string s1, s2;
            cin >> s1;
            istringstream ss1{s1};
            if(ss1 >> r) {
                cin >> s2;
                istringstream ss2{s2};
                if (ss2 >> c) {
                    applyFirewall(r,c);
                }
                else throw runtime_error("PLEASE ENTER ROW AND COL NUMBERS.");
            }
            else throw runtime_error("PLEASE ENTER ROW AND COL NUMBERS.");
        }else if(ability == "Download"){
            char id;
            if (cin >> id && ((('a'<=id) && (id<='h')) || (('A'<=id) && (id <= 'H')))) applyDownload(id);
            else throw runtime_error("PLEASE ENTER A LINK ID.");
        }else if(ability == "Polarize"){
            char id;
            if (cin >> id && ((('a'<=id) && (id<='h')) || (('A'<=id) && (id <= 'H')))) applyPolarize(id);
            else throw runtime_error("PLEASE ENTER A LINK ID.");
        }else if(ability == "Scan"){
            char id;
            if (cin >> id && ((('a'<=id) && (id<='h')) || (('A'<=id) && (id <= 'H')))) applyScan(id);
            else throw runtime_error("PLEASE ENTER A LINK ID.");
        }else if(ability == "Sand"){
            int r,c;
            string s1, s2;
            cin >> s1;
            istringstream ss1{s1};
            if(ss1 >> r) {
                cin >> s2;
                istringstream ss2{s2};
                if (ss2 >> c) {
                    applySand(r,c);
                }
                else throw runtime_error("PLEASE ENTER ROW AND COL NUMBERS.");
            }
            else throw runtime_error("PLEASE ENTER ROW AND COL NUMBERS.");
        }else if(ability == "Portal"){
            char id;
            int r,c;
            if (cin >> id && ((('a'<=id) && (id<='h')) || (('A'<=id) && (id <= 'H')))) {
                string s1, s2;
                cin >> s1;
                istringstream ss1{s1};
                if(ss1 >> r) {
                    cin >> s2;
                    istringstream ss2{s2};
                    if (ss2 >> c) {
                        applyPortal(id,r,c);
                    }
                    else throw runtime_error("PLEASE ENTER LINK ID AND ROW, COL NUMBERS.");
                }
                else throw runtime_error("PLEASE ENTER LINK ID AND ROW, COL NUMBERS.");
            }
            else throw runtime_error("PLEASE ENTER LINK ID AND ROW, COL NUMBERS.");
        }else if(ability == "Strengthen"){
            char id;
            if (cin >> id) applyStrengthen(id);
            else throw runtime_error("PLEASE ENTER A LINK ID.");
        }
        players[currPlayer-1]->useAbility(ab-1);
        notifyObservers();
    }
    catch(const exception& ex){
        throw ex;
    }
}
void Game::applyLinkBoost(char id)
{   
    if(whoseLink(id)!= currPlayer) throw runtime_error("INVALID USE OF LINKBOOST ABILITY: NOT YOUR LINK.");
    if(players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF PORTAL ABILITY: LINK NOT IN PLAY");
    players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsLinkBoosted(true);
}

void Game::applyPortal(char id, int r, int c){
    if(whoseLink(id)!= currPlayer) throw runtime_error("INVALID USE OF PORTAL ABILITY: NOT YOUR LINK.");
    if(players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF PORTAL ABILITY: LINK NOT IN PLAY");
    int curRow = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getRow();
    int curCol = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getCol();
    int half= boardSize/2;
    if ((curRow<half && r < half) || (curRow>=half && r>=half)){
        generalMove(id, curRow, curCol, r, c);
    }else{
        throw runtime_error("INVALID USE OF PORTAL ABILITY: PORTAL CAN ONLY BE USED ON WITHIN LINKS CURRENT SIDE.");
    }
}

void Game::applyStrengthen(char id)
{
    if(whoseLink(id)!= currPlayer) throw runtime_error("INVALID USE OF STRENGTHEN ABILITY: NOT YOUR LINK.");
    if(players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF STRENGTHEN ABILITY: LINK NOT IN PLAY.");
    int tmp_strength = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getStrength();
    if (tmp_strength <=3)
    {
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setStrength(tmp_strength + 1);
    }
}

void Game::applyFirewall(int r, int c)
{
    
    if (((r == 0) || (r == 7)) && ((c == 3) || (c == 4)))
    {
        throw runtime_error("INVALID USE OF FIREWALL ABILITY: CAN'T BE PLACED ON SERVERPORT.");
    }
    else if ((r < 0) || (r > 7) || (c < 0) || (c > 7))
    {
        throw runtime_error("INVALID USE OF FIREWALL ABILITY: CAN'T BE PLACED OUTSIDE OF THE BOARD.");
    }
    else if (board[r][c].isFireWall)
    {

        throw runtime_error("INVALID USE OF FIREWALL ABILITY: CAN'T BE PLACED ON ANOTHER FIREWALL.");
    }
    else if (!board[r][c].isEmpty)
    {
        throw runtime_error("INVALID USE OF FIREWALL ABILITY: PLACE FIREWALL ON EMPTY CELL.");
    }
    else
    {
        board[r][c].isFireWall = true; 
        board[r][c].fireWallOwner = currPlayer; 
        players[currPlayer-1]->fwCells.push_back(&board[r][c]);
    }
}
    

void Game::applySand(int r, int c)
{
    if ((r < 0) || (r > 7) || (c < 0) || (c > 7))
    {
        throw runtime_error("INVALID USE OF SAND ABILITY: CAN'T BE USED OUTSIDE OF THE BOARD.");
    }
    else if (!board[r][c].isFireWall)
    {
        throw runtime_error("INVALID USE OF SAND ABILITY: NO FIREWALL TO BE SANDED.");
    }
    else if ((board[r][c].isFireWall) && (board[r][c].fireWallOwner == currPlayer))
    {
        throw runtime_error("INVALID USE OF SAND ABILITY: SAND OPPONENTS FIREWALL.");
    }
    else
    {
        board[r][c].isFireWall = false;
        int numOfFW = players[board[r][c].fireWallOwner - 1]->fwCells.size();
        for (int i = 0; i < numOfFW; ++i) {
            if ((players[board[r][c].fireWallOwner - 1]->fwCells[i]->row == r) && (players[board[r][c].fireWallOwner - 1]->fwCells[i]->col == c))  {
                players[board[r][c].fireWallOwner - 1]->fwCells.erase(players[board[r][c].fireWallOwner - 1]->fwCells.begin()+ i);
            }
        }

        board[r][c].fireWallOwner = 0;
    }
}
    


void Game::applyDownload(char id){
    
    if(players[whoseLink(id) - 1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF DOWNLOAD ABILITY: LINK NOT IN PLAY.");
    if(whoseLink(id)!= currPlayer){
        generalDownload(whoseLink(id),id,currPlayer);

    }else throw runtime_error("INVALID USE OF DOWNLOAD ABILITY: CAN'T DOWNLOAD YOUR OWN LINK");

}

void Game::applyPolarize(char id)
{
    if(players[whoseLink(id) - 1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF POLARIZE ABILITY: LINK NOT IN PLAY.");
    bool tmp= players[whoseLink(id)-1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->getType();
    players[whoseLink(id)-1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->setType(!tmp);
}

void Game::applyScan(char id)
{   
    if (whoseLink(id) == currPlayer) throw runtime_error("INVALID USE OF SCAN ABILITY: CANNOT SCAN YOUR OWN LINK.");
    if(players[whoseLink(id) - 1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF SCAN ABILITY: LINK NOT IN PLAY.");
    if(players[whoseLink(id)-1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->getIsVisible()) throw runtime_error("INVALID USE OF SCAN ABILITY: LINK ALREADY VISIBLE.");
    players[whoseLink(id)-1]->links[id - players[whoseLink(id) - 1]->getFirstId()]->setIsVisible(true);
}


void Game::generalMove(char id, int curRow, int curCol, int newRow, int newCol, bool ignoreFirewall){
    if(curRow<0 || curRow >=boardSize || curCol < 0 || curCol >=boardSize) throw runtime_error("INVALID USE OF MOVE: LINK NOT ON BOARD.");
    if((currPlayer==1 && newRow<0) || (currPlayer==2 && newRow >=boardSize) || newCol < 0 || newCol >=boardSize) throw runtime_error("INVALID USE OF MOVE: DESTINATION NOT ON BOARD.");

    //Moves off opponents edge
    if((currPlayer==2 && newRow<0) || (currPlayer==1 && newRow>7)){
        generalDownload(currPlayer,id,currPlayer);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);
    }

    //Moves into opponents server port
    else if(board[newRow][newCol].isServerPort && board[newRow][newCol].whoseServerPort!=currPlayer){
        generalDownload(currPlayer, id, board[newRow][newCol].whoseServerPort);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);
    }

    //Moves onto a fireWall
    else if(board[newRow][newCol].isFireWall && board[newRow][newCol].fireWallOwner!=currPlayer && ignoreFirewall == false){
        
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setIsVisible(true);
        int linkType = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getType();
        if(linkType == 1){
            generalDownload(currPlayer,id,currPlayer);
            players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
            players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);
        }

        else generalMove(id, curRow, curCol, newRow, newCol, true);
     
    //Move onto firewall remember to handle if someone already there
    }

    //Move onto empty space
    else if(board[newRow][newCol].isEmpty && board[newRow][newCol].text == '.'){
        board[curRow][curCol].text = '.';
        board[curRow][curCol].isEmpty =true;
        board[newRow][newCol].text = id;
        board[newRow][newCol].isEmpty =false;
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);
    }

    //Move onto another player
    else if(!board[newRow][newCol].isEmpty && whoseLink(board[newRow][newCol].text)!=currPlayer){
        //Initiate Battle
        char otherId = board[newRow][newCol].text;
        int otherPlayer =whoseLink(otherId);
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

        generalDownload(loser, loserID, winner);
        board[curRow][curCol].text = '.';
        board[curRow][curCol].isEmpty =true;
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setRow(newRow);
        players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->setCol(newCol);
        
        board[newRow][newCol].text = winnerID;
        board[newRow][newCol].isEmpty =false;
        // players[winner - 1]->links[winnerID - players[winner - 1]->getFirstId()]->setRow(newRow);
        // players[winner - 1]->links[winnerID - players[winner - 1]->getFirstId()]->setCol(newCol);
    }
    else throw runtime_error("INVALID USE OF MOVE.");   
    notifyObservers();
}

void Game::applyMove(char id, string direction){
    if(whoseLink(id)!= currPlayer) throw runtime_error("INVALID USE OF MOVE: MUST MOVE YOUR OWN LINK.");
    if(players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF MOVE: LINK NOT IN PLAY.");

    int moveFactor = players[currPlayer - 1]->links[id - players[currPlayer - 1]->getFirstId()]->getMoveFactor();

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
    else throw runtime_error("INVALID USE OF MOVE: DIRECTION NOT RECOGNIZED.");

    generalMove(id,curRow,curCol,newRow,newCol);

}

void Game::generalDownload(int linkOwner, char toDownloadLink, int toDownloadPlayer){
    if(players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->getIsDownloaded()) throw runtime_error("INVALID USE OF DOWNLOAD: LINK NOT IN PLAY.");
    players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->setIsVisible(true);
    players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->setIsDownloaded(true);
    players[toDownloadPlayer-1]->downloaded.push_back(players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]);
    int linkType = players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->getType();
    linkType == 0 ? players[toDownloadPlayer - 1]->dataDownload() : players[toDownloadPlayer - 1]->virusDownload();
    int row = players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->getRow();
    int col = players[linkOwner - 1]->links[toDownloadLink - players[linkOwner - 1]->getFirstId()]->getCol();
    board[row][col].text = '.';
    board[row][col].isEmpty =true;
    wonGame();
    notifyObservers();
}

void Game::wonGame(){
    for (int i=0;i< numOfPlayers; i++){
        if(players[i]->getNumOfData() == 4){
            gameWon=true;
            gameWinner = i+1;
        }
        if(players[i]->getNumOfVirus() == 4){
            gameWon=true;
            gameWinner = (i+1)==1 ? 2 :1;//WILL NOT WORK FOR 4 PLAYER
        }
    }
}

//getters

int Game::getWinner() const{
    return gameWinner;
}
bool Game::getGameWon() const{
    return gameWon;
}
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
            builder += (players[currPlayer - 1]->abilities[i]->getIsUsed()) ?" [USED]" : "";
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

