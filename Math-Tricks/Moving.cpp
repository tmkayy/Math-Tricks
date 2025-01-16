/**
*
* Solution to course project #2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Haralampy Slavkov
* @idnumber 2MI0600476* @compiler VC
*
* <file containing the functions for player moves>
*
*/

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


void Move (Operation** mat, char** posMat,
	int& playerRow, int& playerCol,
	bool player, const int rows, const int cols, int& score,
	int player1Row, int player1Col, int player2Row, int player2Col,
	int& player1Score, int& player2Score, bool turn) {
	int nextMoveRow = 0;
	int nextMoveCol = 0;

	while (true) {
		std::cout << "Enter your next move (row and column 1 cell away or \"-1\" on row to save game and quit):" << std::endl;
		std::cout << "Row = ";
		std::cin >> nextMoveRow;

		if (nextMoveRow == -1) {
			std::cout << "Saving game and quitting..." << std::endl;
			Deserialize(mat, posMat, rows, cols, player1Row, player1Col, player2Row, player2Col, player1Score, player2Score, turn);
			exit(0);
		}

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
