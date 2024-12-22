#include <iostream>
#include <Windows.h> 
#include "GenerateMatrix.h"
#include "PrintMatrix.h"
#include "Moving.h"
#include "Validation.h"
#include "Game.h"

int main()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BG_BLACK);
		std::cout << "     BLUE: " << player1Score;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BG_BLACK);
		std::cout << "   GREEN: " << player2Score << std::endl;
		SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
		if (turn) { //green
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BG_BLACK);
			std::cout << "Green's turn:" << std::endl;
			SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
			Move(mat, posMat, player2RowPos, player2ColPos, turn, rows, cols, player2Score);
			if (GameOver(posMat, player1RowPos, player1ColPos, rows, cols))
				break;
		}
		else { //blue
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BG_BLACK);
			std::cout << "Blue's turn:" << std::endl;
			SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
			Move(mat, posMat, player1RowPos, player1ColPos, turn, rows, cols, player1Score);
			if (GameOver(posMat, player2RowPos, player2ColPos, rows, cols))
				break;
		}

		turn = !turn;
	}
	PrintWinner(player1Score, player2Score);
	return 0;
}