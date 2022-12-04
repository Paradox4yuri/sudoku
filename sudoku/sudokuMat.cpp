#include "stdafx.h"
using namespace std;

sudokuMat::sudokuMat()
{
	srand((unsigned)time(NULL)); // generate random seed
}

vector<vector<int>> sudokuMat::randomMat()
{	
	ofstream out;
	out.open("./sudoku.txt", ios::app);
	set<string> checkSet;

	changeTool ct(initMat);			// transform tools. includes swapRow, swapNumber, etc.
	int changeTime = changeTimes; // times to transform matrix
	int changeOption; // random change option
	int i, a, b; // random parameters
	
	while (changeTime--)
	{
		changeOption = rand() % 5;
		switch (changeOption)
		{
		case 0:                             //transform type 0
			a = rand() % 9 + 1;
			b = rand() % 9 + 1;
			if (a != b) ct.swapNumber(a, b);
			break;
		case 1:                             //transform type 1
			i = rand() % 3;
			a = rand();
			b = rand();
			if (a != b) ct.swapRow(i, a, b);
			break;
		case 2:                             //transform type 2
			i = rand() % 3;
			a = rand();
			b = rand();
			if (a != b) ct.swapCol(i, a, b);
			break;
		case 3:                              //transform type 3
			a = rand() % 3;
			b = rand() % 3;
			if (a != b)ct.swap3Row(a, b);
			break;
		case 4:                              //transform type 4
			a = rand() % 3;
			b = rand() % 3;
			if (a != b) ct.swap3Col(a, b);
			break;
		default:
			a = rand() % 9 + 1;
			b = rand() % 9 + 1;
			if (a != b) ct.swapNumber(a, b);
			break;
		}
	}
	ct.check(); // make sure the first element in matrix is 5
	return ct.Mat;
}
