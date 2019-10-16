#pragma once
#include <climits>
#include "../CreateTestArray.h"

void Merge(int* array, int leftStartIndex, int middleIndex, int rightEndIndex);

void MergeSort(int* array, int leftStartIndex, int rightEndIndex)
{
	if (leftStartIndex == rightEndIndex)
		return;

	int centerIndex = (leftStartIndex + rightEndIndex) / 2;
	MergeSort(array, leftStartIndex, centerIndex);
	MergeSort(array, centerIndex + 1, rightEndIndex);
	Merge(array, leftStartIndex, centerIndex, rightEndIndex);

}

void Merge(int* array, int leftStartIndex, int middleIndex, int rightEndIndex)
{
	int leftPartLength = middleIndex - leftStartIndex + 1;
	int rightPartLength = rightEndIndex - middleIndex;

	int* leftArray = new int[leftPartLength + 1];
	int* rightArray = new int[rightPartLength + 1];

	for (int i = 0; i < leftPartLength; i++)
		leftArray[i] = array[leftStartIndex + i];

	for (int i = 0; i < rightPartLength; i++)
		rightArray[i] = array[middleIndex + 1 + i];


	//Make the last index to be max
	leftArray[leftPartLength] = INT_MAX;
	rightArray[rightPartLength] = INT_MAX;

	int leftArrayIndex = 0, rightArrayIndex = 0;

	for (int i = leftStartIndex; i <= rightEndIndex; i++)
	{
		if (leftArray[leftArrayIndex] < rightArray[rightArrayIndex])
			array[i] = leftArray[leftArrayIndex++];
		else
			array[i] = rightArray[rightArrayIndex++];
	}

	delete[] leftArray;
	delete[] rightArray;
}
