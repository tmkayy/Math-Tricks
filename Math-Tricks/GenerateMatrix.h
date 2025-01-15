#pragma once

#include "Operation.h"
#include "Validation.h"

int getMax (int a, int b);

char getRandomOperator();

Operation randomOp (const int rows, const int cols);

void seedOperation (Operation** mat, const int rows, const int cols, char op, int num);

void minimalRequirements (Operation** mat, const int rows, const int cols);

void FillPositions (char** posMat, const int rows, const int cols);

void CreateMatrix (Operation** mat, const int rows, const int cols);

void FillMatrix (Operation** mat, const int rows, const int cols);
