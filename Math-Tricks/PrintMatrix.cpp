#include "PrintMatrix.h"
#include <iostream>

void PrintMatrix(Operation** mat, char** posMat, const int rows, const int cols,
    const int player1RowPos, const int player1ColPos,
    const int player2RowPos, const int player2ColPos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "      ";
    for (int j = 0; j < cols; ++j) {
        std::cout << "c" << j << "  "; //print column number and it wont be centered with double digit nums
    }
    std::cout << std::endl << std::endl << std::endl;

    for (size_t i = 0; i < rows; i++) {
        std::cout << 'r' << i << "    "; //print row number

        for (size_t j = 0; j < cols; j++) { // Print each cell
            if (i == player1RowPos && j == player1ColPos) {
                SetConsoleTextAttribute(hConsole, FG_YELLOW | BG_BLUE);
            }
            else if (i == player2RowPos && j == player2ColPos) {
                SetConsoleTextAttribute(hConsole, FG_YELLOW | BG_GREEN);
            }
            else if (posMat[i][j] == 'b') {
                SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLUE);
            }
            else if (posMat[i][j] == 'g') {
                SetConsoleTextAttribute(hConsole, FG_WHITE | BG_GREEN);
            }
            else {
                SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
            }

            std::cout << mat[i][j].operation << mat[i][j].number;
            SetConsoleTextAttribute(hConsole, FG_WHITE | BG_BLACK);
            std::cout << "  ";
        }
        std::cout << std::endl << std::endl;
    }
}