#pragma once
#include <iostream>
#include "Operation.h"
#include "Validation.h"

int getMax(int a, int b) {
	return (a > b) ? a : b;
}

char getRandomOperator() {
	const char operators[] = { '+', '*', '/', '-' };
	int randomIndex = std::rand() % 4;
	return operators[randomIndex];
}

Operation randomOp(const int rows, const int cols) {
	int randomNum = rand() % (getMax(rows, cols) - 2); //larger nums for larger matrix
	char randomChar = getRandomOperator();
	randomNum = checkForDivisionBy0(randomNum, randomChar);
	return { randomChar, randomNum };
}

void seedOperation(Operation** mat, const int rows, const int cols, char op, int num) {
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

void minimalRequirements(Operation** mat, const int rows, const int cols) {
	seedOperation(mat, rows, cols, '+', rand() % (getMax(rows, cols) - 2));
	seedOperation(mat, rows, cols, '-', rand() % (getMax(rows, cols) - 2));
	seedOperation(mat, rows, cols, '*', 0);
	seedOperation(mat, rows, cols, '*', 2);
	seedOperation(mat, rows, cols, '/', 2);
}

void CreateMatrix(Operation** mat, const int rows, const int cols) {
	for (int i = 0; i < rows; i++)
	{
		mat[i] = new Operation[cols];
		for (size_t j = 0; j < cols; j++)
		{
			//fill matrix with default operators (e for empty)
			mat[i][j] = {'e', 0};
		}
	}
	minimalRequirements(mat, rows, cols);
}

void FillMatrix(Operation** mat, const int rows, const int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			//fill matrix with random operators
			if (mat[i][j].operation == 'e')
			{
				mat[i][j] = randomOp(rows, cols);
			}
		}
	}
}