#pragma once

#include <sstream>
#include <algorithm>

const char greaterThanChar = '>';

struct Entry {
	unsigned int id;
	std::string name;
	unsigned int year;
	unsigned int rent;
	std::string region;
	std::string location;
	std::string type;
	unsigned int rooms;
	unsigned int parking;
	unsigned int bathrooms;
	unsigned int size;
	std::string furnished;
	std::string facilities;
	std::string additionalFacilities;

	void setName(std::string s) {
		std::string names[2] = { s, "N/A" };
		name = names[s.empty()];
	}

	void setRent(std::string s) {
		s.erase(0, 3);
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
		rent = stoul(s + char('0' * s.empty()), nullptr, 0);
	}

	void setRegionAndLocation(std::string s) {
		size_t pos = s.find(" - ");
		region = s.substr(0, pos);
		s.erase(0, pos + 3);
		location = s;
	}

	void setRooms(std::string s) {
		bool gtet = s.length() >= 2;
		bool empty = s.length() == 0;
		rooms = stoul(s.substr(s.length() - (1 + gtet - empty)) + char('0' * empty), nullptr, 0);
		bool gtt = s.length() > 2;
		rooms += (gtet && gtt) * greaterThanChar;
	}

	void setFurnished(std::string s) {
		std::string statuses[2] = { s, "N/A" };
		furnished = statuses[s.empty()];
	}

	void setFacilities(std::string s) {
		s.erase(remove(s.begin(), s.end(), '"'), s.end());
		std::string facilityTable[2] = { s, "N/A" };
		facilities = facilityTable[s.empty()];
	}

	void setAdditionalFacilities(std::string s) {
		s.erase(remove(s.begin(), s.end(), '"'), s.end());
		std::string facilityTable[2] = { s, "N/A" };
		additionalFacilities = facilityTable[s.empty()];
	}

	std::string getYear() {
		if (!year)
			return "N/A";
		else
			return std::to_string(year);
	}

	std::string getRent() {
		if (!rent)
			return "N/A";
		else
			return std::to_string(rent);
	}

	std::string getRooms() {
		char symbol = (rooms > greaterThanChar) * greaterThanChar;
		int roomInt = (rooms < greaterThanChar) * rooms + (rooms > greaterThanChar) * (rooms - greaterThanChar);
		std::string roomString = std::to_string(roomInt);
		std::string roomTable[2] = {roomString, "N/A"};
		std::ostringstream oss;
		oss << symbol << roomTable[roomString.empty()];

		return oss.str();
	}

	std::string getParking() {
		if (!parking)
			return "N/A";
		else
			return std::to_string(parking);
	}

	std::string getBathrooms() {
		if (!bathrooms)
			return "N/A";
		else
			return std::to_string(bathrooms);
	}

	void print() {
		std::cout << "---------------------------Property Details---------------------------" << std::endl;
		std::cout << "ID: " << id << std::endl;
		std::cout << "Name: " << name << std::endl;
		std::cout << "Completion Year:" << getYear() << std::endl;
		std::cout << "Location: " << location << std::endl;
		std::cout << "Region: " << region << std::endl;
		std::cout << "Property Type: " << type << std::endl;
		std::cout << "Rooms: " << getRooms() << std::endl;
		std::cout << "Parking: " << getParking() << std::endl;
		std::cout << "Bathroom: " << getBathrooms() << std::endl;
		std::cout << "Size: " << size << " square feet" << std::endl;
		std::cout << "Furnish Status: " << furnished << std::endl;
		std::cout << "Facilities: " << facilities << std::endl;
		std::cout << "Additional Facilities: " << additionalFacilities << std::endl << std::endl;
	}

	Entry(void) {}

	Entry(std::string *col) {
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