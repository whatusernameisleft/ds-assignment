#pragma once

#include <future>
#include "Entry.h"

extern const int MAX_DATA_SIZE;
extern const int COLUMN_COUNT;

Entry createEntry(std::string line) {
	std::string *col = new std::string[COLUMN_COUNT];
	int i = 0;
	const char *start = line.c_str();
	bool instring{ false };

	for (const char *p = start; *p; p++) {
		if (*p == '"') instring = !instring;
		else if (*p == ',' && !instring) {
			col[i] = std::string(start, p - start);
			i++;
			start = p + 1;
		}
	}
	col[i] = std::string(start);
	Entry entry(col);

	return entry;
}

Entry* readCSV(std::ifstream &in) {
	Entry *entries = new Entry[MAX_DATA_SIZE];
	int i = 0;
	std::string line;

	while (getline(in, line)) {
		entries[i] = (createEntry(line));
		i++;
	}

	return entries;
}