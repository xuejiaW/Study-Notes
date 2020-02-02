#pragma once

void InsertationSort(int* array, int arraySize)
{
	for (int i = 1; i < arraySize; i++)
	{
		int key = array[i];
		int startIndex = i - 1;
		while (startIndex >= 0 && array[startIndex] > key)
		{
			array[startIndex + 1] = array[startIndex];
			startIndex--;
		}
		array[++startIndex] = key;
	}
}
