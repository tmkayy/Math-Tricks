#pragma once

void PrintWinner(int player1Score, int player2Score) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (player1Score > player2Score) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BG_BLACK);
		std::cout << "   BLUE WON";
	}
	else if (player2Score > player1Score) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BG_BLACK);
		std::cout << "   GREEN WON";
	}
	else {
		SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
		std::cout << "   GAME ENDED IN A DRAW";
	}
	SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
}