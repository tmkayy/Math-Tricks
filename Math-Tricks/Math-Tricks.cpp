#include <iostream>
#include <Windows.h> 
#include "GenerateMatrix.h"
#include "PrintMatrix.h"
#include "Moving.h"
#include "Validation.h"
#include "Game.h"

void HandleTurn(HANDLE hConsole, Operation** mat, char** posMat, int& playerRow, int& playerCol,
	int& playerScore, int opponentRow, int opponentCol, int rows, int cols,
	bool& turn) {
	SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
	Move(mat, posMat, playerRow, playerCol, turn, rows, cols, playerScore,
		playerRow, playerCol, opponentRow, opponentCol, playerScore, playerScore, turn);
}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
	int cols = 0, rows = 0;
	int player1Score = 0, player2Score = 0;

	std::cout << "Do you want to load a saved game? (Y/N): ";
	char choice;
	std::cin >> choice;

	Operation** mat = nullptr;
	char** posMat = nullptr;
	int player1RowPos = 0, player1ColPos = 0;
	int player2RowPos = 0, player2ColPos = 0;
	bool turn = 0; // 0 is blue, 1 is green

	if (choice == 'Y' || choice == 'y') { // Load the saved game
		mat = SerializeGame(rows, cols, player1Score, player2Score, turn);
		posMat = SerializePos(rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos);

		if (!mat || !posMat) {
			std::cout << "Failed to load saved game." << std::endl;
			return -1;
		}
	}
	else {
		while (cols < 4 || rows < 4) {
			std::cout << "Input size of the board (RxC) (minimum 4x4): ";
			std::cin >> rows >> cols;
		}
		mat = new Operation * [rows];
		posMat = new char* [rows];
		CreateMatrix(mat, rows, cols);
		FillMatrix(mat, rows, cols);
		FillPositions(posMat, rows, cols);
		player2RowPos = rows - 1;
		player2ColPos = cols - 1;
	}

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
			Move(mat, posMat, player2RowPos, player2ColPos, turn, rows, cols, player2Score,
				player1RowPos, player1ColPos, player2RowPos, player2ColPos, player1Score, player2Score, turn);
			if (GameOver(posMat, player1RowPos, player1ColPos, rows, cols))
				break;
		}
		else { //blue
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BG_BLACK);
			std::cout << "Blue's turn:" << std::endl;
			SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
			Move(mat, posMat, player1RowPos, player1ColPos, turn, rows, cols, player1Score,
				player1RowPos, player1ColPos, player2RowPos, player2ColPos, player1Score, player2Score, turn);
			if (GameOver(posMat, player2RowPos, player2ColPos, rows, cols))
				break;
		}

		turn = !turn;
	}

	PrintWinner(player1Score, player2Score);

	for (int i = 0; i < rows; ++i) {
		delete[] mat[i];
		delete[] posMat[i];
	}
	delete[] mat;
	delete[] posMat;

	return 0;
}