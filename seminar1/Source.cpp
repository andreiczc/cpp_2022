#include <iostream>

int sumOfArray();

int sumOfTwoElements(int a, int b) {
		return a + b;
}

int sumOfTwoElements2(int& a, int b) {
		a++;
		b++;

		return a + b;
}

int sumOfTwoElements3(int* a, int b) {
		(*a)++;
		b++;

		return (*a) + b;
}

int sumOfArray2(int* array, int noElements) {
		int sum = 0;

		for (int i = 0; i < noElements; ++i) {
				sum += array[i];
		}

		return sum;
}

int minOfArray(int* array, int noElements) {
		if (array == nullptr) {
				return -1;
		}

		int min = array[0];
		for (int i = 0; i < noElements; ++i) {
				if (min > array[i]) {
						min = array[i];
				}
		}

		return min;
}

int sumOfEvenElements(int* array, int noElements) {
		if (array == nullptr) {
				return -1;
		}

		int sum = 0;

		for (int i = 0; i < noElements; ++i) {
				if (array[i] % 2 == 0) {
						sum += array[i];
				}
		}

		return sum;
}

int power(int num, int pwr) {
		if (pwr == 0) {
				return 1;
		}

		return num * power(num, pwr - 1);
}

int sumOfEvenIdx(int* array, int noElements) {
		if (array == nullptr) {
				return -1;
		}

		int sum = 0;
		for (int i = 0; i < noElements; i += 2) {
				sum += array[i];
		}

		return sum;
}

int main() {
		int variable1 = 0;
		variable1 = 5;

		printf("The value of `variable1` is %d\n", variable1);

		int factorial = 1;
		for (int i = 1; i <= 5; i++) {
				// factorial = factorial * i;
				factorial *= i;
		}
		printf("The value of `factorial` is %d\n", factorial);

		int idx = 1;
		int factorial2 = 1;
		while (idx <= 5) {
				factorial2 *= idx++;
		}
		printf("The value of `factorial2` is %d\n", factorial2);

		int* pointer = nullptr;
		printf("The value of `pointer` is %p\n", pointer);

		pointer = &variable1;
		*pointer = 22;

		printf("The value pointed by `pointer` is %d\n", *pointer);
		printf("The value of `variable1` is %d\n", variable1);

		int sum = sumOfArray();
		printf("The value of `sum` is %d\n", sum);

		int a = 1;
		int b = 2;
		int sum2 = sumOfTwoElements(a, b);
		printf("The value of `sum2` is %d\n", sum2);
		printf("The value of `a` is %d\n", a);
		printf("The value of `b` is %d\n", b);

		int sum3 = sumOfTwoElements2(a, b);
		printf("The value of `sum3` is %d\n", sum3);
		printf("The value of `a` is %d\n", a);
		printf("The value of `b` is %d\n", b);

		int sum4 = sumOfTwoElements3(&a, b);
		printf("The value of `sum4` is %d\n", sum4);
		printf("The value of `a` is %d\n", a);
		printf("The value of `b` is %d\n", b);

		int array[] = { 10, 20, 30, 40 };
		int sum5 = sumOfArray2(array, 4);
		printf("The value of `sum5` is %d\n", sum5);

		int min = minOfArray(array, 4);
		printf("The value of `min` is %d\n", min);

		minOfArray(nullptr, 4);

		int array2[] = { 11, 5, 10, 24, 19 };
		int sum6 = sumOfEvenElements(array2, 5);
		printf("The value of `sum6` is %d\n", sum6);

		int sum7 = sumOfEvenIdx(array2, 5);
		printf("The value of `sum7` is %d\n", sum7);

		int p = power(2, 2);
		printf("The value of `p` is %d\n", p);

		return 0;
}

int sumOfArray() {
		int array[] = { 10, 20, 30, 40 };
		int noElements = 4;
		int sum = 0;

		int* ptr = array;

		int i = 0;
		while (i < noElements) {
				sum += array[i++];
		}

		// for (int i = 0; i < noElements; i++) {
		//		sum += array[i];
		// }

		return sum;
}