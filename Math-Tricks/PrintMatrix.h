#pragma once

#include <Windows.h>
#include "Operation.h"

const int BG_BLUE = BACKGROUND_BLUE;
const int BG_GREEN = BACKGROUND_GREEN;
const int BG_BLACK = 0;
const int FG_RED = FOREGROUND_RED;
const int FG_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void PrintMatrix (Operation** mat, char** posMat, const int rows, const int cols,
	const int player1RowPos, const int player1ColPos,
	const int player2RowPos, const int player2ColPos);
