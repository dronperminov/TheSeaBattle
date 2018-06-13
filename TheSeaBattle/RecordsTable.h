#pragma once

#include <string>
#include <iostream>
#include <fstream>

class RecordsTable {
	struct Record {
		std::string name;
		int userScore;
		int aiScore;
	};

	const std::string path = "records.txt";
	const int maxRecords = 8;

	Record *records;
	int size;
public:
	RecordsTable();

	void AddRecord(std::string name, int userScore, int aiScore);
	void Save();
	void Print();

	~RecordsTable();
};

