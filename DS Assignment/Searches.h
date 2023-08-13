#pragma once

/*
	Title: Binary Search – Data Structure and Algorithm Tutorials
	Author: GeeksforGeeks
	Date: 2023
	Code version: N/A
	Availability: https://www.geeksforgeeks.org/binary-search/
*/
int binarySearch(Entry *entries, int n, unsigned int id) {
	int l = 0;
	int r = n - 1;
	while (l <= r) {
		int m = l +(r - l) / 2;
		
		if (entries[m].id == id)
			return m;

		if (entries[m].id < id) 
			l = m + 1;
		else 
			r = m - 1;
	}

	return -1;
}

/*
	Title: Sentinel Linear Search
	Author: kaushikkakdey
	Date: 2023
	Code version: N/A
	Availability: https://www.geeksforgeeks.org/sentinel-linear-search/
*/
int sentinelLinearSearch(Entry *entries, int n, unsigned int id) {
	unsigned int last = entries[n - 1].id;

	entries[n - 1].id = id;
	int i = 0;

	while (entries[i].id != id)
		i++;

	entries[n - 1].id = last;

	if ((i < n - 1) || (entries[n - 1].id == id))
		return i;
	else
		return -1;
}