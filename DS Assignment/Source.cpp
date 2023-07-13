#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Entry.hpp"
#include "CSV.h"
#include "HashTable.h"
#include "TrieNode.h"
#include "Vector.hpp"

#define MAX_DATA_SIZE 19991
#define COLUMN_COUNT 14

int main() {
	char firstChar = 'a';
	unordered_map<char, string> facilityMap;
	unordered_map<string, vector<int>> combinationMap;

	string header;
	string **csvRows = new string*[MAX_DATA_SIZE];
	ifstream reader("data.csv");
	if (reader.is_open()) {
		int i = 0;
		string line, column;
		getline(reader, line);
		header = line;
		while (getline(reader, line)) { 
			string *col = new string[COLUMN_COUNT];
			int j = 0;
			const char *start = line.c_str();
			bool instring{ false };
			for (const char *p = start; *p; p++) {
				if (*p == '"') instring = !instring;
				else if (*p == ',' && !instring) {
					col[j] = string(start, p - start);
					j++;
					start = p + 1;
				}
			}
			col[j] = string(start);
			csvRows[i] = col;
			i++;
		}
	}

	reader.close();

	string *firstRow = csvRows[19783];
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << firstRow[i] << endl;
	}

	/*string header;
	Vector<Vector<string>> csvRows;
	ifstream reader("data.csv");
	if (reader.is_open()) {
		string line, column, id;
		getline(reader, line);
		header = line;
		while (getline(reader, line)) {
			stringstream ss(line);
			Vector<string> columns;
			bool withQ = false;
			string part{ "" };
			while (getline(ss, column, ',')) {
				auto pos = column.find("\"");
				if (pos < column.length()) {
					withQ = !withQ;
					part += column.substr(0, pos);
					column = column.substr(pos + 1, column.length());
				}
				if (!withQ) {
					column += part;
					columns.push(move(column));
					part = "";
				} else {
					part += column + ",";
				}
			}
			csvRows.push(columns);
		}
	}*/

	/*getline(dataFile, line);
	while (getline(dataFile, line)) {
		if (line == "") continue;
		Entry e(line, firstChar, facilityMap, combinationMap);
	}
	dataFile.close();*/

	//Entry e("100323185,The Hipster @ Taman Desa,2022,RM 4 200 per month,Kuala Lumpur - Taman Desa,Condominium,5,2,6,1842 sq.ft.,Fully Furnished,\"Minimart, Gymnasium, Security, Playground, Swimming Pool, Parking, Lift, Barbeque area, Multipurpose hall, Jogging Track\",\"Air - Cond, Cooking Allowed, Washing Machine\",Kuala Lumpur", firstChar, facilityMap, combinationMap);
	//Entry e2("100323128,Pangsapuri Teratak Muhibbah 2,,RM 1 000 per month,Kuala Lumpur - Taman Desa,Apartment,3,,2,650 sq.ft.,Fully Furnished,\"Minimart, Jogging Track, Lift, Swimming Pool\",,Kuala Lumpur", firstChar, facilityMap, combinationMap);
	//Entry e3("100322078,Pangsapuri Melur (Sentul),2006,RM 1 750 per month,Kuala Lumpur - Sentul,Apartment,3,,2,1065 sq.ft.,Partially Furnished,,,Kuala Lumpur", firstChar, facilityMap, combinationMap);
	//Entry e4("86821569,,,RM 1 700 per month,Kuala Lumpur - Jalan Kuching,Condominium,3,2,2,1100 sq.ft.,Partially Furnished,Swimming Pool,Air-Cond,Kuala Lumpur", firstChar, facilityMap, combinationMap);
	//Entry e5("95419037,,,RM 700 per month,Selangor - Semenyih,Apartment,3,,2,1000 sq.ft.,Partially Furnished,Lift,,Selangor", firstChar, facilityMap, combinationMap);
	//Entry e6("98921213,\"Kita Mekar, KITA @ Cybersouth\",2024,RM 2 200 per month,Selangor - Dengkil,Townhouse Condo,3,2,2,1160 sq.ft.,Fully Furnished,\"Parking, Playground, Security, Swimming Pool, Club house, Minimart, Multipurpose hall, Jogging Track, Gymnasium, Barbeque area\",\"Air - Cond, Cooking Allowed, Washing Machine, Internet\",Selangor", firstChar, facilityMap, combinationMap);

	//string facCodes[] = { e.facilities, e2.facilities };
	//TrieNode *root = new TrieNode();
	//int n = sizeof(facCodes) / sizeof(string);
	//insertIntoTrie(root, facCodes, n);
	//string query = "ag";
	//displayNodes(root, query);

	/*cout << endl;
	for (auto const &i : facilityMap) {
		cout << i.first << ": " << i.second << endl;
	}*/
	/*for (auto const &i : combinationMap) {
		stringstream res;
		copy(i.second.begin(), i.second.end(), ostream_iterator<int>(res, " "));
		cout << i.first << ": " << res.str() << endl;
	}*/

	//HashTable *ht = create_table(CAPACITY);
	//ht_insert(ht, (char *)"1", (char *)"First address");
	//ht_insert(ht, (char *)"2", (char *)"Second address");
	//ht_insert(ht, (char *)"Hel", (char *)"Third address");
	//ht_insert(ht, (char *)"Cau", (char *)"Fourth address");
	//print_search(ht, (char *)"1");
	//print_search(ht, (char *)"2");
	//print_search(ht, (char *)"3");
	//print_search(ht, (char *)"Hel");
	//print_search(ht, (char *)"Cau"); // Collision!
	//print_table(ht);
	//ht_delete(ht, (char *)"1");
	//ht_delete(ht, (char *)"Cau");
	//print_table(ht);
	//free_table(ht);


}