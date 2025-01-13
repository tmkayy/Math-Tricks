#include "Game.h"

const char positionFile[] = "position.txt";
const char gameFile[] = "game.txt";

void PrintWinner(int player1Score, int player2Score) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (player1Score > player2Score) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | 0);
		std::cout << "   BLUE WON";
	}
	else if (player2Score > player1Score) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | 0);
		std::cout << "   GREEN WON";
	}
	else {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << "   GAME ENDED IN A DRAW";
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Deserialize(Operation** mat, char** matPos, int rows, int cols, int player1row, int player1col, int player2row, int player2col,
	int player1score, int player2score, bool turn) //save game
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
	ofs1 << player1row << ' ' << player1col << ' ' << player2row << ' ' << player2col;// save positions
	ofs1.close();

	for (int i = 0; i < rows; i++) //save game board
	{
		for (int j = 0; j < cols; j++)
		{
			ofs2 << mat[i][j].operation << ' ' << mat[i][j].number << ' ';
		}
		ofs2 << '\n';
	}
	ofs2 << player1score << ' ' << player2score << std::endl; //save scores
	ofs2 << turn;
	ofs2.close();
}

char** SerializePos(int& rows, int& cols, int& player1row, int& player1col, int& player2row, int& player2col)
{//load positions matrix and positions
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
	ifs >> player1row >> player1col >> player2row >> player2col;
	ifs.close();

	return posMat;
}

Operation** SerializeGame(int& rows, int& cols, int& player1score, int& player2score, bool& turn)
{//load board, scores and turn
	std::ifstream ifs(gameFile);
	if (!ifs.is_open())
		return nullptr;

	ifs >> rows >> cols;
	Operation** mat = new Operation * [rows] {};

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new Operation[cols];
		for (int j = 0; j < cols; ++j) {
			ifs >> mat[i][j].operation >> mat[i][j].number;
		}
	}
	ifs >> player1score >> player2score;
	ifs >> turn;
	ifs.close();

	return mat;
}
