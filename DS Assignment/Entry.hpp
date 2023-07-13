#pragma once
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "Trim.h"

using namespace std;

struct Entry {
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
			trim(section);
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

	void setId(string col) {
		id = atoi(col.c_str());
	}

	void setName(string col) {
		name = col;
	}

	void setYear(string col) {
		year = atoi(col.c_str());
	}

	void setRent(string col) {
		col.erase(0, 3);
		col.erase(remove(col.begin(), col.end(), ' '), col.end());
		rent = atoi(col.c_str());
	}

	void setRegionAndLocation(string col) {
		size_t pos = col.find(" - ");
		region = col.substr(0, pos);
		col.erase(0, pos + 3);
		location = col;
	}

	void setType(string col) {
		type = col;
	}

	void setRooms(string col) {
		rooms = atoi(col.c_str());
	}

	void setParking(string col) {
		parking = atoi(col.c_str());
	}

	void setBathrooms(string col) {
		bathrooms = atoi(col.c_str());
	}

	void setSize(string col) {
		size = atoi(col.c_str());
	}

	void setFurnished(string col) {
		furnished = col;
	}

	//vector<char> mapFacilities(vector<string> facs, char &character, unordered_map<string, char> &facilityMap) {
	//	vector<char> facChars = 
	//}

	bool isInMap(unordered_map<char, string> map, string value) {
		vector<string> values;
		for (unordered_map<char, string>::iterator it = map.begin(); it != map.end(); ++it) {
			values.push_back(it->second);
		}
		if (find(values.begin(), values.end(), value) != values.end()) {
			return true;
		}
		return false;
	}

	char getChar(unordered_map<char, string> map, string value) {
		for (auto const &i : map) {
			if (i.second == value) {
				return i.first;
			}
		}
		return ' ';
	}

	/*vector<string> get_all_selections(vector<char> arr) {
		vector<string> selections;
		selections.push_back("");
		for (int i = 0; i < arr.size(); i++) {
			int size = selections.size();
			for (int j = 0; j < size; j++) {
				string new_selection = selections[j] + arr[i];
				selections.push_back(new_selection);
			}
		}
		return selections;
	}

	void setCombinations(unordered_map<string, vector<int>> &combinationMap) {
		vector<string> selections = get_all_selections(facilities);
		for (string selection : selections) {
			combinationMap[selection].push_back(id);
		}
	}*/

	void setFacilities(string col, char &character, unordered_map<char, string> &facilityMap, unordered_map<string, vector<int>> &combinationMap) {
		vector<string> facs = separateSections(col, ',');
		for (string facility : facs) {
			char c;
			if (isInMap(facilityMap, facility)) c = getChar(facilityMap, facility);
			else {
				facilityMap[character] = facility;
				c = character;
				character++;
			}
			facilities.push_back(c);
		}
		sort(facilities.begin(), facilities.end());
		cout << facilities << endl;
		//setCombinations(combinationMap);
	}

	void setAdditionalFacilities(string col) {
		additionalFacilities = col;
	}
	
	void setDetails(vector<string> columns, char &character, unordered_map<char, string> &facilityMap, unordered_map<string, vector<int>> &combinationMap) {
		setId(columns[0]);
		setName(columns[1]);
		setYear(columns[2]);
		setRent(columns[3]);
		setRegionAndLocation(columns[4]);
		setType(columns[5]);
		setRooms(columns[6]);
		setParking(columns[7]);
		setBathrooms(columns[8]);
		setSize(columns[9]);
		setFurnished(columns[10]);
		setFacilities(columns[11], character, facilityMap, combinationMap);
		setAdditionalFacilities(columns[12]);
	}

	void initEntry(string row, char &character, unordered_map<char, string> &facilityMap, unordered_map<string, vector<int>> &combinationMap) {
		vector<string> columns = getColumns(row);
		setDetails(columns, character, facilityMap, combinationMap);
	}

	int id;
	Entry(string row, char &character, unordered_map<char, string> &facilityMap, unordered_map<string, vector<int>> &combinationMap) {
		initEntry(row, character, facilityMap, combinationMap);
	}

	int getId() {
		return id;
	}
};