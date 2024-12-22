#include <iostream>
#include "GenerateMatrix.h";
#include "Operation.h"

int main()
{
	srand(time(0));
	int cols = 0;
	int rows = 0;
	while (cols < 4 && rows < 4) {
		std::cout << "Input size of the board (RxC) (minimum 4x4):";
		std::cin >> rows >> cols;
	}
	Operation** matrix = new Operation * [rows];
	CreateMatrix(matrix, rows, cols);
}

