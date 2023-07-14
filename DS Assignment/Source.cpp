#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <chrono>
#include "Entry.hpp"
#include "CSV.h"
#include "HashTable.h"
#include "TrieNode.h"
#include "Vector.hpp"

#define MAX_DATA_SIZE 19991
#define COLUMN_COUNT 14
#define RANGE 255

// A utility function to get maximum
// value in arr[]
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp)
{

	// Output array
	int *output = new int[n];
	int i, count[10] = { 0 };

	// Store count of occurrences
	// in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i]
	// now contains actual position
	// of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[],
	// so that arr[] now contains sorted
	// numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(int arr[], int n)
{

	// Find the maximum number to
	// know number of digits
	int m = getMax(arr, n);

	// Do counting sort for every digit.
	// Note that instead of passing digit
	// number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void countingSort(int array[], int size) {
	// The size of count must be at least the (max+1) but
	// we cannot assign declare it as int count(max+1) in C++ as
	// it does not support dynamic memory allocation.
	// So, its size is provided statically.
	int output[MAX_DATA_SIZE];
	int count[MAX_DATA_SIZE];
	int max = array[0];

	// Find the largest element of the array
	for (int i = 1; i < size; i++) {
		if (array[i] > max)
			max = array[i];
	}

	// Initialize count array with all zeros.
	for (int i = 0; i <= max; ++i) {
		count[i] = 0;
	}

	// Store the count of each element
	for (int i = 0; i < size; i++) {
		count[array[i]]++;
	}

	// Store the cummulative count of each array
	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	// Find the index of each element of the original array in count array, and
	// place the elements in output array
	for (int i = size - 1; i >= 0; i--) {
		output[count[array[i]] - 1] = array[i];
		count[array[i]]--;
	}

	// Copy the sorted elements into original array
	for (int i = 0; i < size; i++) {
		array[i] = output[i];
	}
}

// Function to print an array
void printArray(int array[], int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

static void RadixSort256(unsigned int *arr, int n)
{
	if (n <= 1) return; // Added base case

	unsigned int *output = new unsigned int[n]; // output array
	int *count = new int[256];
	unsigned int *originalArr = arr; // So we know which was input

	for (int shift = 0, s = 0; shift < 4; shift++, s += 8)
	{
		// Zero the counts
		for (int i = 0; i < 256; i++)
			count[i] = 0;

		// Store count of occurrences in count[] 
		for (int i = 0; i < n; i++)
			count[(arr[i] >> s) & 0xff]++;

		// Change count[i] so that count[i] now contains 
		// actual position of this digit in output[] 
		for (int i = 1; i < 256; i++)
			count[i] += count[i - 1];

		// Build the output array 
		for (int i = n - 1; i >= 0; i--)
		{
			// precalculate the offset as it's a few instructions
			int idx = (arr[i] >> s) & 0xff;

			// Subtract from the count and store the value
			output[--count[idx]] = arr[i];
		}

		// Copy the output array to input[], so that input[] 
		// is sorted according to current digit

		// We can just swap the pointers
		unsigned int *tmp = arr;
		arr = output;
		output = tmp;
	}

	// If we switched pointers an odd number of times,
	// make sure we copy before returning
	if (originalArr == output)
	{
		unsigned int *tmp = arr;
		arr = output;
		output = tmp;

		for (int i = 0; i < n; i++)
			arr[i] = output[i];
	}

	delete[] output;
	delete[] count;
}

int partition(int arr[], int low, int high)
{
	// pivot
	int pivot = arr[high];

	// Index of smaller element
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller
		// than or equal to pivot
		if (arr[j] <= pivot) {

			// increment index of
			// smaller element
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
int partition_r(int arr[], int low, int high)
{
	// Generate a random number in between
	// low .. high
	srand(time(NULL));
	cout << low << " " << high << endl;
	int random = low + rand() % (high - low);

	// Swap A[random] with A[high]
	swap(arr[random], arr[high]);

	return partition(arr, low, high);
}

/* The main function that implements
QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high) {

		/* pi is partitioning index,
		arr[p] is now
		at right place */
		int pi = partition_r(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int main() {
	char firstChar = 'a';
	unordered_map<char, string> facilityMap;
	unordered_map<string, vector<int>> combinationMap;

	string header;
	string **csvRows = new string*[MAX_DATA_SIZE];
	int sizes[MAX_DATA_SIZE];
	unsigned int *sizes2 = new unsigned int[MAX_DATA_SIZE];
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
			col[3].erase(0, 3);
			col[3].erase(remove(col[3].begin(), col[3].end(), ' '), col[3].end());
			sizes[i] = atoi(col[6].c_str());
			//sizes2[i] = stoul(col[6], nullptr, 0);
			csvRows[i] = col;
			i++;
		}
	}

	reader.close();

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();
	//countingSort(sizes, MAX_DATA_SIZE);
	//radixsort(sizes, MAX_DATA_SIZE);
	//RadixSort256(sizes2, MAX_DATA_SIZE);
	//quickSort(sizes, 0, MAX_DATA_SIZE - 1);
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << " microseconds";

	/*for (int i = 0; i < MAX_DATA_SIZE; i++) {
		cout << sizes2[i] << endl;
	}*/
	/*string *firstRow = csvRows[19783];
	for (int i = 0; i < COLUMN_COUNT; i++) {
		cout << firstRow[i] << endl;
	}*/

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