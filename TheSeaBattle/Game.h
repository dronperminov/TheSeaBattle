#pragma once

#include "GameField.h"
#include "Ship.h"
#include "RecordsTable.h"

class Game {
	GameField field; // �������� ���� ����

	GameField userField[2]; // ���� ������
	GameField aiField[2]; // ���� AI

	Ship userShips[shipsCount]; // ������� ������
	Ship aiShips[shipsCount]; // ������� AI

	int x0; // ��������� ���������� ��� ��������� �� x
	int y0; // ��������� ���������� ��� ��������� �� y

	int userScores; // ���� ������
	int aiScores; // ���� AI

public:
	Game(int x0, int y0);

	void TextXY(int x, int y, int color, const char *text); // ��������� ����� � ����������� ������ color � ����� (x, y)
	
	void DrawField(bool left);
	void DrawGame();
	void DrawScores();
	void PlaceShips(); // ����������� ��������

	void FindEmptyPointLeft(int &x, int &y); // ����� ��������� ����� �� x, y �����
	void FindEmptyPointRight(int &x, int &y); // ����� ��������� ����� �� x, y ������
	void FindEmptyPointUp(int &x, int &y); // ����� ��������� ����� �� x, y ������
	void FindEmptyPointDown(int &x, int &y); // ����� ��������� ����� �� x, y �����

	void SetUserTarget(int &userX, int &userY);
	void SetAI_Target(int &aiX, int & aiY, bool &wasShot);

	int GetShipByCoordinates(int x, int y, bool isUser); // ��������� ������� �� �����������

	void MakeGame();
};

