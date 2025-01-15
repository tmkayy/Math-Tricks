#include "Moving.h"
#include <iostream>
#include <cstdlib>

int charToInt (char c) {
	return c - '0';
}

void ManipulateScore (Operation op, int& score) {
	switch (op.operation)
	{
		case '+': score += op.number; break;
		case '-': score -= op.number; break;
		case '*': score *= op.number; break;
		case '/': score /= op.number; break;
	}
}

int stringToInt (const char* str) {
	int result = 0;
	bool isNegative = false;

	while (*str == ' ') { //in case theres white spaces
		str++;
	}
	if (*str == '-') {
		isNegative = true;
		str++;
	}
	while (*str >= '0' && *str <= '9') {
		result = result * 10 + charToInt(*str);
		str++;
	}

	return (isNegative ? -result : result);
}

void Move (Operation** mat, char** posMat,
	int& playerRow, int& playerCol,
	bool player, const int rows, const int cols, int& score,
	int player1Row, int player1Col, int player2Row, int player2Col,
	int& player1Score, int& player2Score, bool turn) {
	int nextMoveRow = 0;
	int nextMoveCol = 0;
	char input[MAX_LENGTH];

	while (true) {
		std::cout << "Enter your next move (row and column 1 cell away or \"S\" to save game and quit):" << std::endl;
		std::cout << "Row = ";
		std::cin >> input;

		if (input[0] == 'S' || input[0] == 's') {
			std::cout << "Saving game and quitting..." << std::endl;
			Deserialize(mat, posMat, rows, cols, player1Row, player1Col, player2Row, player2Col, player1Score, player2Score, turn);
			exit(0);
		}

		nextMoveRow = stringToInt(input);

		std::cout << "Column = ";
		std::cin >> nextMoveCol;

		if (ValidMove(posMat, playerRow, playerCol, nextMoveRow, nextMoveCol, rows, cols)) {
			break;
		}
	}

	playerRow = nextMoveRow;
	playerCol = nextMoveCol;
	posMat[playerRow][playerCol] = (player == 0) ? 'b' : 'g';
	ManipulateScore(mat[playerRow][playerCol], score);
}
