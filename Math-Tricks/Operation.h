#pragma once
#include <iostream>

struct Operation {
	char operation; // (+, -, *, /)
	int number;

	void ManipulateScore(int& score) {
		switch (operation)
		{
		case '+': score += number; break;
		case '-': score -= number; break;
		case '*': score *= number; break;
		case '/': score /= number; break;
		}
	}
};