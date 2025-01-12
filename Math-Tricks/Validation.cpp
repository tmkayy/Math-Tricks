#include "Validation.h"

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
        return false; // Check out of bounds
    }
    if (myAbs(newPlayerRow - playerRow) > 1 || myAbs(newPlayerCol - playerCol) > 1) {
        return false; // Check if it's more than 1 cell away
    }
    if (posMat[newPlayerRow][newPlayerCol] != '\0') {
        return false; // Check if the cell is already taken
    }
    return true;
}

bool GameOver(char** posMat, int playerRow, int playerCol, int rows, int cols) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int newRow = playerRow + i;
            int newCol = playerCol + j;

            if (newRow >= 0 && newRow < rows &&  // check bounds and if the cell is empty
                newCol >= 0 && newCol < cols &&
                posMat[newRow][newCol] == '\0') {
                return false;
            }
        }
    }
    return true;
}
