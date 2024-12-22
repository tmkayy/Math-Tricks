#pragma once

int checkForDivisionBy0(int num, char op) {
	if (op == '/' && num == 0)
		return num + 1;
	else
		return num;
}