#include <iostream>
#include "GenerateMatrix.h"
#include "Operation.h"
#include <Windows.h> 
#include "PrintMatrix.h"
#include "Moving.h"

int main()
{
	srand(time(0));
	int cols = 0;
	int rows = 0;
	int player1Score = 0;
	int player2Score = 0;

	while (cols < 4 || rows < 4) {
		std::cout << "Input size of the board (RxC) (minimum 4x4): ";
		std::cin >> rows >> cols;
	}

	Operation** mat = new Operation * [rows];
	char** posMat = new char* [rows];
	CreateMatrix(mat, rows, cols);
	FillMatrix(mat, rows, cols);
	FillPositions(posMat, rows, cols);

	int player1RowPos = 0;
	int player1ColPos = 0;
	int player2RowPos = rows - 1;
	int player2ColPos = cols - 1;
	bool turn = 0; //0 is blue, 1 is green

	while (true)//handle turns
	{
		system("cls");
		PrintMatrix(mat, posMat, rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				std::cout << posMat[i][j];
			}
		}
		std::cout << "     BLUE: " << player1Score << "   GREEN: " << player2Score << std::endl;
		if (turn) { //green
			std::cout << "Green's turn:" << std::endl;
			Move(mat, posMat, player2RowPos, player2ColPos, turn, rows, cols);
		}
		else { //blue
			std::cout << "Blue's turn:" << std::endl;
			Move(mat, posMat, player1RowPos, player1ColPos, turn, rows, cols);
		}
		turn = !turn;
	}
}

