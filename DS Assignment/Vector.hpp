/*
	Title: How to implement our own Vector Class in C++?
	Author : mv15
	Date : 2022
	Code version : N/A
	Availability : https://www.geeksforgeeks.org/how-to-implement-our-own-vector-class-in-c/
*/

#pragma once

template <typename T> 
class Vector {
	T *arr;
	int capacity;
	int current;

	public:
	Vector() {
		arr = new T[1];
		capacity = 1;
		current = 0;
	}

	void push(T data) {
		if (current == capacity) {
			T *temp = new T[2 * capacity];
			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}

			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[current] = data;
		current++;
	}

	void push(T data, int index) {
		if (index == capacity) push(data);
		else arr[index] = data;
	}

	T get(int index) {
		if (index < current) return arr[index];
	}

	void pop() {
		current--;
	}

	int size() {
		return current;
	}

	int getCapacity() {
		return capacity;
	}

	T *getValues() {
		return arr;
	}

	void print() {
		for (int i = 0; i < current; i++) {
			cout << arr[i] << endl;
		}
	}
};