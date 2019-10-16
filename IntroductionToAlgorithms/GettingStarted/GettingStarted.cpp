// GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../CreateTestArray.h"
#include "InsertionSort.h"
#include "MergeSort.h"

using namespace std;

int main()
{
	int testArraySize = 0;
	int* testArray = CreateTestArray(testArraySize);

	//InsertationSort(testArray, testArraySize);
	MergeSort(testArray, 0, testArraySize - 1);

	ShowTheArray(testArray, testArraySize);
	DeleteTestArray(testArray);
}

