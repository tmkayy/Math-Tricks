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
* <file containing the functions for the flow of the game>
*
*/

#include <iostream>
#include <Windows.h> 
#include "GenerateMatrix.h"
#include "PrintMatrix.h"
#include "Moving.h"
#include "Validation.h"
#include "Game.h"

const int MIN_SIZE = 4;
const int MAX_SIZE = 25;
const int BLACK_BG = 0;

bool LoadGame(Operation**& mat, char**& posMat, int& rows, int& cols,
	int& player1RowPos, int& player1ColPos, int& player2RowPos, int& player2ColPos,
	int& player1Score, int& player2Score, bool& turn) {
	mat = SerializeGame(rows, cols, player1Score, player2Score, turn);
	posMat = SerializePos(rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos);

	return mat != nullptr && posMat != nullptr;
}

void InitializeGame(Operation**& mat, char**& posMat, int& rows, int& cols, int& player1RowPos, int& player1ColPos,
	int& player2RowPos, int& player2ColPos, int& player1Score, int& player2Score, bool& turn) {
	std::cout << "Do you want to load a saved game? (Y/N): ";
	char choice;
	std::cin >> choice;

	if (choice == 'Y' || choice == 'y') { //load game
		if (!LoadGame(mat, posMat, rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos,
			player1Score, player2Score, turn)) {
			std::cerr << "Failed to load saved game. Exiting..." << std::endl;
			exit(-1);
		}
	}
	else {
		while (cols < MIN_SIZE || cols > MAX_SIZE || rows < MIN_SIZE || rows > MAX_SIZE) {
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
}

void HandleTurns(Operation** mat, char** posMat, int rows, int cols, int& player1RowPos, int& player1ColPos,
	int& player2RowPos, int& player2ColPos, int& player1Score, int& player2Score, bool& turn) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) { //handle turns
		system("cls");
		PrintMatrix(mat, posMat, rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos);

		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BLACK_BG);
		std::cout << "   BLUE: " << player1Score;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BLACK_BG);
		std::cout << "   GREEN: " << player2Score << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		//take a turn
		if (turn) { //green
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | BLACK_BG);
			std::cout << "Green's turn:" << std::endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Move(mat, posMat, player2RowPos, player2ColPos, turn, rows, cols, player2Score, player1RowPos, player1ColPos,
				player2RowPos, player2ColPos, player1Score, player2Score, turn);
			if (GameOver(posMat, player1RowPos, player1ColPos, rows, cols)) break;
		}
		else { //blue
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BLACK_BG);
			std::cout << "Blue's turn:" << std::endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			Move(mat, posMat, player1RowPos, player1ColPos, turn, rows, cols, player1Score, player1RowPos, player1ColPos,
				player2RowPos, player2ColPos, player1Score, player2Score, turn);
			if (GameOver(posMat, player2RowPos, player2ColPos, rows, cols)) break;
		}

		turn = !turn;
	}
}

void CleanUp(Operation** mat, char** posMat, int rows) {
	for (int i = 0; i < rows; ++i) {
		delete[] mat[i];
		delete[] posMat[i];
	}
	delete[] mat;
	delete[] posMat;
}

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(static_cast<unsigned>(time(0)));

	int rows = 0, cols = 0;
	int player1Score = 0, player2Score = 0;
	int player1RowPos = 0, player1ColPos = 0;
	int player2RowPos = 0, player2ColPos = 0;
	bool turn = false; // 0 = blue, 1 = green

	Operation** mat = nullptr;
	char** posMat = nullptr;

	InitializeGame(mat, posMat, rows, cols, player1RowPos, player1ColPos, player2RowPos,
		player2ColPos, player1Score, player2Score, turn);

	HandleTurns(mat, posMat, rows, cols, player1RowPos, player1ColPos, player2RowPos, player2ColPos,
		player1Score, player2Score, turn);

	PrintWinner(player1Score, player2Score);

	CleanUp(mat, posMat, rows);

	return 0;
}