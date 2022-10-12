#include <iostream>

using namespace std;

void printArray(int* array, int noElements) {
		for (int i = 0; i < noElements; ++i) {
				cout << array[i] << " ";
		}

		cout << endl;
}

void addElements(int* array, int& currIdx, int newElement, int capacity) {
		if (array == nullptr || currIdx >= capacity) {
				return;
		}

		array[currIdx] = newElement;
		++currIdx;
}

int* addElements(int* array, int noElements, int newElement) {
		int* result = new int[noElements + 1];
		//for (int i = 0; i < noElements; ++i) {
		//		result[i] = array[i];
		// }

		memcpy(result, array, noElements * sizeof(int));
		result[noElements] = newElement;

		return result;
}

// don't do this -> undefined behaviour
int* addElements2(int* array, int noElements, int newElement) {
		int result[1024];

		memcpy(result, array, noElements * sizeof(int));
		result[noElements] = newElement;

		return result;
}

int main() {
		int noElements = 5;
		int array[5];
		printArray(array, noElements);

		cout << array << endl;

		for (int i = 0; i < noElements; ++i) {
				array[i] = i;
		}
		printArray(array, noElements);

		int array2[] = { 0, 1, 2, 3, 4 };
		printArray(array2, noElements);

		const int noElements2 = 1024;
		int buffer[noElements2];
		int currIdx = 0;

		addElements(buffer, currIdx, 1, noElements2);
		addElements(buffer, currIdx, 2, noElements2);
		addElements(buffer, currIdx, 3, noElements2);
		printArray(buffer, 3);

		int dynamicNoElements = 5;
		int* dynamicArray = (int*)malloc(dynamicNoElements * sizeof(int));
		for (int i = 0; i < dynamicNoElements; ++i) {
				dynamicArray[i] = i * 2;
				// *(dynamicArray + i * sizeof(int)) = i * 2;
		}
		cout << "Dynamic array" << endl;
		printArray(dynamicArray, dynamicNoElements);
		free(dynamicArray);

		int noElements3 = 10;
		int* array3 = new int[noElements3];
		for (int i = 0; i < noElements3; ++i) {
				array3[i] = i * 3;
		}
		printArray(array3, noElements3);
		delete[] array3;

		int* result = addElements(array, noElements, 7);
		printArray(result, noElements + 1);
		delete[] result;

		int* result2 = addElements2(array, noElements, 8);
		printArray(result2, noElements + 1);

		int noRows = 3;
		int noCols = 3;
		int** matrix;
		matrix = new int*[noRows];
		for (int i = 0; i < noRows; ++i) {
				matrix[i] = new int[noCols];
		}

		for (int i = 0; i < noRows; ++i) {
				for (int j = 0; j < noCols; ++j) {
						matrix[i][j] = i + j;
				}
		}

		cout << "Printing the matrix" << endl;
		for (int i = 0; i < noRows; ++i) {
				for (int j = 0; j < noCols; ++j) {
						cout << matrix[i][j] << " ";
				}
				cout << endl;
		}

		int sum1 = 0; // main diagonal sum
		int sum2 = 0; // second diagonal sum
		for (int i = 0; i < noRows; ++i) {
				for (int j = 0; j < noCols; ++j) {
						if (i == j) {
								sum1 += matrix[i][j];
						}

						if (i + j == noRows - 1) {
								sum2 += matrix[i][j];
						}
				}
		}
		cout << "Main diagonal sum: " << sum1 << endl;
		cout << "Second diagonal sum: " << sum2 << endl;

		for (int i = 0; i < noRows; ++i) {
				delete[] matrix[i];
		}
		delete[] matrix;

		return 0;
}