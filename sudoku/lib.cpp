#include "lib.h"
#include <iostream>
#include<string>
#include<vector>
#include <algorithm>
#include <fstream>

using namespace std;

// implement for Menu class
// PUBLIC methods

// DOES: show current level menu
// INPUT:  user input option
void Menu::show(int option){
    update(option);
    cout<<menuText[level]<<endl;
}

// DOES: reset menu level and display menu
// INPUT:  None
void Menu::initShow(){
    level = 0;
    cout<<menuText[level]<<endl;
}
// DOES: returns current level of menu
// INPUT:  None
int Menu::getLevel(){
    return level;
}

// PRIVATE methods

// DOES: update menu level based on current level and user option
// INPUT: user option
void Menu::update(int option){
    if(level == 0 && option == 2)
        level++;
    else if(level == 1)
        level--;
}

// implement for Board class
// PUBLIC methods

// DOES: class Board construct function. gives board initial value
// INPUT: None
Board::Board(){
	for(int i=0; i<BOARD_WIDTH; i++){
        vector<char> row(BOARD_WIDTH, EMPTY_CHAR);
        board.push_back(row);
    }
}

// DOES: update board vales based on x,y
// INPUT: row x, col y, value
// validation checked already, simply replace char in board
void Board::updateBoard(int x, int y, int value){
    board[x-1][y-1] = to_string(value)[0];
}

// DOES: Abort current game.
// INPUT: None
void Board::abortGame(){
    return ;
}

// DOES: Print horizental line to split board
// INPUT: None
void Board::showHorizentalLine(){
    for(int k=0; k<10; k++)
                cout<<"-----";
    cout<<endl;
}

// DOES: display current board including row, column numbers
// INPUT: None
void Board::showBoard(){
    // print column numbers
    for(int i=1; i<=BOARD_WIDTH; i++){
        if(i==1 || i==4 || i==7)
            cout<<" ";
        else
            cout<<"\t";
        cout<<i;
    }     
    cout<<endl;

    showHorizentalLine();

    for(int i=0; i < BOARD_WIDTH; i++){
        cout<<i+1<<"|";         // print row number
        
        vector<char> row = board[i];
        for(int j=0; j < BOARD_WIDTH; j++){
            // use black space to replace EMPTY_CHAR when printing board
            if(row[j] == EMPTY_CHAR)
                cout<<" ";
            else 
                cout<<row[j];

            if(j==2 || j==5 || j==8)        // 3*3 group vertical line
                cout<<"|";
            else
                cout<<"\t";

            if (j == BOARD_WIDTH-1)  // line break
                cout<<endl;
        }
        // print horizental row line
        if(i == 2 || i==5 || i==8){
            showHorizentalLine();
        }
    }
}

// PRIVATE methods

// DOES: init board values at the start of the game 
// INPUT: difficulty level. the number of covered digits is set based on it.
// Note: Use sudokuMat.randomMat() to generate complete board,
        // then repalce some digits to create game board
void Board::initBorad(int difficulty){
    vector<vector<int>> mat = smat.randomMat();

    int cover_num = 30;
    if(difficulty == 1)
        cover_num = 2;
    else if(difficulty == 2)
        cover_num = 50;
    else if(difficulty == 3)
        cover_num = 60;

    vector<int> covered;
    int rand_a = 0, rand_b=80;
    while(cover_num--)
        covered.push_back((rand() % (rand_b-rand_a+1))+rand_a);

    for(int i=0; i<BOARD_WIDTH; i++){
        for(int j=0; j<BOARD_WIDTH; j++){
            char ch = to_string(mat[i][j])[0];
            if(find(covered.begin(), covered.end(), i*9+j) != covered.end())    // set cell empty
                ch = EMPTY_CHAR;
            // put char in board
            board[i][j] = ch;
        }
    }
    startBoard = board;
}

// DOES: to check if a put attempt valid
// INPUT:  coordinate and value
bool Board::validStep(int x, int y, int value){
    x = x-1;
    y = y-1;

    // check coordinates
    if(x<0 || x>8 || y<0 || y>8)
        return false;

    // check if position empty
    if(board[x][y] != EMPTY_CHAR)
        return false;

    // check input value range
    if(value<1 || value>9)
        return false;

    // check if value satisfies game rule
    for(int i=0; i<BOARD_WIDTH; i++){
        // check row
        if(board[x][i] == to_string(value)[0])
            return false;
        // check col
        if(board[i][y] == to_string(value)[0])
            return false;
    }

    // check mini square
    int x_start = (x / 3) * 3, y_start = (y / 3) * 3;

    for(int gap = 0; gap<3; gap++){
        if(board[x_start+gap][y_start] == to_string(value)[0] ||
            board[x_start][y_start+gap] == to_string(value)[0] ||
            board[x_start+gap][y_start+gap] == to_string(value)[0])

            return false;
    }

    // all check passed
    return true;
}

// DOES: judge if user wins
// INPUT:  None
bool Board::userWins(){
    for(int i=0; i<BOARD_WIDTH; i++){
        for(int j=0; j<BOARD_WIDTH; j++)
            if(board[i][j] == EMPTY_CHAR)
                return false;
    }
    return true;
}

// DOES: returns game steps taken
// INPUT: None
int Board::getStepsTaken(){
    return steps_taken;
}

// DOES:  reset board to the initial state
// INPUT:    None
void Board::resetBoard(){
    steps_taken = 0;
    moved_steps = stack<int>();
    board = startBoard;
    showBoard();
}

// DOES: Undo last step
// INPUT:   None
void Board::undoBoard(){
    if(!moved_steps.empty()){
        int x = moved_steps.top();      moved_steps.pop();
        int y = moved_steps.top();      moved_steps.pop();
        board[x][y] = EMPTY_CHAR;
        showBoard();
    }
}

// DOES:  init board and start a new game. 
// INPUT:  difficulty level
// returns true if user wins, otherwise false
bool Board::newGame(int difficulty){
    initBorad(difficulty);
    showBoard();
    int x, y,value;

    cout<<"Enter row, column, value(split by blank space):"<<endl;
    cout<<"(To exit: -1 0 0  To reset: 0 -1 0  To undo: 0 0 -1)"<<endl;
    while(cin>>x>>y>>value){
        if(x==-1 && y==0 && value==0)       // exit game
            return false;
        else if(x==0 && y==-1 && value==0){    // reset game
            resetBoard();
        }
        else if(x==0 && y==0 && value==-1){     // undo game
            undoBoard();
        } 
        else {                                // try put a new number
            tryPutNum(x, y, value);
            // check if user wins
            if(userWins()){
                cout<<"Congratulations, You win!"<<endl;
                cout<<"Level:"<<difficulty<<" Steps taken:"<<steps_taken<<endl;
                return true;
            }
        }
        showBoard();
        cout<<"Enter row, column, value(split by blank space):"<<endl;
        cout<<"(To exit: -1 0 0  To reset: 0 -1 0  To undo: 0 0 -1)"<<endl;
    }
}

// DOES:  checks if a put attempt valid and then update the board.
// INPUT:   coordinates and value
void Board::tryPutNum(int x, int y, int value){
    if(validStep(x, y, value)){
        updateBoard(x, y, value);
        // save moved steps
        moved_steps.push(y-1);
        moved_steps.push(x-1);

        steps_taken ++;
    }
    else {
        cout<<"You cannot put "<<value<<" at "<<x<<","<<y<<endl;
    }
}

// implement for Game class 
// PUBLIC methods
// DOES: class Game construct function
// INPUT:  None
Game::Game(){
    // load local file to read record
    ifstream infile; 
    string rec;
    try{
        infile.open(REC_FILE); 
        infile >> rec;
        record = stoi(rec);
        infile.close();
    } catch (exception){
        ;
    }
}

// DOES: Start a new game
// INPUT:   None
void Game::start(){
    menu.initShow();
}

// DOES:  controls game state, including menu selections and game state
// INPUT:   user option
bool Game::action(int option){
    int level = menu.getLevel();
    if(level == 0){
        // new game
        if (option == 1){
            bool ifWin = board.newGame(difficulty);
            // user wins, save record to local file
            if(ifWin && (record == -1 || board.getStepsTaken() < record)){
                record = board.getStepsTaken();
                try{
                    ofstream outfile;
                    outfile.open(REC_FILE);
                    outfile << record;
                    outfile.close();
                    cout<<"New record saved!"<<endl;
                } catch (exception){
                    cout<<"Write record to local file failed."<<endl;
                }
            }
            // a new game is over, re-display menu
            menu.initShow();
        }
        // select difficulty
        else if(option == 2){
            menu.show(option);      // update menu
        }
        // show records
        else if(option == 3){
            showRecord();
            menu.initShow();
        }
        // exit game
        else if(option == 4){
            exit();
            return false;   // return false to end game
        }
    } 
    // in difficulty setting
    else if (level == 1){
        // update difficulty
        if(option <1 || option>3)
            cout<<"Invalid difficulty choice"<<endl;
        else    
            difficulty = option;

        // update menu
        menu.show(option);
    }
    return true;
}

// PRIVATE methods

// DOES:  Exit entire game
// INPUT:   None
void Game::exit(){
    cout<<"Good Bye!"<<endl;
    return;
}

// DOES:    show current record
// INPUT:    None
void Game::showRecord(){
    cout<<"Minimum step taken: ";
    if(record==-1)
        cout<<"No record yet."<<endl;
    else
        cout<<record<<endl;
    return;
}
