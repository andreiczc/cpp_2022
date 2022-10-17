#pragma once

__declspec(dllexport) void printArray(int* arr, int noElements);

__declspec(dllexport) int sumOfArray(const char* str);

__declspec(dllexport) bool isPresent(const char* str, char element);

__declspec(dllexport) bool targetSum(int* arr, int noElements, int targetSum);