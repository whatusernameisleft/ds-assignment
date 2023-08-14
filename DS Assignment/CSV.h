#pragma once

#include <iomanip>

extern const int MAX_DATA_SIZE;
extern const int COLUMN_COUNT;

/*
	Title: CSV Parser Source Code
	Author: Christophe
	Date: 2016
	Code version: N/A
	Availability: https://stackoverflow.com/a/35639462
*/
Entry* readCSV(std::ifstream &in) {
	Entry *entries = new Entry[MAX_DATA_SIZE];
	std::string *cols = new std::string[COLUMN_COUNT];
	int i = 0, j;
	std::string line;

	while (getline(in, line)) {
		j = 0;
		const char *start = line.c_str();
		bool instring = false ;

		for (const char *p = start; *p; p++) {
			if (*p == '"') instring = !instring;
			else if (*p == ',' && !instring) {
				cols[j] = std::string(start, p - start);
				j++;
				start = p + 1;
			}
		}
		cols[j] = std::string(start);
		entries[i] = Entry(cols);
		i++;
	}
	delete[] cols;

	return entries;
}