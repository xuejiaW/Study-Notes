// GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../CreateTestArray.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "MaximumSubarray_BruteForce.h"
#include "MaximumSubarray_DivideAConquer.h"
#include "MatrixMultiply.h"

using namespace std;

void TestSortFunction();
void TestMaximumSubarray();
void TestMatrixMultiply();

int main()
{
	//TestSortFunction();
	//TestMaximumSubarray();
	TestMatrixMultiply();
}


void TestMatrixMultiply()
{
	int aData[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }, bData[] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32 };
	Matrix A(4, 4), B(4, 4);
	A.LoadData(aData, 16);
	B.LoadData(bData, 16);

	cout << "A is: " << endl;
	A.PrintMatrix(7);
	cout << endl << endl;

	cout << "B is: " << endl;
	B.PrintMatrix(7);
	cout << endl << endl;

	cout << "Matrix multiply result is: " << endl;
	Matrix result = MatrixMultiply(A, B);
	result.PrintMatrix(7);
	cout << endl << endl;

	cout << "Matrix recursive multiply result is: " << endl;
	Matrix* result_recursive = MatrixMultiply_Recursive(&A, &B, nullptr, 0, 0, 0, 0, 0, 0, 4);
	result_recursive->PrintMatrix(7);
	delete result_recursive;
	cout << endl << endl;

	cout << "Matrix strassen multiply result is: " << endl;
	Matrix result_Strassen = MatrixMultiply_Strassen(A, B);
	result_Strassen.PrintMatrix(7);
	cout << endl << endl;
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
