#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
	system("mode con cols=100 lines=30"); // устанавливаем минимальный размер консоли
	srand(time(NULL)); // инициализируем генератор случайных чисел

	bool exit = false;
	int item;

	do {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
		system("cls");
		cout << "What do you want to do?" << endl;
		cout << "1. Start game" << endl;
		cout << "2. View records table" << endl;
		cout << "3. View about menu" << endl;
		cout << "4. Quit" << endl;
		cout << "> ";
		cin >> item;

		if (item == 1) {
			Game game(fieldX0, fieldY0);

			game.DrawField(0);
			game.PlaceShips();
			game.DrawGame();
			game.MakeGame();
		}
		else if (item == 2) {
			RecordsTable table;
			table.Print();
		}
		else if (item == 3) {
			cout << "The Sea battle game" << endl;
			cout << "Developed by programforyou in june 2018" << endl;
		}

		if (item != 4) {
			system("pause");
		}		
	} while (item != 4);

    return 0;
}

