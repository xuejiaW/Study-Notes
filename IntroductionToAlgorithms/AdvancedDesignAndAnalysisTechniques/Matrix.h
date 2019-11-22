#pragma once

#include <iostream>
#include <iomanip>


using namespace std;

class Matrix
{
public:
	int** data;
	int row;
	int column;
	Matrix(int row, int column);
	~Matrix();
	void PrintMatrix();
	Matrix* multiply(Matrix* mat);
	void LoadData(int* data, int dataLength);
private:
};


void Matrix::LoadData(int* toLoadData, int dataLength)
{
	int dataIndex = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			data[i][j] = dataIndex < dataLength ? toLoadData[dataIndex++] : 0;
		}
	}
}

Matrix* Matrix::multiply(Matrix* mat)
{
	int matColumn = mat->column;
	Matrix* result = new Matrix(row, matColumn);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < matColumn; j++)
		{
			result->data[i][j] = 0;
			for (int k = 0; k < column; k++)
			{
				result->data[i][j] = result->data[i][j] + data[i][k] * mat->data[k][j];
			}
		}
	}
	return result;
}

void Matrix::PrintMatrix()
{
	cout.setf(ios::left);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << setiosflags(ios::fixed);
			cout << setw(7) << data[i][j];
		}
		cout << endl;
	}
}

Matrix::Matrix(int row, int column)
{
	this->row = row;
	this->column = column;
	data = new int* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int[column];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < row; i++)
	{
		delete[] data[i];
	}

	delete[] data;
}
