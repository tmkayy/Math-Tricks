#pragma once
#include <iostream>
#include "Operation.h"
#include "Validation.h"

void Move(Operation** mat, char** posMat, int& playerRow, int& playerCol, bool player, const int rows, const int cols) {
	int nextMoveRow = 0;
	int nextMoveCol = 0;
	while (true)
	{
		std::cout << "Enter your next move (1 cell away):" << std::endl;
		std::cout << "Row = ";
		std::cin >> nextMoveRow;
		std::cout << "Column = ";
		std::cin >> nextMoveCol;
		if (ValidMove(posMat, playerRow, playerCol, nextMoveRow, nextMoveCol, rows, cols))
			break;
	}
	playerRow = nextMoveRow;
	playerCol = nextMoveCol;
	posMat[playerRow][playerCol] = (player == 0) ? 'b' : 'g';
}