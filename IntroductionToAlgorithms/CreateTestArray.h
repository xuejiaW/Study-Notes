#pragma once

#include <iostream>
using namespace std;

int* CreateTestArray(int& testArraySize)
{
	// Return: the size of the test Array
	cout << "Please enter the test Array size: ";
	cin >> testArraySize;
	int* testArray = new int[testArraySize];
	cout << "Please enter every element of the test Array: \n";

	for (int i = 0; i < testArraySize; i++)
	{
		cin >> testArray[i];
	}


	return testArray;
}

void ShowTheArray(int* testArray, int testArraySize)
{
	cout << "Array elements are: ";
	for (int i = 0; i < testArraySize; i++)
	{
		cout << testArray[i] << " ";
	}
	cout << "\n";
}

void DeleteTestArray(int* testArray)
{
	delete[] testArray;
}

