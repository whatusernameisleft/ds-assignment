#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <chrono>
#include "Entry.h"
#include "CSV.h"
#include "Vector.h"
#include "Sorts.h"

#define MAX_DATA_SIZE 19991
#define COLUMN_COUNT 14
#define RANGE 255

using namespace std;

int main() {
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	ifstream reader("data.csv");
	if (!reader.is_open()) {
		reader.close();
		cout << "Can't read data file. Exiting program." << endl;
		return 1;
	}
	string header;
	getline(reader, header);
	auto entries = readCSV(reader);

	reader.close();
	entries.pop_back();

	//RadixSort256(sizes2, MAX_DATA_SIZE);
	//QuickSort(sizes2, MAX_DATA_SIZE);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << endl;
	cout << entries.size() << endl;

	/*for (int i = 0; i < MAX_DATA_SIZE; i++) {
		cout << sizes2[i] << endl;
	}*/
	/*string *firstRow = csvRows[19783];
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << firstRow[i] << endl;
	}*/
	Entry e = entries.get(19990).get();
	cout << e.facilities << endl;
	cout << e.additionalFacilities << endl;
	cout << entries.size() << endl;

	int i;
	cin >> i;

	return 0;
}