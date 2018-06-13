#include "stdafx.h"
#include "RecordsTable.h"

using namespace std;

RecordsTable::RecordsTable() {
	fstream file;
	file.open(path.c_str(), ios::in);

	records = new Record[maxRecords + 1];

	if (!file) {
		size = 0;
	}
	else {
		file >> size;

		for (int i = 0; i < size; i++)
			file >> records[i].name >> records[i].userScore >> records[i].aiScore;

		file.close();
	}
}

void RecordsTable::AddRecord(std::string name, int userScore, int aiScore) {
	records[size].name = name;
	records[size].userScore = userScore;
	records[size].aiScore = aiScore;

	size++;
}

void RecordsTable::Save() {
	bool isSorted = false;

	// сортируем таблицу рекордов
	while (!isSorted) {
		isSorted = true;

		for (int i = 0; i < size - 1; i++) {
			if (records[i].aiScore + records[i].userScore > records[i + 1].aiScore + records[i + 1].userScore) {
				swap(records[i], records[i + 1]);
				isSorted = false;
			}
		}
	}

	if (size > maxRecords)
		size = maxRecords;

	fstream file;
	file.open(path.c_str(), ios::out);

	file << size;

	for (int i = 0; i < size ; i++)
		file << records[i].name << " " << records[i].userScore << " " << records[i].aiScore << endl;

	file.close();
}

void RecordsTable::Print() {
	if (size == 0) {
		cout << "No records yet!" << endl;
	}
	else {
		for (int i = 0; i < size; i++)
			cout << records[i].name << " " << records[i].userScore << " " << records[i].aiScore << endl;
	}
}


RecordsTable::~RecordsTable() {
	delete[] records;
}