#pragma once

#include <iomanip>
#include <iostream>

using namespace std;

class Matrix
{
public:
	int** data;
	int row;
	int column;
	Matrix(int row, int column, bool initData = true)
	{
		this->row = row;
		this->column = column;
		data = new int* [row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new int[column];
		}

		if (initData)
			LoadData(nullptr, -1);//fill matrix up with 0
	}

	Matrix(const Matrix& sub_11, const Matrix& sub_12, const Matrix& sub_21, const Matrix& sub_22) :Matrix(sub_11.row + sub_21.row, sub_11.column + sub_12.column, false)
	{
		for (int i = 0; i < sub_11.row; i++)
		{
			for (int j = 0; j < sub_11.column; ++j)
			{
				data[i][j] = sub_11.data[i][j];
			}
		}

		for (int i = 0; i < sub_12.row; i++)
		{
			for (int j = 0; j < sub_12.column; ++j)
			{
				data[i][sub_11.column + j] = sub_12.data[i][j];
			}
		}

		for (int i = 0; i < sub_21.row; i++)
		{
			for (int j = 0; j < sub_21.column; ++j)
			{
				data[sub_11.row + i][j] = sub_21.data[i][j];
			}
		}


		for (int i = 0; i < sub_22.row; i++)
		{
			for (int j = 0; j < sub_22.column; ++j)
			{
				data[sub_11.row + i][sub_11.column + j] = sub_22.data[i][j];
			}
		}
	}

	Matrix(const Matrix& pt) :Matrix(pt.row, pt.column, false)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				data[i][j] = pt.data[i][j];
			}
		}
	}

	Matrix& operator=(const Matrix& matrix)
	{
		Matrix result(matrix.row, matrix.column, false);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				result.data[i][j] = matrix.data[i][j];
			}
		}
		return result;
	}

	Matrix operator+(const Matrix& matrix)
	{
		Matrix result(matrix.row, matrix.column, false);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				result.data[i][j] = data[i][j] + matrix.data[i][j];
			}
		}
		return result;
	}

	Matrix operator-(const Matrix& matrix)
	{
		Matrix result(matrix.row, matrix.column, false);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				result.data[i][j] = data[i][j] - matrix.data[i][j];
			}
		}
		return result;
	}


	void LoadData(int* toLoadData, int dataLength)
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


	void PrintMatrix(int width)
	{
		cout.setf(ios::left);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				cout << setiosflags(ios::fixed);
				cout << setw(width) << data[i][j];
			}
			cout << endl;
		}
	}

	~Matrix()
	{
		//cout << "Delete a matrix" << endl;
		if (data == nullptr)
			return;

		for (int i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
};

Matrix createSubMatrix(const Matrix& originMatrix, int startRow, int startColumn, int subMatSize)
{
	Matrix result(subMatSize, subMatSize);
	for (int i = 0; i < subMatSize; i++)
	{
		for (int j = 0; j < subMatSize; j++)
		{
			result.data[i][j] = originMatrix.data[startRow + i][startColumn + j];
		}
	}
	return result;
}

Matrix MatrixMultiply(const Matrix& A, const Matrix& B)
{
	Matrix result(A.row, B.column);

	for (int i = 0; i < A.row; i++)
	{
		for (int j = 0; j < B.column; ++j)
		{
			for (int k = 0; k < A.column; k++)
			{
				result.data[i][j] = result.data[i][j] + A.data[i][k] * B.data[k][j];
			}
		}
	}
	return result;
}

Matrix* MatrixMultiply_Recursive(Matrix* A, Matrix* B, Matrix* result, int resultStartRow, int resultStartCol,
	int aStartRow, int aStartCol, int bStartRow, int bStartColumn, int subMatSize)
{
	//This method assume that the size of Matrix is n*n where n is an exact power of 2
	//StartRow and startColumn indicate where subMatrix starts, three pairs of value individually for A,B and result
	//The subMatrix of A and B should be the same size, so there is only on subMatrixSize value

	if (result == nullptr)
		result = new Matrix(A->row, B->column);

	if (subMatSize == 1)
		result->data[resultStartRow][resultStartCol] = result->data[resultStartRow][resultStartCol] + A->data[aStartRow][aStartCol] * B->data[bStartRow][bStartColumn];
	else
	{
		subMatSize /= 2;
		//result 11
		MatrixMultiply_Recursive(A, B, result, resultStartRow, resultStartCol, aStartRow, aStartCol, bStartRow, bStartColumn, subMatSize);//A11*B11
		MatrixMultiply_Recursive(A, B, result, resultStartRow, resultStartCol, aStartRow, aStartCol + subMatSize, bStartRow + subMatSize, bStartColumn, subMatSize);//A12*B21;
		//result 12
		MatrixMultiply_Recursive(A, B, result, resultStartRow, resultStartCol + subMatSize, aStartRow, aStartCol, bStartRow, bStartColumn + subMatSize, subMatSize);//A11*B12
		MatrixMultiply_Recursive(A, B, result, resultStartRow, resultStartCol + subMatSize, aStartRow, aStartCol + subMatSize, bStartRow + subMatSize, bStartColumn + subMatSize, subMatSize);//A12*B22
		//result 21
		MatrixMultiply_Recursive(A, B, result, resultStartRow + subMatSize, resultStartCol, aStartRow + subMatSize, aStartCol, bStartRow, bStartColumn, subMatSize);//A21*B11
		MatrixMultiply_Recursive(A, B, result, resultStartRow + subMatSize, resultStartCol, aStartRow + subMatSize, aStartCol + subMatSize, bStartRow + subMatSize, bStartColumn, subMatSize);//A22*B21
		//result 22
		MatrixMultiply_Recursive(A, B, result, resultStartRow + subMatSize, resultStartCol + subMatSize, aStartRow + subMatSize, aStartCol, bStartRow, bStartColumn + subMatSize, subMatSize);//A21*B12
		MatrixMultiply_Recursive(A, B, result, resultStartRow + subMatSize, resultStartCol + subMatSize, aStartRow + subMatSize, aStartCol + subMatSize, bStartRow + subMatSize, bStartColumn + subMatSize, subMatSize);//A22*B22
	}
	return result;
}

Matrix MatrixMultiply_Strassen(const Matrix& A, const Matrix& B)
{
	if (A.row == 1 && A.column == 1 && B.row == 1 && B.column == 1)
	{
		Matrix result(A.row, B.column);
		result.data[0][0] += A.data[0][0] * B.data[0][0];
		return result;
	}
	else
	{
		Matrix A_11 = createSubMatrix(A, 0, 0, A.row / 2), A_12 = createSubMatrix(A, 0, A.column / 2, A.row / 2);
		Matrix A_21 = createSubMatrix(A, A.row / 2, 0, A.row / 2), A_22 = createSubMatrix(A, A.row / 2, A.column / 2, A.row / 2);

		Matrix B_11 = createSubMatrix(B, 0, 0, B.row / 2), B_12 = createSubMatrix(B, 0, B.column / 2, B.row / 2);
		Matrix B_21 = createSubMatrix(B, B.row / 2, 0, B.row / 2), B_22 = createSubMatrix(B, B.row / 2, B.column / 2, B.row / 2);

		Matrix P_1 = MatrixMultiply_Strassen(A_11, B_12) - (MatrixMultiply_Strassen(A_11, B_22));
		Matrix P_2 = MatrixMultiply_Strassen(A_11, B_22) + (MatrixMultiply_Strassen(A_12, B_22));
		Matrix P_3 = MatrixMultiply_Strassen(A_21, B_11) + (MatrixMultiply_Strassen(A_22, B_11));
		Matrix P_4 = MatrixMultiply_Strassen(A_22, B_21) - (MatrixMultiply_Strassen(A_22, B_11));
		Matrix P_5 = MatrixMultiply_Strassen(A_11, B_11) + (MatrixMultiply_Strassen(A_11, B_22)) + (MatrixMultiply_Strassen(A_22, B_11)) + (MatrixMultiply_Strassen(A_22, B_22));
		Matrix P_6 = MatrixMultiply_Strassen(A_12, B_21) + (MatrixMultiply_Strassen(A_12, B_22)) - (MatrixMultiply_Strassen(A_22, B_21)) - (MatrixMultiply_Strassen(A_22, B_22));
		Matrix P_7 = MatrixMultiply_Strassen(A_11, B_11) + (MatrixMultiply_Strassen(A_11, B_12)) - (MatrixMultiply_Strassen(A_21, B_11)) - (MatrixMultiply_Strassen(A_21, B_12));

		Matrix C_11 = P_5 + (P_4)-(P_2)+(P_6);
		Matrix C_12 = P_1 + (P_2);
		Matrix C_21 = P_3 + (P_4);
		Matrix C_22 = P_5 + (P_1)-(P_3)-(P_7);

		Matrix result(C_11, C_12, C_21, C_22);
		return result;
	}
}