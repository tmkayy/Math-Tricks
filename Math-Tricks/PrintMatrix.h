#pragma once
#include <iostream>
#include <Windows.h>
#include "Operation.h"

const int BG_BLUE = BACKGROUND_BLUE;
const int BG_GREEN = BACKGROUND_GREEN;
const int BG_BLACK = 0;
const int FG_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const int FG_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void PrintMatrix(Operation** mat, char** posMat, const int rows, const int cols,
	const int player1RowPos, const int player1ColPos,
	const int player2RowPos, const int player2ColPos) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++) //print operations
		{
			if (i == player1RowPos && j == player1ColPos) {
				SetConsoleTextAttribute(hConsole, FG_YELLOW | BG_BLUE);
			}
			else if (i == player2RowPos && j == player2ColPos) {
				SetConsoleTextAttribute(hConsole, FG_YELLOW | BG_GREEN);
			}
			else if (posMat[i][j] == 'b') {
				SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLUE);
			}
			else if (posMat[i][j] == 'g') {
				SetConsoleTextAttribute(hConsole, FG_WHITE | BG_GREEN);
			}
			else {
				SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
			}
			std::cout << mat[i][j].operation << mat[i][j].number;
			SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
			std::cout << "  ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}