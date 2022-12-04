# Sudoku Game

## Team Members
Ziyang Yu

## Game Description
Sudoku is played on a grid of 9 x 9 spaces. Within the rows and columns are 9 “squares” (made up of 3 x 3 spaces). Each row, column and square (9 spaces each) needs to be filled out with the numbers 1-9, without repeating any numbers within the row, column or square.

## Game features
1. Provides complete gaming framework, including menu, game interaction, difficulty setting, game records.
2. The menu allows users to: **Start New Game, Change Difficulty, Check Record, Exit Game**.
3. When playing the game, **undo**  and **reset** is allowed.
4. The initial game board is **randomly generated** based on difficulty setting (More digits will be covered if user selects hard level).
5. User record is **stored locally as a file**, and can be updated when player wins.

## Code File Description
- main.cpp - start the main program.
- lib.h, lib.cpp - implements gaming framework and game features.
- sudokuMat, changeTool - generates sudoku initial board.

## Non-standard C/C++ libraries
- The only non-standard libraries we use are `sudoku.h` and `changeTool.h`. They are already added to the project.
- These two libraries serve for the same purpose: to generate a **complete** initial sudoku game board.
- Though we used some help to generate initial game board from `sudoku.h` and `changeTool.h`, we guarantee that all the other game functions and features in `lib.h` and `lib.cpp` are implemented without any addtional help.

## Compilation and Execution
### Use Dev C++
1. Open sudoku.dev
2. Select main.cpp and **compile and run**.

### Use .exe
