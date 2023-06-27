#include <iostream>
#include <unordered_map>
#include "Entry.h"
#include "CSV.h"

int main() {
	Entry e("100323185,The Hipster @ Taman Desa,2022,RM 4 200 per month,Kuala Lumpur - Taman Desa,Condominium,5,2,6,1842 sq.ft.,Fully Furnished,\"Minimart, Gymnasium, Security, Playground, Swimming Pool, Parking, Lift, Barbeque area, Multipurpose hall, Jogging Track\",\"Air - Cond, Cooking Allowed, Washing Machine\",Kuala Lumpur");
	Entry e2("100323128,Pangsapuri Teratak Muhibbah 2,,RM 1 000 per month,Kuala Lumpur - Taman Desa,Apartment,3,,2,650 sq.ft.,Fully Furnished,\"Minimart, Jogging Track, Lift, Swimming Pool\",,Kuala Lumpur");
	unordered_map<int, Entry, EntryHashFunction> entryMap;
	entryMap[e.getId()] = e;
	entryMap[e2.getId()] = e2;

	/*for (const auto &i : entryMap) {
		cout << i.first << endl;
	}*/
}