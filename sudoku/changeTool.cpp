#include "stdafx.h"
using namespace std;

changeTool::changeTool(vector<vector<int>> mat)
{
	// memcpy(&Mat[0][0], &mat[0][0], 9 * 9 * sizeof(int)); //get initial sudoku matrix
	/*	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", Mat[i][j]);
		}
		printf("\n");
	}*/
	Mat = mat;
}

// swap the position of num1 and num2
void changeTool::swapNumber(int num1, int num2) 
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			Mat[i][j] = Mat[i][j] == num1 ? num2 : (Mat[i][j] == num2 ? num1 : Mat[i][j]);
		}
	}
}

// swap row1 and row2 in "wide row" i, a "wide row" consists of three normal rows
void changeTool::swapRow(int i, int row1, int row2)
{
	row1 = i * 3 + row1 % 3; 
	row2 = i * 3 + row2 % 3; 
	if (row1 != row2)
	{
		swap(Mat[row1], Mat[row2]);
	}
}

// swap col1 and col2 in "wide col" i, a "wide col" consists of three normal cols
void changeTool::swapCol(int i, int col1, int col2)
{
	col1 = i * 3 + col1 % 3; 
	col2 = i * 3 + col2 % 3; 
	if (col1 != col2)
	{
		for (int i = 0; i < 9; i++)
		{
			if(Mat[i][col1] != Mat[i][col2])
			{
				swap(Mat[i][col1], Mat[i][col2]);
			}		
		}
	}
}

// swap 'wide row'1 and 'wide row'2
void changeTool::swap3Row(int squ1, int squ2) 
{
	for (int i = 0; i < 3; i++)
	{
		swap(Mat[squ1 * 3 + i], Mat[squ2 * 3 + i]);
	}
}

// swap 'wide col'1 and 'wide col'2
void changeTool::swap3Col(int squ1, int squ2)
{
	int a, b;
	for (int i = 0; i < 3; i++)
	{
		a = squ1 * 3 + i;
		b = squ2 * 3 + i;
		for (int j = 0; j < 9; j++)
		{
			if(Mat[j][a] != Mat[j][b])
			{
				swap(Mat[j][a], Mat[j][b]);
			}		
		}
	}
}

// make sure the 0,0 element in matrix is '5'
void changeTool::check()
{
	if (Mat[0][0] != 5)
	{
		swapNumber(5, Mat[0][0]); //if not '5', swap it with another '5'
	}
}

// return value in matrix at postion (a, b)
int changeTool::getMat(int a, int b)
{
	return Mat[a][b];
}