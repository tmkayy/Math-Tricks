#pragma once

int checkForDivisionBy0(int num, char op) {
	if (op == '/' && num == 0)
		return num + 1;
	else
		return num;
}

int myAbs(int value) {
	return (value < 0) ? -value : value;
}

bool ValidMove(char** posMat, int playerRow, int playerCol, int newPlayerRow, int newPlayerCol, int rows, int cols) {
	if (newPlayerRow < 0 || newPlayerRow >= rows ||
		newPlayerCol < 0 || newPlayerCol >= cols) {
		return false;
	}//check out of bounds
	if (myAbs(newPlayerRow - playerRow) > 1 || myAbs(newPlayerCol - playerCol) > 1) {
		return false;
	}//check if its 1 away
	if (posMat[newPlayerRow][newPlayerCol] != '\0') {
		return false;
	}//check if the cell already taken

	return true;
}