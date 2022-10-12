#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

char* copyString(char* msg) {
		char* result = new char[strlen(msg) + 1];
		// strcpy_s(result, strlen(msg), msg);
		strcpy(result, msg);

		return result;
}

char* concatenateWithSpace(char* msg1, char* msg2) {
		// strcat(msg1, " ");
		// strcat(msg1, msg2);

		// return msg1;

		char* result = new char[strlen(msg1) + strlen(msg2) + 2];
		strcpy(result, msg1);
		// strcpy(result + strlen(msg1), " ");
		result[strlen(msg1)] = ' ';
		strcpy(result + strlen(msg1) + 1, msg2);

		return result;
}

void printTokens(char* msg) {
		char* token = strtok(msg, " ");
		int idx = 1;

		// while (token != nullptr) {
		while (token) {
				cout << "Token " << idx++ << " is " << token << endl;
				token = strtok(nullptr, " ");
		}
}

void printTokensWithCopy(char* msg) {
		char* copy = copyString(msg);
		printTokens(copy);

		delete[] copy;
}

void toUpper(char* message) {
		int difference = 'a' - 'A';
		for (int i = 0; i < strlen(message); ++i) {
				if(message[i] >= 'a' && message[i] <= 'z')
				message[i] -= difference;
		}
}

int strstrCaseInsensitive(char* str, char* substr) {
		char* copyOfStr = copyString(str);
		char* copyOfSubstr = copyString(substr);

		toUpper(copyOfStr);
		toUpper(copyOfSubstr);

		char* result = strstr(copyOfStr, copyOfSubstr);
		// int idx = result != nullptr ? (result - copyOfStr) : -1;
		int idx = -1;
		if (result != nullptr) {
				idx = result - copyOfStr;
		}
		else {
				idx = -1;
		}

		delete[] copyOfSubstr;
		delete[] copyOfStr;

		return idx;
}

char** parseAndToUpper(char* message) {
		char** result = new char* [5];
		int idx = 0;
		char* token = strtok(message, " ");
		while (token) {
				char* copy = copyString(token);
				toUpper(copy);

				result[idx++] = copy;
				token = strtok(nullptr, " ");
		}

		return result;
}

int main() {
		char ch = 'a';
		char str[] = "a";
		// const char* str2 = "a";

		cout << "`ch` value " << ch << endl;

		char str2[] = "hello world";
		cout << "length of `str2` is " << strlen(str2) << endl;

		char* copyOfStr2 = copyString(str2);
		cout << "`copyOfStr2` value " << copyOfStr2 << endl;

		cout << "`strcmp(str2, copyOfStr2): `" << strcmp(str2, copyOfStr2) << endl;
		cout << "`str2 == copyOfStr2`: " << (str2 == copyOfStr2 ? "true" : "false") << endl;

		char* indexW = strchr(str2, 'w');
		cout << "`indexW` value " << indexW << endl;
		cout << "`indexW` index " << (indexW - str2) << endl;

		char* indexWorld = strstr(str2, "world");
		cout << "`indexWorld` value " << indexWorld << endl;
		cout << "`indexWorld` index " << (indexWorld - str2) << endl;

		printTokens(str2);
		cout << "`str2` value after strtok: " << str2 << endl;

		printTokensWithCopy(copyOfStr2);
		cout << "`copyOfStr2` value after strtok: " << copyOfStr2 << endl;

		// char buffer1[50] = "";
		// cout << "input `buffer1` value: ";
		// cin >> buffer1;
		// cout << "`buffer1` value: " << buffer1 << endl;

		// char buffer2[50] = "";
		// cout << "input `buffer2` value: ";
		// cin >> buffer2;
		// cout << "`buffer2` value: " << buffer2 << endl;

		// char buffer3[100] = "";
		// strcat(buffer3, buffer1);
		// strcat(buffer3, buffer2);
		// cout << "`buffer3` value: " << buffer3 << endl;

		// strcat(buffer1, buffer2);

		// char* result = concatenateWithSpace(buffer1, buffer2);
		// cout << "`buffer1` value: " << result << endl;

		char smallTest[] = "HelLO";
		toUpper(smallTest);
		cout << "`smallTest` value: " << smallTest << endl;

		char buff1[] = "HELLO WORLD";
		char buff2[] = "world";
		int idxOfBuff2 = strstrCaseInsensitive(buff1, buff2);
		cout << "`idxOfBuff2` value: " << idxOfBuff2 << endl;

		char buff3[] = "hello world";
		char** tokens = parseAndToUpper(buff3);
		for (int i = 0; i < 2; ++i) {
				cout << "Token " << i << " : " << tokens[i] << endl;
		}

		return 0;
}