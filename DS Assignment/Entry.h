#pragma once

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const char greaterThanChar = '>';

struct Entry {
	unsigned int id;
	string name;
	unsigned int year;
	unsigned int rent;
	string region;
	string location;
	string type;
	unsigned int rooms;
	unsigned int parking;
	unsigned int bathrooms;
	unsigned int size;
	string furnished;
	string facilities;
	string additionalFacilities;

	void setName(string s) {
		string names[2] = { s, "N/A" };
		name = names[s.empty()];
	}

	void setRent(string s) {
		s.erase(0, 3);
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
		rent = stoul(s + char('0' * s.empty()), nullptr, 0);
	}

	void setRegionAndLocation(string s) {
		size_t pos = s.find(" - ");
		region = s.substr(0, pos);
		s.erase(0, pos + 3);
		location = s;
	}

	void setRooms(string s) {
		bool gtet = s.length() >= 2;
		bool empty = s.length() == 0;
		rooms = stoul(s.substr(s.length() - (1 + gtet - empty)) + char('0' * empty), nullptr, 0);
		bool gtt = s.length() > 2;
		rooms += (gtet && gtt) * greaterThanChar;
	}

	string getRooms() {
		char symbol = (rooms > greaterThanChar) * greaterThanChar;
		int roomInt = (rooms < greaterThanChar) * rooms + (rooms > greaterThanChar) * (rooms - greaterThanChar);
		ostringstream oss;
		oss << symbol << to_string(roomInt);

		return oss.str();
	}

	void setFurnished(string s) {
		string statuses[2] = { s, "N/A" };
		furnished = statuses[s.empty()];
	}

	void setFacilities(string s) {
		string facilityTable[2] = { s, "N/A" };
		facilities = facilityTable[s.empty()];
	}

	void setAdditionalFacilities(string s) {
		string facilityTable[2] = { s, "N/A" };
		additionalFacilities = facilityTable[s.empty()];
	}

	Entry(string *col) {
		id = stoul(col[0], nullptr, 0);
		setName(col[1]);
		year = stoul(col[2] + char('0' * col[2].empty()), nullptr, 0);
		setRent(col[3]);
		setRegionAndLocation(col[4]);
		type = col[5];
		setRooms(col[6]);
		parking = stoul(col[7] + char('0' * col[7].empty()), nullptr, 0);
		bathrooms = stoul(col[8] + char('0' * col[8].empty()), nullptr, 0);
		size = stoul(col[9], nullptr, 0);
		setFurnished(col[10]);
		setFacilities(col[11]);
		setAdditionalFacilities(col[12]);
	}
};