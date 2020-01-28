// AdvancedDataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Wheels.h"
#include "TestTxtParser.h"
#include "FabonacciHeap.h"

int calculate(int firstNumber, int targetNum, int remainToUse, int max);

int main(int argc, char* argv[])
{
	calculate(0, 4, 3, 7);
}

int calculate(int firstNumber, int targetNum, int remainToUse, int max)
{
	//cout << "Input is " << firstNumber << " : " << targetNum << " : " << remainToUse << endl;

	if (remainToUse == 0)
	{
		if (targetNum == 0)
		{
			cout << "This is the end of one try,succeed" << endl;
			return 1;
		}
		else
		{
			return -1;
		}
	}

	remainToUse--;
	int toUp = -1;

	for (int i = 1; i <= max; i++)
	{
		if (targetNum - i < 0)
			break;


		int end = calculate(i, targetNum - i, remainToUse, max);
		if (end == 1)
		{
			cout << "Number is " << i << endl;
			toUp = 1;
		}
	}
	//cout << "No answer" << endl;
	return toUp;
}