#pragma once
#ifndef SUDOKUMAT_H
#define SUDOKUMAT_H

#include <vector>

using namespace std;
// generate random sudoku matrix
class sudokuMat
{
public:
	sudokuMat();
	vector<vector<int>> randomMat();  //generate one random matrix
	// void getMat();          //returns random matrix

private:
	const int changeTimes = 19;  //times to change matrix
	vector<vector<int>> initMat =          //original source matrix
	{
		{ 5, 7, 4, 6, 3, 1, 8, 9, 2 },
		{ 8, 9, 6, 7, 2, 5, 4, 3, 1 },
		{ 2, 3, 1, 4, 8, 9, 6, 5, 7 },
		{ 4, 5, 2, 1, 9, 6, 7, 8, 3 },
		{ 7, 6, 8, 3, 5, 4, 2, 1, 9 },
		{ 9, 1, 3, 8, 7, 2, 5, 4, 6 },
		{ 3, 2, 9, 5, 6, 8, 1, 7, 4 },
		{ 1, 8, 7, 2, 4, 3, 9, 6, 5 },
		{ 6, 4, 5, 9, 1, 7, 3, 2, 8 }
	};
};

#endif // !SUDOKUMAT_H
