#pragma once

#include "Constants.h"
#include "GameField.h"

class Ship {
	int x; // ���������� � �������
	int y; // ���������� � �������
	int state; // ��������� ������� �� ���� (����������� (0) / ������������� (1))
	int length; // ����� �������
	int count; // ����� ������ ������

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

	bool Boom(); // ������� � ������� (��������� ��� �� ���� �������)

	bool CanSet(int x, int y, GameField &gameField);
	bool CheckCoordinates(int x, int y); // ��������, ��� ���� ������� ��������� � ����� x, y
};

