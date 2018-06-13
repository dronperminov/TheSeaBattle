#include "stdafx.h"

#include "Constants.h"
#include "Ship.h"

Ship::Ship(int length) {
	this->length = length;

	x = 0;
	y = 0;
	state = 0;
	count = 0;
}

void Ship::Draw(GameField &gameField, bool clear) {
	for (int i = 0; i < length; i++)
		gameField(x + state * i, y + !state * i) = { clear ? emptyChar : shipChar, shipColor };
}

void Ship::DrawBorder(GameField &gameField) {
	int w = gameField.GetWidth();
	int h = gameField.GetHeight();

	int startX = x - 1;
	int startY = y - 1;

	int endX = state ? x + length : x + 1;
	int endY = state ? y + 1 : y + length;

	for (int x0 = startX; x0 <= endX; x0++) {
		if (x0 < 0 || x0 >= w)
			continue;

		for (int y0 = startY; y0 <= endY; y0++) {
			if (y0 < 0 || y0 >= h)
				continue;

			if ((state && x0 >= x && x0 < x + length && y0 == y) || (!state && y0 >= y && y0 < y + length && x0 == x)) {
				gameField(x0, y0) = { shipChar, diedColor };
			}
			else {
				gameField(x0, y0) = { failChar, failColor };
			}
		}
	}
}

void Ship::Die(GameField &gameField) {
	for (int i = 0; i < length; i++)
		gameField(x + state * i, y + !state * i) = { shipChar, diedColor };

	DrawBorder(gameField);
}

void Ship::MoveLeft(GameField &gameField) {
	if (CanSet(x - 1, y, gameField)) {
		x--;
	}
	else {
		int x0 = x - 2;

		while (x0 > 0 && !CanSet(x0, y, gameField))
			x0--;

		if (x0 > 0)
			x = x0;
	}
}

void Ship::MoveRight(GameField &gameField) {
	if (CanSet(x + 1, y, gameField)) {
		x++;
	}
	else {
		int x0 = x + 2;
		while (x0 < 10 && !CanSet(x0, y, gameField))
			x0++;

		if (x0 < 10)
			x = x0;
	}
}

void Ship::MoveUp(GameField &gameField) {
	if (CanSet(x, y - 1, gameField)) {
		y--;
	}
	else {
		int y0 = y - 2;
		while (y0 > 0 && !CanSet(x, y0, gameField))
			y0--;

		if (y0 > 0)
			y = y0;
	}
}

void Ship::MoveDown(GameField &gameField) {
	if (CanSet(x, y + 1, gameField)) {
		y++;
	}
	else {
		int y0 = y + 2;
		while (y0 < 10 && !CanSet(x, y0, gameField))
			y0++;

		if (y0 < 10)
			y = y0;
	}
}

void Ship::AutoPlace(GameField &gameField) {
	state = rand() % 2; // положение - вертикальное (0) или горизонтальное (1)

	do {
		x = rand() % (10 - length * state);
		y = rand() % (10 - length * !state);
	} while (!CanSet(x, y, gameField));

	for (int i = 0; i < length; i++)
		gameField(x + state * i, y + (!state) * i) = { shipChar, shipColor };
}

void Ship::Place(GameField &gameField) {
	bool find = false;
	bool changed = false;

	for (int i = 0; i < gameField.GetHeight() && !find; i++) {
		for (int j = 0; j < gameField.GetWidth() && !find; j++) {
			if (CanSet(j, i, gameField)) {
				x = j;
				y = i;
				find = true;
			}
		}
	}

	Draw(gameField);
	gameField.Draw(fieldX0, fieldY0);

	while (!GetAsyncKeyState(VK_SPACE)) {
		Draw(gameField, true);

		if (GetAsyncKeyState(VK_LEFT)) {
			MoveLeft(gameField);
			changed = true;

			while (GetAsyncKeyState(VK_LEFT))
				Sleep(20);
		}
		
		if (GetAsyncKeyState(VK_RIGHT)) {
			MoveRight(gameField);
			changed = true;

			while (GetAsyncKeyState(VK_RIGHT))
				Sleep(20);
		}
		
		if (GetAsyncKeyState(VK_UP)) {
			MoveUp(gameField);
			changed = true;

			while (GetAsyncKeyState(VK_UP))
				Sleep(20);
		}
		
		if (GetAsyncKeyState(VK_DOWN)) {
			MoveDown(gameField);
			changed = true;

			while (GetAsyncKeyState(VK_DOWN))
				Sleep(20);
		}
		
		if (GetAsyncKeyState(key_R)) {
			state = !state;

			if (!CanSet(x, y, gameField)) {
				state = !state;
			}
			else {
				changed = true;
			}

			while (GetAsyncKeyState(key_R))
				Sleep(20);
		}

		Draw(gameField);

		if (changed) {
			gameField.Draw(fieldX0, fieldY0);
			changed = false;
		}

		Sleep(100);
	}

	while (GetAsyncKeyState(VK_SPACE))
		Sleep(20);
}

// падание в корабль (возращает был ли убит корабль)
bool Ship::Boom() {
	count++;

	return count >= length;
}

bool Ship::CanSet(int x, int y, GameField &gameField) {
	int w = gameField.GetWidth();
	int h = gameField.GetHeight();

	if (x < 0 || x >= w || y < 0 || y >= h)
		return false;

	if (!state && (y + length > h))
		return false;

	if (state && (x + length > w))
		return false;

	int startX = x - 1;
	int startY = y - 1;

	int endX = state ? x + length : x + 1;
	int endY = state ? y + 1 : y + length;

	for (int x0 = startX; x0 <= endX; x0++) {
		if (x0 < 0 || x0 >= w)
			continue;

		for (int y0 = startY; y0 <= endY; y0++) {
			if (y0 < 0 || y0 >= h)
				continue;

			if (gameField(x0, y0).c != emptyChar)
				return false;
		}
	}

	return true;
}

// проверка, что этот корабль находится в точке x, y
bool Ship::CheckCoordinates(int x, int y) {
	for (int i = 0; i < length; i++)
		if ((this->x + state * i) == x && (this->y + !state * i) == y)
			return true;

	return false;
}