#pragma once

#include "GameField.h"
#include "Ship.h"
#include "RecordsTable.h"

class Game {
	GameField field; // основное поле игры

	GameField userField[2]; // поля игрока
	GameField aiField[2]; // поля AI

	Ship userShips[shipsCount]; // корабли игрока
	Ship aiShips[shipsCount]; // корабли AI

	int x0; // начальная координата для отрисовки по x
	int y0; // начальная координата для отрисовки по y

	int userScores; // очки игрока
	int aiScores; // очки AI

public:
	Game(int x0, int y0);

	void TextXY(int x, int y, int color, const char *text); // отрисовка текса с параметрами цветом color в точке (x, y)
	
	void DrawField(bool left);
	void DrawGame();
	void DrawScores();
	void PlaceShips(); // расстановка кораблей

	void FindEmptyPointLeft(int &x, int &y); // поиск свободной точки от x, y слева
	void FindEmptyPointRight(int &x, int &y); // поиск свободной точки от x, y справа
	void FindEmptyPointUp(int &x, int &y); // поиск свободной точки от x, y сверху
	void FindEmptyPointDown(int &x, int &y); // поиск свободной точки от x, y снизу

	void SetUserTarget(int &userX, int &userY);
	void SetAI_Target(int &aiX, int & aiY, bool &wasShot);

	int GetShipByCoordinates(int x, int y, bool isUser); // получение корабля по координатам

	void MakeGame();
};

