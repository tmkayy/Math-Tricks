#include "GenerateMatrix.h"
#include <cstdlib>

const int REDUCE_NUM = 2;

int getMax (int a, int b) {
	return (a > b) ? a : b;
}

char getRandomOperator() {
	const char operators[] = { '+', '*', '/', '-' };
	int randomIndex = std::rand() % 4;
	return operators[randomIndex];
}

Operation randomOp (const int rows, const int cols) {
	int randomNum = rand() % (getMax(rows, cols) - REDUCE_NUM); //larger numbers for larger matrices
	char randomChar = getRandomOperator();
	if (randomChar == '+') //get less useless cells
		randomNum++;
	randomNum = checkForDivisionBy0(randomNum, randomChar);
	return { randomChar, randomNum };
}

void seedOperation (Operation** mat, const int rows, const int cols, char op, int num) {
	bool seeded = false;
	while (!seeded) {
		int row = rand() % rows;
		int col = rand() % cols;
		if (mat[row][col].operation == 'e') {
			mat[row][col] = { op, num };
			seeded = true;
		}
	}
}

void minimalRequirements (Operation** mat, const int rows, const int cols) {
	seedOperation(mat, rows, cols, '+', rand() % (getMax(rows, cols) - REDUCE_NUM));
	seedOperation(mat, rows, cols, '-', rand() % (getMax(rows, cols) - REDUCE_NUM));
	seedOperation(mat, rows, cols, '*', 0);
	seedOperation(mat, rows, cols, '*', 2);
	seedOperation(mat, rows, cols, '/', 2);
}

void FillPositions (char** posMat, const int rows, const int cols) {
	for (int i = 0; i < rows; ++i) {
		posMat[i] = new char[cols];
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (i == 0 && j == 0)
				posMat[i][j] = 'b'; // starting position of player 1
			else if (i == rows - 1 && j == cols - 1)
				posMat[i][j] = 'g'; // starting position of player 2
			else
				posMat[i][j] = '\0';
		}
	}
}

void CreateMatrix (Operation** mat, const int rows, const int cols) {
	for (int i = 0; i < rows; i++) {
		mat[i] = new Operation[cols];
		for (size_t j = 0; j < cols; j++) {
			if ((i == 0 && j == 0) || (i == rows - 1 && j == cols - 1)) //start positions
				mat[i][j] = { '*', 0 };
			else
				mat[i][j] = { 'e', 0 }; //fill matrix with default operators (e for empty)
		}
	}
	minimalRequirements (mat, rows, cols);
}

void FillMatrix (Operation** mat, const int rows, const int cols) {
	for (int i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			//fill matrix with random operators if empty
			if (mat[i][j].operation == 'e') {
				mat[i][j] = randomOp(rows, cols);
			}
		}
	}
}
