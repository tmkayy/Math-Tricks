#pragma once
#include <iostream>
#include <fstream>

const char positionFile[] = "position.txt";
const char gameFile[] = "game.txt";

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

void Deserialize(Operation** mat, char** matPos, int rows, int cols)
{
	std::ofstream ofs1(positionFile);
	std::ofstream ofs2(gameFile);

	if (!(ofs1.is_open() && ofs2.is_open()))
	{
		return;
	}

	ofs1 << rows << ' ' << cols << '\n';
	ofs2 << rows << ' ' << cols << '\n';
	for (int i = 0; i < rows; i++) //save positions
	{
		for (int j = 0; j < cols; j++)
		{
			ofs1 << matPos[i][j] << ' ';
		}
		ofs1 << '\n';
	}

	ofs1.close();

	for (int i = 0; i < rows; i++) //save positions
	{
		for (int j = 0; j < cols; j++)
		{
			ofs2 << mat[i][j].operation << ' ' << mat[i][j].number << ' ';
		}
		ofs2 << '\n';
	}
	ofs2.close();
}

char** SerializePos(int& rows, int& cols)
{
	std::ifstream ifs(positionFile);
	if (!ifs.is_open())
		return nullptr;

	ifs >> rows >> cols;
	char** posMat = new char* [rows] {};

	for (int i = 0; i < rows; i++)
	{
		posMat[i] = new char[cols];
		for (int j = 0; j < cols; ++j) {
			ifs >> posMat[i][j];
		}
	}
	ifs.close();

	return posMat;
}

Operation** SerializeGame(int& rows, int& cols)
{
	std::ifstream ifs(positionFile);
	if (!ifs.is_open())
		return nullptr;

	ifs >> rows >> cols;
	Operation** mat = new Operation * [rows] {};

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new char[cols];
		for (int j = 0; j < cols; ++j) {
			ifs >> mat[i][j].operation >> mat[i][j].number;
		}
	}
	ifs.close();

	return mat;
}