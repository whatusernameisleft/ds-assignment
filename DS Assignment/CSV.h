#pragma once

#include <fstream>
#include <future>
#include "Vector.h"
#include "Entry.h"

#define COLUMN_COUNT 14

Entry createEntry(string line) {
	string *col = new string[COLUMN_COUNT];
	int i = 0;
	const char *start = line.c_str();
	bool instring{ false };

	for (const char *p = start; *p; p++) {
		if (*p == '"') instring = !instring;
		else if (*p == ',' && !instring) {
			col[i] = string(start, p - start);
			i++;
			start = p + 1;
		}
	}
	col[i] = string(start);
	Entry entry(col);

	return entry;
}

Vector<future<Entry>> readCSV(ifstream &in) {
	Vector<future<Entry>> entries;

	while (!in.eof() && !in.fail()) {
		string line;
		getline(in, line);
		entries.push_back(async(
			[](string data) {
				return createEntry(data);
			},
			move(line)));
	}
	return entries;
}