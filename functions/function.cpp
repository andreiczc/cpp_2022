#include "functions.h"

#include <iostream>

using namespace std;

void printArray(int* arr, int noElements) {
		for (int i = 0; i < noElements; ++i) {
				cout << arr[i] << " ";
		}

		cout << endl;
}

int sumOfArray(const char* str) {
		int sum = 0;

		for (int i = 0; i < strlen(str); ++i) {
				int currNumber = str[i] - '0';
				sum += currNumber;
		}

		return sum;
}

bool isPresent(const char* str, char element) {
		return strchr(str, element) != nullptr;
}

static bool isPresent(int* array, int noElements, int target) {
		for (int i = 0; i < noElements; ++i) {
				if (array[i] == target) {
						return true;
				}
		}

		return false;
}

bool targetSum(int* arr, int noElements, int targetSum) {
		for (int i = 0; i < noElements; ++i) {
				int difference = targetSum - arr[i];
				if (isPresent(arr, noElements, difference)) {
						return true;
				}
		}

		return false;
}