#include "functions.h"

#include <iostream>

using namespace std;

int main() {
		int array[] = { 10, 20, 30 };
		int noElements = 3;
		printArray(array, noElements);

		const char* testString = "123";
		int sum = sumOfArray(testString);
		cout << "The sum is " << sum << endl;

		bool value = isPresent(testString, '4');
		cout << "Is present: " << value << endl;

		bool targetSumPresent = targetSum(array, noElements, 40);
		cout << "Target sum present: " << targetSumPresent << endl;

		return 0;
}