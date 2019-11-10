#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

void PrintFloatMatrix(float*** floatMatrix,int matrixSize)
{
	cout.setf(ios::left);
	cout << setw(7) << "";

	for (int u = 0; u < matrixSize; u++)
	{
		cout << setw(7) << u;
	}

	cout << endl;
	for (int u = 0; u < matrixSize; u++)
	{
		cout << setw(7) << u;
		for (int v = 0; v < matrixSize; v++)
		{
			cout << setiosflags(ios::fixed);
			cout << setprecision(1);
			if ((*floatMatrix)[u][v] == INT_MAX)
				cout << setw(7) << ".";
			else
				cout << setw(7) << (*floatMatrix)[u][v];
		}
		cout << endl;
	}
}
