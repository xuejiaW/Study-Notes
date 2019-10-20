// GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../CreateTestArray.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "MaximumSubarray_BruteForce.h"
#include "MaximumSubarray_DivideAConquer.h"

using namespace std;

void TestSortFunction();
void TestMaximumSubarray();

int main()
{
	//TestSortFunction();
	TestMaximumSubarray();
}

void TestSortFunction()
{
	int testArraySize = 0;
	int* testArray = CreateTestArray(testArraySize);

	InsertationSort(testArray, testArraySize);
	//MergeSort(testArray, 0, testArraySize - 1);

	ShowTheArray(testArray, testArraySize);
	DeleteTestArray(testArray);
}


void TestMaximumSubarray()
{
	int testArraySize = 0, leftIndex = 0, rightIndex = 0;
	int* testArray = CreateTestArray(testArraySize);

	//int maxSum = FindMaximumSubarray_BruteForce(testArray, testArraySize, leftIndex, rightIndex);
	int maxSum = FindMaximumSubarray_DivideAConquer(testArray, 0, testArraySize - 1, leftIndex, rightIndex);

	cout << "Max sum is " << maxSum << " ,left Index is " << leftIndex << " ,right Index is " << rightIndex << endl;
}
