#pragma once

#include "Operation.h"
#include "Validation.h"
#include "Game.h"

const int MAX_LENGTH = 10;

int charToInt (char c);

void ManipulateScore (Operation op, int& score);

int stringToInt (const char* str);

void Move (Operation** mat, char** posMat,
	int& playerRow, int& playerCol,
	bool player, const int rows, const int cols, int& score,
	int player1Row, int player1Col, int player2Row, int player2Col,
	int& player1Score, int& player2Score, bool turn);
