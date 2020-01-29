#include <iostream>
#include <math.h>
using namespace std;

class Heap
{
public:
	Heap(int* dataArray, int dataLength, int arrayLength)
	{
		this->dataArray = dataArray;
		this->arrayLength = arrayLength;
		this->dataLength = dataLength;
		BuildMaxHeap();
	}

	void heapSort()
	{
		BuildMaxHeap();
		for (int tempDataLength = dataLength; tempDataLength > 1; tempDataLength--)
		{
			int temp = dataArray[0];
			dataArray[0] = dataArray[tempDataLength - 1];
			dataArray[tempDataLength - 1] = temp;

			MaxHeapify(0, tempDataLength - 1);
		}

		//This part is not related to the heapsort
		//Output the sort result and recover the heap 
		HeapDebug();
		BuildMaxHeap();
	}

	int Maximum()
	{
		return dataArray[0];
	}

	int ExtractMaximum()
	{
		int max = dataArray[0];
		dataArray[0] = dataArray[--dataLength];

		if (dataLength != 0)
			MaxHeapify(0, dataLength);

		return max;
	}

	bool IsEmpty()
	{
		return dataLength == 0;
	}

	void HeapDebug()
	{
		cout << "Data value is : ";
		for (int i = 0; i < dataLength; i++)
		{
			cout << " " << dataArray[i] << " ";
		}
		cout << endl;
	}

	void IncreaseKey(int index, int newValue)
	{
		if (index >= dataLength)
		{
			cout << "Invalid index in IncreaseKey" << endl;
			return;
		}
		if (dataArray[index] >= newValue)
		{
			cout << "No need to update" << endl;
			return;
		}

		dataArray[index] = newValue;
		int parentIndex = parent(index);
		cout << "parent index is " << parentIndex << endl;
		while (index > 0 && dataArray[parentIndex] < newValue)
		{
			dataArray[index] = dataArray[parentIndex];
			dataArray[parentIndex] = newValue;
			index = parent(index);
			parentIndex = parent(index);
		}
	}

	void Insert(int value)
	{
		dataLength++;
		if (dataLength > arrayLength)
		{
			cout << "The heap is full" << endl;
			return;
		}

		dataArray[dataLength - 1] = -INT_MAX;
		IncreaseKey(dataLength - 1, value);
	}

	~Heap()
	{
	}

private:
	int* dataArray;
	int dataLength;
	int arrayLength;

	int parent(int index)
	{
		return ceil(index / 2.0) - 1;
	}

	int left(int index)
	{
		return index * 2 + 1;
	}

	int right(int index)
	{
		return index * 2 + 2;
	}


	void MaxHeapify(int index, int dataLength)
	{
		if (index >= dataLength)
		{
			cout << "Invalid index " << index << endl;
			return;
		}

		int largest = index;
		int lIndex = left(index);
		int rIndex = right(index);
		if (lIndex < dataLength)
			largest = dataArray[index] > dataArray[lIndex] ? index : lIndex;
		if (rIndex < dataLength)
			largest = dataArray[rIndex] > dataArray[largest] ? rIndex : largest;


		if (largest != index)
		{
			int temp = dataArray[index];
			dataArray[index] = dataArray[largest];
			dataArray[largest] = temp;
			MaxHeapify(largest, dataLength);
		}
	}

	void BuildMaxHeap()
	{
		for (int i = dataLength / 2 - 1; i >= 0; i--)
			MaxHeapify(i, dataLength);
	}
};
