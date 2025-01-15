#pragma once

#include <iostream>
#include <fstream>
#include "Operation.h"
#include <Windows.h>

extern const char positionFile[];
extern const char gameFile[];

void PrintWinner (int player1Score, int player2Score);

void Deserialize (Operation** mat, char** matPos, int rows, int cols,
	int player1row, int player1col, int player2row, int player2col,
	int player1score, int player2score, bool turn);
 
char** SerializePos (int& rows, int& cols, int& player1row, int& player1col, int& player2row, int& player2col);

Operation** SerializeGame (int& rows, int& cols, int& player1score, int& player2score, bool& turn);
