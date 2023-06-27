#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

class Entry {
	int id;
	string name;
	int year;
	int rent;
	string region;
	string location;
	string type;
	int rooms;
	int parking;
	int bathrooms;
	int size;
	string furnished;
	string facilities;
	string additionalFacilities;

	vector<string> separateSections(string line, char delim) {
		stringstream s(line);
		string section;
		vector<string> sections;

		while (getline(s, section, delim)) {
			sections.push_back(section);
		}

		return sections;
	}

	bool hasChar(string row, char c) {
		return row.find(c) != string::npos;
	}

	vector<string> removeCommas(vector<string> strings) {
		vector<string> newStrings;
		for (string s : strings) {
			if (s == ",") continue;
			else if (s[0] == ',') {
				s.erase(0, 1);
			} else if (s.back() == ',') {
				s.pop_back();
			}
			newStrings.push_back(s);
		}

		return newStrings;
	}

	vector<string> getColumns(string row) {
		vector<string> columns;
		vector<string> quotedSections;
		if (hasChar(row, '"')) {
			quotedSections = separateSections(row, '"');
			quotedSections = removeCommas(quotedSections);
		}

		if (quotedSections.empty()) columns = separateSections(row, ',');
		else {
			columns = separateSections(quotedSections[0], ',');
			switch (quotedSections.size()) {
			case 3:
				if (hasChar(quotedSections[2], ',')) {
					columns.push_back(quotedSections[1]);
					vector<string> lastCol = separateSections(quotedSections[2], ',');
					columns.insert(columns.end(), lastCol.begin(), lastCol.end());
				} else {
					columns.push_back(quotedSections[1]);
					columns.push_back(quotedSections[2]);
				}
				break;
			case 4:
				quotedSections.erase(quotedSections.begin());
				columns.insert(columns.end(), quotedSections.begin(), quotedSections.end());
				break;
			}
		}

		return columns;
	}

	void initEntry(string row) {
		vector<string> columns = getColumns(row);

		for (string col : columns) {
			cout << col << endl;
		}
	}

	public:
		Entry(string row) {
			initEntry(row);
		}

};