#pragma once

/*
	Title: Why is Radix Sort so Fast? Part 3 Comparison and Code, Radix Sort vs QuickSort
	Author: Creel
	Date: 2020
	Code version: N/A
	Availability: https://youtu.be/TPpWvpnQq5s
*/
static void RadixSortRent(Entry *arr, int n)
{
	if (n <= 1) return; // Added base case

	Entry *output = new Entry[n]; // output array
	int *count = new int[256];
	Entry *originalArr = arr; // So we know which was input

	for (int shift = 0, s = 0; shift < 4; shift++, s += 8)
	{
		// Zero the counts
		for (int i = 0; i < 256; i++)
			count[i] = 0;

		// Store count of occurrences in count[] 
		for (int i = 0; i < n; i++)
			count[(arr[i].rent >> s) & 0xff]++;

		// Change count[i] so that count[i] now contains 
		// actual position of this digit in output[] 
		for (int i = 1; i < 256; i++)
			count[i] += count[i - 1];

		// Build the output array 
		for (int i = n - 1; i >= 0; i--)
		{
			// precalculate the offset as it's a few instructions
			int idx = (arr[i].rent >> s) & 0xff;

			// Subtract from the count and store the value
			output[--count[idx]] = arr[i];
		}

		// Copy the output array to input[], so that input[] 
		// is sorted according to current digit

		// We can just swap the pointers
		Entry *tmp = arr;
		arr = output;
		output = tmp;
	}

	// If we switched pointers an odd number of times,
	// make sure we copy before returning
	if (originalArr == output)
	{
		Entry *tmp = arr;
		arr = output;
		output = tmp;

		for (int i = 0; i < n; i++)
			arr[i] = output[i];
	}

	delete[] output;
	delete[] count;
}

static void RadixSortSize(Entry *arr, int n)
{
	if (n <= 1) return; // Added base case

	Entry *output = new Entry[n]; // output array
	int *count = new int[256];
	Entry *originalArr = arr; // So we know which was input

	for (int shift = 0, s = 0; shift < 4; shift++, s += 8)
	{
		// Zero the counts
		for (int i = 0; i < 256; i++)
			count[i] = 0;

		// Store count of occurrences in count[] 
		for (int i = 0; i < n; i++)
			count[(arr[i].size >> s) & 0xff]++;

		// Change count[i] so that count[i] now contains 
		// actual position of this digit in output[] 
		for (int i = 1; i < 256; i++)
			count[i] += count[i - 1];

		// Build the output array 
		for (int i = n - 1; i >= 0; i--)
		{
			// precalculate the offset as it's a few instructions
			int idx = (arr[i].size >> s) & 0xff;

			// Subtract from the count and store the value
			output[--count[idx]] = arr[i];
		}

		// Copy the output array to input[], so that input[] 
		// is sorted according to current digit

		// We can just swap the pointers
		Entry *tmp = arr;
		arr = output;
		output = tmp;
	}

	// If we switched pointers an odd number of times,
	// make sure we copy before returning
	if (originalArr == output)
	{
		Entry *tmp = arr;
		arr = output;
		output = tmp;

		for (int i = 0; i < n; i++)
			arr[i] = output[i];
	}

	delete[] output;
	delete[] count;
}

static void RadixSortId(Entry *arr, int n)
{
	if (n <= 1) return; // Added base case

	Entry *output = new Entry[n]; // output array
	int *count = new int[256];
	Entry *originalArr = arr; // So we know which was input

	for (int shift = 0, s = 0; shift < 4; shift++, s += 8)
	{
		// Zero the counts
		for (int i = 0; i < 256; i++)
			count[i] = 0;

		// Store count of occurrences in count[] 
		for (int i = 0; i < n; i++)
			count[(arr[i].id >> s) & 0xff]++;

		// Change count[i] so that count[i] now contains 
		// actual position of this digit in output[] 
		for (int i = 1; i < 256; i++)
			count[i] += count[i - 1];

		// Build the output array 
		for (int i = n - 1; i >= 0; i--)
		{
			// precalculate the offset as it's a few instructions
			int idx = (arr[i].id >> s) & 0xff;

			// Subtract from the count and store the value
			output[--count[idx]] = arr[i];
		}

		// Copy the output array to input[], so that input[] 
		// is sorted according to current digit

		// We can just swap the pointers
		Entry *tmp = arr;
		arr = output;
		output = tmp;
	}

	// If we switched pointers an odd number of times,
	// make sure we copy before returning
	if (originalArr == output)
	{
		Entry *tmp = arr;
		arr = output;
		output = tmp;

		for (int i = 0; i < n; i++)
			arr[i] = output[i];
	}

	delete[] output;
	delete[] count;
}

/*
	Title: Why is Radix Sort so Fast? Part 3 Comparison and Code, Radix Sort vs QuickSort
	Author: Creel
	Date: 2020
	Code version: N/A
	Availability: https://youtu.be/TPpWvpnQq5s
*/
int PartitionRent(Entry *data, int lo, int hi)
{
	Entry pivot = data[lo + (hi - lo) / 2];
	int i = lo - 1;
	int j = hi + 1;

	for (;;)
	{
		do {} while (data[++i].rent < pivot.rent);
		do {} while (data[--j].rent > pivot.rent);

		if (i >= j)
			return j;

		// Swap [i] and [j]
		Entry tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}

void QuickSortRent(Entry *data, int lo, int hi)
{
	if (lo < hi)
	{
		int p = PartitionRent(data, lo, hi);
		QuickSortRent(data, lo, p);
		QuickSortRent(data, p + 1, hi);
	}
}

int PartitionLocation(Entry *data, int lo, int hi)
{
	Entry pivot = data[lo + (hi - lo) / 2];
	int i = lo - 1;
	int j = hi + 1;

	for (;;)
	{
		do {} while (data[++i].location < pivot.location);
		do {} while (data[--j].location > pivot.location);

		if (i >= j)
			return j;

		// Swap [i] and [j]
		Entry tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}

void QuickSortLocation(Entry *data, int lo, int hi)
{
	if (lo < hi)
	{
		int p = PartitionLocation(data, lo, hi);
		QuickSortLocation(data, lo, p);
		QuickSortLocation(data, p + 1, hi);
	}
}

int PartitionSize(Entry *data, int lo, int hi)
{
	Entry pivot = data[lo + (hi - lo) / 2];
	int i = lo - 1;
	int j = hi + 1;

	for (;;)
	{
		do {} while (data[++i].size < pivot.size);
		do {} while (data[--j].size > pivot.size);

		if (i >= j)
			return j;

		// Swap [i] and [j]
		Entry tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}

void QuickSortSize(Entry *data, int lo, int hi)
{
	if (lo < hi)
	{
		int p = PartitionSize(data, lo, hi);
		QuickSortSize(data, lo, p);
		QuickSortSize(data, p + 1, hi);
	}
}

void QuickSort(Entry *data, int count, int type)
{
	if (count <= 1) return; // Added base case

	switch (type) {
	case 0:
		QuickSortRent(data, 0, count - 1);
		break;
	case 1:
		QuickSortLocation(data, 0, count - 1);
		break;
	case 2:
		QuickSortSize(data, 0, count - 1);
		break;
	}
}