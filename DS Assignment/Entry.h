#pragma once
#include <string>
#include <list>

using namespace std;

class Entry {
	int id;
	string name;
	int year;
	int rent;
	string location;
	string type;
	int rooms;
	int parking;
	int bathrooms;
	int size;
	string furnished;
	list<string> facilities;
	list<string> additionalFacilities;
};