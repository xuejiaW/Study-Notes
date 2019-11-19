#pragma once
#include <iostream>
using namespace std;

int MemoizedCutRodAux(int* priceTable, int* maxPriceMemo, int length);

int CutRod(int* priceTable, int rodLength)
{
	if (rodLength == 0)
		return 0;

	int price = INT_MIN;
	for (int i = 1; i <= rodLength; i++) //cut from 1 to length(equals to no cuts)
	{
		int tempPrice = priceTable[i] + CutRod(priceTable, rodLength - i);
		if (tempPrice > price)
			price = tempPrice;
	}
	return price;
}


int MemoizedCutRod(int* priceTable, int rodLength)
{
	//create an array from 0 to rodLength, array length is (rodLength+1)
	//array[0] = 0, array[rodLength] means the max PriceMemo for rod of rodLength
	int* maxPriceMemo = new int[rodLength + 1];
	for (int i = 0; i < rodLength + 1; i++)
	{
		maxPriceMemo[i] = INT_MIN;
	}

	int maxPrice = MemoizedCutRodAux(priceTable, maxPriceMemo, rodLength);

	for (int i = 1; i < rodLength + 1; i++)
	{
		cout << "Max price for " << i << " is " << maxPriceMemo[i] << endl;
	}
	return maxPrice;
}

int MemoizedCutRodAux(int* priceTable, int* maxPriceMemo, int rodLength)
{
	if (maxPriceMemo[rodLength] > 0)//has record
		return maxPriceMemo[rodLength];

	int price = INT_MIN;
	if (rodLength == 0)
		price = 0;
	else
		for (int i = 1; i <= rodLength; i++)
		{
			int tempPrice = priceTable[i] + MemoizedCutRodAux(priceTable, maxPriceMemo, rodLength - i);
			if (tempPrice > price)
				price = tempPrice;
		}

	maxPriceMemo[rodLength] = price;
	return price;
}

int BottomUpCutRod(int* priceTable, int rodLength)
{
	//Init for maxPriceMemo
	int* maxPriceMemo = new int[rodLength + 1];
	for (int i = 0; i < rodLength + 1; i++)
	{
		maxPriceMemo[i] = INT_MIN;
	}

	maxPriceMemo[0] = 0;

	//Calculate the MaxPriceMemo for length from 1 to length
	for (int i = 1; i <= rodLength; i++)
	{
		//Calculate cutRod for length = i
		int price = INT_MIN;

		for (int j = 1; j <= i; j++)
		{
			int tempPrice = priceTable[j] + maxPriceMemo[i - j];
			if (tempPrice > price)
				price = tempPrice;
		}

		maxPriceMemo[i] = price;
	}

	for (int i = 1; i < rodLength + 1; i++)
	{
		cout << "Max price for " << i << " is " << maxPriceMemo[i] << endl;
	}

	return maxPriceMemo[rodLength];
}

void ExtendedBottomUpCutRod(int* priceTable, int rodLength, int* maxPriceMemo, int* cutLength)
{
	for (int i = 0; i < rodLength + 1; i++)
	{
		maxPriceMemo[i] = INT_MIN;
	}

	maxPriceMemo[0] = 0;

	//Calculate the MaxPriceMemo for length from 1 to length
	for (int i = 1; i <= rodLength; i++)
	{
		//Calculate cutRod for length = i
		int price = INT_MIN;

		for (int j = 1; j <= i; j++)
		{
			int tempPrice = priceTable[j] + maxPriceMemo[i - j];
			if (tempPrice > price)
			{
				price = tempPrice;
				cutLength[i] = j;
			}
		}

		maxPriceMemo[i] = price;
	}

	//for (int i = 1; i < rodLength + 1; i++)
	//{
	//	//cout << "Max price for " << i << " is " << maxPriceMemo[i] << endl;
	//	cout << "First cut length for " << i << " is " << cutLength[i] << endl;
	//}
}

int CutRodSolution(int* priceTable, int rodLength)
{
	int* maxPriceMemo = new int[rodLength + 1];
	int* cutLength = new int[rodLength + 1];
	ExtendedBottomUpCutRod(priceTable, rodLength, maxPriceMemo, cutLength);


	int remainLength = rodLength;
	while (remainLength > 0)
	{
		int length = cutLength[remainLength];
		cout << "to Cut " << length << endl;
		remainLength = remainLength - length;
	}

	return maxPriceMemo[rodLength];
}