#include "stdafx.h"
#include "GameField.h"

GameField::GameField(int width, int height, int backColor) {
	this->width = width;
	this->height = height;
	this->backColor = backColor;

	cells = new Cell*[height];

	for (int i = 0; i < height; i++) {
		cells[i] = new Cell[width];

		for (int j = 0; j < width; j++) {
			cells[i][j].c = emptyChar;
			cells[i][j].color = 0;
		}
	}
}

int GameField::GetWidth() { 
	return width;
}

int GameField::GetHeight() { 
	return height;
}

void GameField::Draw(int x, int y) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cells[i][j].color + backColor);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(x + j), (short)(y + i) });
			printf("%c", cells[i][j].c);
		}
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short) (x + width), (short)(y + height) });
}

void GameField::Clear() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			cells[i][j] = { emptyChar, 0 };
}

Cell& GameField::operator()(int x, int y) {
	return cells[y][x];
}