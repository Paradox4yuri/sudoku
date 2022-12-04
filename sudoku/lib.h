#pragma once
#ifndef LIB_H
#define LIB_H

 #include "sudokuMat.h"
#include <vector>
#include <string>
#include <stack>

using namespace std;

// show board and contain game core codes
// CENTRAL THOUGHT: Transform initMat and cover some digits to randomly get new game board
//                  Rely on sudokuMat
class Board{
    public:
    	Board();
        bool newGame(int difficulty);               // start new game
        void abortGame();                               // exit game
        void tryPutNum(int x, int y, int value);      // put a number to the board
        int getStepsTaken();                        // returns steps taken
    private:
        void updateBoard(int x, int y, int value);      // update board state
        void showBoard();                           // show current board
        void initBorad(int difficulty);             // init a new board using sudokuMat
        void resetBoard();                          // reset the board to initial state
        void undoBoard();                           // undo last step
        bool validStep(int x, int y, int value);    // check if a step is valid
        bool userWins();     // mainly to judge if the player wins
        void showHorizentalLine();                  // print a horizental line

        int steps_taken = 0;                        
        char EMPTY_CHAR = 'x';
        int BOARD_WIDTH = 9;
        sudokuMat smat;                 // sudokuMat.randomMat() can generate a complete sudoku matrix

        stack<int> moved_steps;             // use a stack to save moved steps, in case to undo.
        vector<vector<char>> startBoard;    // store initial game board, in case to reset game.
        vector<vector<char>> board;      // use 'x' to represent empty cell
};

// update and show menu
class Menu{
    public:
        void initShow();       // reset varibles and show menu
        void show(int option);  // show menu based on option
        int getLevel();         // return current menu level
    private:
        void update(int option);

        int level = 0;
        vector<string> menuText = {"1.New Game  2.Difficulty  3.Records  4.Exit", 
                                            "1.Easy  2.Normal  3.Hard"};
};

// main Game class, controls the game
class Game{
    public:
        Game();
        bool action(int option);    // process player action
        void start();       // start game
    private:
        void showRecord();
        void exit();        // exit game

        string REC_FILE = "record"; // record file name
        int record = -1;         // minimum steps taken
        bool inGame = false;
        int difficulty = 1;     // game difficulty level
        Menu menu;
        Board board;
};

#endif //!LIB_H
