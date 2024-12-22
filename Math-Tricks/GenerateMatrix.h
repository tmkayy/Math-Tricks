#pragma once
#include <iostream>
#include "Operation.h"

int getMax(int a, int b) {
	return (a > b) ? a : b;
}

char getRandomOperator() {
	const char operators[] = { '+', '*', '/', '-' };
	int randomIndex = std::rand() % 4;
	return operators[randomIndex];
}

void CreateMatrix(Operation** mat, const int rows, const int cols) {
	srand(time(0)); //seed for randomizer

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new Operation[cols];
		for (size_t j = 0; j < cols; j++)
		{
			//fill matrix with random operators
			int randomNum = rand() % (getMax(rows, cols) - 2); //larger nums for larger matrix
			char randomChar = getRandomOperator();
			mat[i][j] = {randomChar, randomNum};
		}
	}
}