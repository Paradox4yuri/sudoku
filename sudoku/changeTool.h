#pragma once
#ifndef CHANGETOOL_H
#define CHANGETOOL_H

#include <vector>
using namespace std;

// transformation tool to transform original source matrix
class changeTool
{
public:
	changeTool(vector<vector<int>> mat);                 
	void swapNumber(int num1,int num2);       // swap the position of num1 and num2
	void swapRow(int i, int row1, int row2);  // swap row1 and row2 in "wide row" i, a "wide row" consists of three normal rows
	void swapCol(int i, int col1, int col2);  // swap col1 and col2 in "wide col" i, a "wide col" consists of three normal cols
	void swap3Row(int squ1, int squ2);        // swap 'wide row'1 and 'wide row'2
	void swap3Col(int squ1, int squ2);        // swap 'wide col'1 and 'wide col'2
	void check();                             // make sure the 0,0 element in matrix is '5'
	int getMat(int a, int b);                 // return value in matrix at postion (a, b)

	vector<vector<int>> Mat;
};

#endif //!CHANGETOOL_H
