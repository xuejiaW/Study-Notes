// AdvancedDesignAndAnalysisTechniques.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "RodCutting.h"
#include "Matrix.h"
#include "MatrixChainMultiplication.h"

void TestRodCutting();
void TestMatrixMultiply();
void TestMatrixChainMultiplication();

int main()
{
	//TestRodCutting();
	//TestMatrixMultiply();
	TestMatrixChainMultiplication();
}

void TestMatrixChainMultiplication()
{
	int matrixSizeArray[] = { 30,35,15,5,10,20,25 };
	Matrix* minMultiplications = new Matrix(6, 6);
	Matrix* minMultiplicationCut = new Matrix(6, 6);

	RecursiveMatrixChain(matrixSizeArray, minMultiplications, 0, 5);
	cout << "minMultiplications result in RecursiveMatrix is :" << endl;
	minMultiplications->PrintMatrix(15);
	cout << endl;

	MemoizedMatrixChain(matrixSizeArray, minMultiplications);
	cout << "minMultiplications result in MemoizedMatrix is :" << endl;
	minMultiplications->PrintMatrix(15);
	cout << endl;

	MatrixChainOrder(matrixSizeArray, minMultiplications, minMultiplicationCut);
	cout << "minMultiplications result in botton up is :" << endl;
	minMultiplications->PrintMatrix(15);
	cout << endl;

	cout << "minMultiplicationCut result is :" << endl;
	cout << endl;
	minMultiplicationCut->PrintMatrix(15);
	cout << endl;

	PrintOptimalParens(minMultiplicationCut, 0, 5);

	delete minMultiplications;
	delete minMultiplicationCut;
}

void TestMatrixMultiply()
{
	Matrix matrixA(2, 3);
	int matrixAData[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	matrixA.LoadData(matrixAData, 13);
	matrixA.PrintMatrix();

	cout << endl;

	Matrix matrixB(3, 4);
	matrixB.LoadData(matrixAData, 13);
	matrixB.PrintMatrix();

	cout << endl;

	Matrix* matrixC = matrixA.multiply(&matrixB);
	matrixC->PrintMatrix();
	delete matrixC;
}

void TestRodCutting()
{
	int rodLength = 10;
	int priceTable[] = { 0,1,5,8,9,10,17,17,20,24,30 };

	cout << "max price of CutRod is " << CutRod(priceTable, rodLength) << endl;
	cout << "max price of MemoizedCutRod is " << MemoizedCutRod(priceTable, rodLength) << endl;
	cout << "max price of BottomUpCutRod is " << BottomUpCutRod(priceTable, rodLength) << endl;
	cout << "max price of BottomUpCutRod is " << CutRodSolution(priceTable, rodLength) << endl;
}
