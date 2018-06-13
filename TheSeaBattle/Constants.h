#pragma once

#include "Colors.h"

const int fieldWidth = 80; // ширина поля
const int fieldHeight = 15; // высота поля

const int fieldX0 = 3; // смещение от левого края
const int fieldY0 = 3; // смещение сверху

const int gameFieldWidth = 10; // ширина игрового поля
const int gameFieldHeight = 10; // высота игрового поля

const char emptyChar = ' '; // символ пустой клетки
const char shipChar = '#'; // символ корабля
const char targetChar = 'x'; // символ цели
const char boomChar = '@'; // символ попадания (взрыва)
const char failChar = '-'; // символ промаха

const int fieldBackgroundColor = BACKGROUND_BLUE; // цвет фона
const int shipColor = yellow + FOREGROUND_INTENSITY; // цвет корабля
const int targetColor = red + FOREGROUND_INTENSITY; // цвет цели
const int boomColor = red + FOREGROUND_INTENSITY; // цвет взрыва
const int diedColor = black + FOREGROUND_INTENSITY; // цвет убитого корабля
const int failColor = cyan; // цвет промаха

const int info_color = green; // цвет информации
const int scores_color = red; // цвет информации об очках

const int shipsCount = 10; // количество кораблей
const int shipLengths[shipsCount] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 }; // размеры кораблей

const int maxScores = 20; // максимальное число очков

const int margin = 17; // смещение правого поля
const int text_x = 30; // смещение правого текста

// коды кнопок
const int key_R = 82;
const int key_S = 83;
const int key_X = 88;

struct Cell {
	char c;
	int color;
};