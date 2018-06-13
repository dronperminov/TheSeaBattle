#pragma once

#include "Colors.h"

const int fieldWidth = 80; // ������ ����
const int fieldHeight = 15; // ������ ����

const int fieldX0 = 3; // �������� �� ������ ����
const int fieldY0 = 3; // �������� ������

const int gameFieldWidth = 10; // ������ �������� ����
const int gameFieldHeight = 10; // ������ �������� ����

const char emptyChar = ' '; // ������ ������ ������
const char shipChar = '#'; // ������ �������
const char targetChar = 'x'; // ������ ����
const char boomChar = '@'; // ������ ��������� (������)
const char failChar = '-'; // ������ �������

const int fieldBackgroundColor = BACKGROUND_BLUE; // ���� ����
const int shipColor = yellow + FOREGROUND_INTENSITY; // ���� �������
const int targetColor = red + FOREGROUND_INTENSITY; // ���� ����
const int boomColor = red + FOREGROUND_INTENSITY; // ���� ������
const int diedColor = black + FOREGROUND_INTENSITY; // ���� ������� �������
const int failColor = cyan; // ���� �������

const int info_color = green; // ���� ����������
const int scores_color = red; // ���� ���������� �� �����

const int shipsCount = 10; // ���������� ��������
const int shipLengths[shipsCount] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // ������� ��������

const int maxScores = 20; // ������������ ����� �����

const int margin = 17; // �������� ������� ����
const int text_x = 30; // �������� ������� ������

// ���� ������
const int key_R = 82;
const int key_S = 83;
const int key_X = 88;

struct Cell {
	char c;
	int color;
};