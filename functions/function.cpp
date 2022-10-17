#include "functions.h"

#include <iostream>

using namespace std;

void printArray(int* arr, int noElements) {
		for (int i = 0; i < noElements; ++i) {
				cout << arr[i] << " ";
		}

		cout << endl;
}