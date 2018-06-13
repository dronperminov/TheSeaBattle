#include "stdafx.h"
#include "Field.h"


Field::Field(int width, int height) {
	this->width = width;
	this->height = height;

	cells = new Cell*[height];

	for (int i = 0; i < height; i++) {
		cells[i] = new Cell[width];

		for (int j = 0; j < width; j++) {
			cells[i][j].c = emptyChar;
			cells[i][j].color = fieldBackgroundColor;
		}
	}
}

Field::~Field() {
	for (int i = 0; i < height; i++)
		delete[] cells[i];

	delete[] cells;
}
