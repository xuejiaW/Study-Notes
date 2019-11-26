#pragma once

#include <iostream>
#include "Matrix.h"

using namespace std;

int LookupChain(int* matrixSizeArray, Matrix* minMultiplications, int i, int j);

int RecursiveMatrixChain(int* matrixSizeArray, Matrix* minMultiplications, int i, int j)
{
	if (i == j)
		return 0;
	minMultiplications->data[i][j] = INT_MAX;
	for (int k = i; k < j; k++)
	{
		int tempMin = RecursiveMatrixChain(matrixSizeArray, minMultiplications, i, k) +
			RecursiveMatrixChain(matrixSizeArray, minMultiplications, k + 1, j) + matrixSizeArray[i] * matrixSizeArray[k + 1] * matrixSizeArray[j + 1];
		if (tempMin < minMultiplications->data[i][j])
			minMultiplications->data[i][j] = tempMin;
	}

	return minMultiplications->data[i][j];
}

void MatrixChainOrder(int* matrixSizeArray, Matrix* minMultiplications, Matrix* minMultiplicationCut)
{

	int totalMatrixLength = minMultiplications->row;

	for (int i = 0; i < totalMatrixLength; i++)
		minMultiplications->data[i][i] = 0;

	for (int matrixLength = 2; matrixLength <= totalMatrixLength; matrixLength++)
	{
		for (int i = 0; i < totalMatrixLength - matrixLength + 1; i++)
		{
			int j = matrixLength + i - 1;
			minMultiplications->data[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				int tempMin = minMultiplications->data[i][k] + minMultiplications->data[k + 1][j] +
					matrixSizeArray[i] * matrixSizeArray[k + 1] * matrixSizeArray[j + 1];
				if (tempMin < minMultiplications->data[i][j])
				{
					minMultiplications->data[i][j] = tempMin;
					minMultiplicationCut->data[i][j] = k;
				}
			}
		}
	}
}

void MemoizedMatrixChain(int* matrixSizeArray, Matrix* minMultiplications)
{
	for (int i = 0; i < minMultiplications->row; i++)
	{
		for (int j = 0; j < minMultiplications->column; j++)
			minMultiplications->data[i][j] = INT_MAX;
	}
	LookupChain(matrixSizeArray, minMultiplications, 0, 5);
}

int LookupChain(int* matrixSizeArray, Matrix* minMultiplications, int i, int j)
{
	if (minMultiplications->data[i][j] < INT_MAX)
		return minMultiplications->data[i][j];
	if (i == j)
		minMultiplications->data[i][j] = 0;
	else
	{
		minMultiplications->data[i][j] = INT_MAX;
		for (int k = i; k < j; k++)
		{
			int tempMin = RecursiveMatrixChain(matrixSizeArray, minMultiplications, i, k) +
				RecursiveMatrixChain(matrixSizeArray, minMultiplications, k + 1, j) + matrixSizeArray[i] * matrixSizeArray[k + 1] * matrixSizeArray[j + 1];
			if (tempMin < minMultiplications->data[i][j])
				minMultiplications->data[i][j] = tempMin;
		}
	}
	return minMultiplications->data[i][j];
}

void PrintOptimalParens(Matrix* minMultiplicationsCut, int i, int j)
{
	if (i == j)
		cout << "A_" << i;
	else
	{
		cout << "(";
		int k = minMultiplicationsCut->data[i][j];
		PrintOptimalParens(minMultiplicationsCut, i, k);
		PrintOptimalParens(minMultiplicationsCut, k + 1, j);
		cout << ")";
	}
}