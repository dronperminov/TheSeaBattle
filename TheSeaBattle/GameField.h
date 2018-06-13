#pragma once

#include "Constants.h"
#include "Colors.h"

class GameField {
	int width;
	int height;
	int backColor;

	Cell **cells;

public:
	GameField(int width = gameFieldWidth, int height = gameFieldHeight, int backColor = black);

	int GetWidth();
	int GetHeight();

	void Draw(int x = 0, int y = 0);
	void Clear();

	Cell& operator()(int x, int y);
};

