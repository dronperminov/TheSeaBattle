#pragma once

#include "Constants.h"
#include "GameField.h"

class Ship {
	int x; // координата Х корабля
	int y; // координата У корабля
	int state; // положение корабля на поле (вертикально (0) / горизонтально (1))
	int length; // длина корабля
	int count; // число сбитых клеток

public:
	Ship(int length = 0);

	void Draw(GameField &gameField, bool clear = false);
	void DrawBorder(GameField &gameField);
	void Die(GameField &gameField);

	void MoveLeft(GameField &gameField);
	void MoveRight(GameField &gameField);
	void MoveUp(GameField &gameField);
	void MoveDown(GameField &gameField);

	void AutoPlace(GameField &gameField);
	void Place(GameField &gameField);

	bool Boom(); // падание в корабль (возращает был ли убит корабль)

	bool CanSet(int x, int y, GameField &gameField);
	bool CheckCoordinates(int x, int y); // проверка, что этот корабль находится в точке x, y
};

