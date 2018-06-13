#include "stdafx.h"
#include "Game.h"

Game::Game(int x0, int y0) {
	field = GameField(fieldWidth, fieldHeight);

	userField[0] = GameField(gameFieldWidth, gameFieldHeight, fieldBackgroundColor);
	userField[1] = GameField(gameFieldWidth, gameFieldHeight, fieldBackgroundColor);

	aiField[0] = GameField(gameFieldWidth, gameFieldHeight, fieldBackgroundColor);
	aiField[1] = GameField(gameFieldWidth, gameFieldHeight, fieldBackgroundColor);

	for (int i = 0; i < shipsCount; i++) {
		userShips[i] = Ship(shipLengths[i]);
		aiShips[i] = Ship(shipLengths[i]);
	}

	this->x0 = x0;
	this->y0 = y0;

	userScores = 0;
	aiScores = 0;
}

// отрисовка текса с параметрами цветом color в точке (x, y)
void Game::TextXY(int x, int y, int color, const char *text) {
	for (int i = 0; text[i]; i++) {
		field(x + i, y) = { text[i], color };

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(x + i), (short)(y) });
		printf("%c", text[i]);
	}
}

void Game::DrawField(bool left) {
	for (int i = 0; i < 10; i++) {
		field(x0 + i + left * margin, y0 - 2) = { (char)('A' + i), white }; // горизонтальные обозначения
		field(x0 - 2 + left * margin, y0 + i) = { (char)('0' + i), white }; // вертикальные обозначения

		// рамки поля
		field(x0 + i + left * margin, y0 - 1) = { '-', white };
		field(x0 + i + left * margin, y0 + 10) = { '-', white };
		field(x0 - 1 + left * margin, y0 + i) = { '|', white };
		field(x0 + 10 + left * margin, y0 + i) = { '|', white };
	}

	// углы
	field(x0 - 1 + left * margin, y0 - 1) = { '+', white };
	field(x0 + 10 + left * margin, y0 - 1) = { '+', white };
	field(x0 - 1 + left * margin, y0 + 10) = { '+', white };
	field(x0 + 10 + left * margin, y0 + 10) = { '+', white };

	field.Draw();
}

void Game::DrawGame() {
	field.Clear();
	field.Draw();

	DrawField(false); // рисуем левое поле
	DrawField(true); // рисуем правое поле

	TextXY(x0 + text_x, y0 + 7, info_color, "For move target use arrow keys");
	TextXY(x0 + text_x, y0 + 8, info_color, "For shot press 'enter'");
}

void Game::DrawScores() {
	char buf[20];

	TextXY(x0 + text_x, y0, scores_color, "Scores");
	sprintf_s(buf, "You: %d / 20", userScores);
	TextXY(x0 + text_x, y0 + 1, scores_color, buf);
	sprintf_s(buf, "PC: %d / 20", aiScores);
	TextXY(x0 + text_x, y0 + 2, scores_color, buf);
}

// расстановка кораблей
void Game::PlaceShips() {
	for (int i = 0; i < shipsCount; i++)
		aiShips[i].AutoPlace(aiField[0]);

	int enter = 0;

	do {
		userField[0].Clear();
		userField[0].Draw(x0, y0);

		TextXY(x0 + margin, y0, info_color, "For rotate ship press 'R' key");
		TextXY(x0 + margin, y0 + 1, info_color, "For move ship use arrow keys");
		TextXY(x0 + margin, y0 + 2, info_color, "For end with ship press 'space'");
		TextXY(x0 + margin, y0 + 3, info_color, "For cancel press 'X' key");

		for (int i = 0; i < shipsCount; i++)
			userShips[i].Place(userField[0]);

		TextXY(x0 + margin, y0 + 5, white, "Start the game?");
		TextXY(x0 + margin, y0 + 6, white, "Press 'S' for continue");
		TextXY(x0 + margin, y0 + 7, white, "Press 'R' for replace ships");
		userField[0].Draw(x0, y0);

		while (!(enter = GetAsyncKeyState(key_S)) && !GetAsyncKeyState(key_R))
			Sleep(50);

		while (GetAsyncKeyState(key_R))
			Sleep(50);

		userField[0].Draw(x0, y0);

	} while (!enter);
}

// поиск свободной точки от x, y слева
void Game::FindEmptyPointLeft(int &x, int &y) {
	for (int j = x; j >= 0; j--) {
		if (userField[1](j, y).c == emptyChar) {
			x = j;
			return;
		}
	}

	for (int i = y - 1; i >= 0; i--) {
		for (int j = userField[1].GetWidth() - 1; j >= 0; j--) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}

	for (int i = userField[1].GetHeight() - 1; i > y; i--) {
		for (int j = userField[1].GetWidth() - 1; j >= 0; j--) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}
}

// поиск свободной точки от x, y справа
void Game::FindEmptyPointRight(int &x, int &y) {
	for (int j = x; j < userField[1].GetWidth(); j++)
		if (userField[1](j, y).c == emptyChar) {
			x = j;

			return;
		}

	for (int i = y + 1; i < 10; i++) {
		for (int j = 0; j < userField[1].GetWidth(); j++) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}

	for (int i = 0; i < y; i++) {
		for (int j = 0; j < userField[1].GetWidth(); j++) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}
}

// поиск свободной точки от x, y сверху
void Game::FindEmptyPointUp(int &x, int &y) {
	for (int i = y; i >= 0; i--) {
		if (userField[1](x, i).c == emptyChar) {
			y = i;

			return;
		}
	}

	for (int j = x - 1; j >= 0; j--) {
		for (int i = userField[1].GetHeight() - 1; i >= 0; i--) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}

	for (int j = userField[1].GetWidth() - 1; j > x; j--) {
		for (int i = userField[1].GetHeight() - 1; i >= 0; i--) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}
}

// поиск свободной точки от x, y снизу
void Game::FindEmptyPointDown(int &x, int &y) {
	for (int i = y; i < 10; i++) {
		if (userField[1](x, i).c == emptyChar) {
			y = i;

			return;
		}
	}

	for (int j = x + 1; j < userField[1].GetWidth(); j++) {
		for (int i = 0; i < userField[1].GetHeight(); i++) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}

	for (int j = 0; j < x; j++) {
		for (int i = 0; i < userField[1].GetHeight(); i++) {
			if (userField[1](j, i).c == emptyChar) {
				x = j;
				y = i;

				return;
			}
		}
	}
}

void Game::SetUserTarget(int &userX, int &userY) {
	if (userScores >= maxScores)
		return;
	
	int x, y;
	bool changed = false;

	userX++;
	FindEmptyPointRight(userX, userY); // ищем первую свободную точку справа от текущих координат

	userField[1](userX, userY) = { targetChar, targetColor }; // отрисовываем "цель" в найденной точке
	userField[1].Draw(x0 + margin, y0);

	// обрабатываем перемещения цели до тех пор, пока не произойдёт выстрел
	while (!GetAsyncKeyState(VK_RETURN)) {
		// стираем крестик
		userField[1](userX, userY) = { emptyChar, 0 };

		if (GetAsyncKeyState(VK_LEFT)) {
			userX--;
			FindEmptyPointLeft(userX, userY);
			changed = true;

			while (GetAsyncKeyState(VK_LEFT))
				Sleep(20);
		}

		if (GetAsyncKeyState(VK_RIGHT)) {
			userX++;
			FindEmptyPointRight(userX, userY);
			changed = true;

			while (GetAsyncKeyState(VK_RIGHT))
				Sleep(20);
		}

		if (GetAsyncKeyState(VK_DOWN)) {
			userY++;
			FindEmptyPointDown(userX, userY);
			changed = true;

			while (GetAsyncKeyState(VK_DOWN))
				Sleep(20);
		}

		if (GetAsyncKeyState(VK_UP)) {
			userY--;
			FindEmptyPointUp(userX, userY);
			changed = true;

			while (GetAsyncKeyState(VK_UP))
				Sleep(20);
		}

		userField[1](userX, userY) = { targetChar, targetColor }; // рисуем крестик в новых координатах

		if (changed) {
			userField[1].Draw(x0 + margin, y0);
			changed = false;
		}

		Sleep(50);
	}

	while (GetAsyncKeyState(VK_RETURN))
		Sleep(20);

	if (aiField[0](userX, userY).c == shipChar) { // было попадание
		userField[1](userX, userY) = { boomChar, boomColor };
		userScores++;
		DrawScores();

		int shipIndex = GetShipByCoordinates(userX, userY, false);

		if (aiShips[shipIndex].Boom())
			aiShips[shipIndex].Die(userField[1]);

		userField[1].Draw(x0 + margin, y0);

		SetUserTarget(userX, userY);
	}
	else {
		userField[1](userX, userY) = { failChar, failColor };
		userField[1].Draw(x0 + margin, y0);
	}
}

void Game::SetAI_Target(int &aiX, int & aiY, bool &wasShot) {
	if (aiScores >= maxScores)
		return;

	if (wasShot) {
		// в приоритете бить по 4 точкам вокруг точки попадания: (x, y - 1), (x, y + 1), (x - 1, y), (x + 1, y)
		int x_p[4] = { aiX, aiX, aiX - 1, aiX + 1 };
		int y_p[4] = { aiY - 1,aiY + 1, aiY, aiY };
		int variants[4] = { -1, -1, -1, -1 };
		int count = 0;

		do {
			int variant = rand() % 4; // определяем случайную точку

			// проверяем её наличие в списке проверенных
			int i = 0;
			while (i < count && variants[i] != variant)
				i++;

			if (i == count) {
				variants[count++] = variant; // если не оказалось, то заносим в список
			}
			else {
				continue; // если оказалась, переходим к новой итерации
			}

			// присваиваем координатам полученную точку
			aiX = x_p[variant];
			aiY = y_p[variant];
		} while ((aiX < 0 || aiX >= aiField[1].GetWidth() || aiY < 0 || aiY >= aiField[1].GetHeight() || aiField[1](aiX, aiY).c != emptyChar) && count < 4);

		// если точек вокруг не оказалось, то ищем рандомную точку
		if (count == 4) {
			do {
				aiX = rand() % aiField[1].GetWidth();
				aiY = rand() % aiField[1].GetHeight();
			} while (aiField[1](aiX, aiY).c != emptyChar);
		}
	}
	else {
		// рандомный поиск пустой клетки на поле компютера
		do {
			aiX = rand() % aiField[1].GetWidth();
			aiY = rand() % aiField[1].GetHeight();
		} while (aiField[1](aiX, aiY).c != emptyChar);
	}

	if ((wasShot = (userField[0](aiX, aiY).c == shipChar))) {
		aiField[1](aiX, aiY) = { boomChar, boomColor };
		userField[0](aiX, aiY) = { boomChar, boomColor };

		aiScores++;
		DrawScores();

		int shipIndex = GetShipByCoordinates(aiX, aiY, true);

		if (userShips[shipIndex].Boom())
			userShips[shipIndex].Die(userField[0]);

		userField[0].Draw(x0, y0);

		SetAI_Target(aiX, aiY, wasShot);
	}
	else {
		aiField[1](aiX, aiY) = { failChar, failColor };
		userField[0](aiX, aiY) = { failChar, failColor };

		userField[0].Draw(x0, y0);
	}
}

// получение корабля по координатам
int Game::GetShipByCoordinates(int x, int y, bool isUser) {
	if (isUser) {
		for (int i = 0; i < shipsCount; i++)
			if (userShips[i].CheckCoordinates(x, y))
				return i;
	}
	else {
		for (int i = 0; i < shipsCount; i++)
			if (aiShips[i].CheckCoordinates(x, y))
				return i;
	}

	return -1;
}

void Game::MakeGame() {
	// координаты хода игрока
	int userX = userField[1].GetWidth() / 2;
	int userY = userField[1].GetHeight() / 2;

	// координаты хода AI
	int aiX;
	int aiY;
	bool aiShot = false;

	bool isUser = true;

	DrawScores();

	do {
		userField[0].Draw(x0, y0);
		userField[1].Draw(x0 + margin, y0);

		if (isUser) {
			SetUserTarget(userX, userY);
		}
		else {
			SetAI_Target(aiX, aiY, aiShot);
		}

		isUser = !isUser;
	} while (userScores < maxScores && aiScores < maxScores); // повторяем, пока кто-то не выиграет

	RecordsTable table;
	table.AddRecord(isUser ? "AI" : "User", userScores, aiScores);
	table.Save();
}