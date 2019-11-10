#pragma once

#include <iostream>
#include "AdjMatrixGraph.h"
using namespace std;

float** FloydWarshallShortest(AdjMatrixGraph* matrixGraph)
{
	int graphSize = matrixGraph->graphSize;
	float** minDistMat = (float**)malloc(sizeof(float*) * graphSize);
	float** graphEdges = matrixGraph->graphEdges;
	for (int i = 0; i < graphSize; i++)
		minDistMat[i] = (float*)malloc(sizeof(float) * graphSize);


	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			if (u == v)
				minDistMat[u][v] = 0;
			else
				minDistMat[u][v] = graphEdges[u][v];

		}
	}

	for (int k = 0; k < graphSize; ++k)
	{
		for (int i = 0; i < graphSize; ++i)
		{
			for (int j = 0; j < graphSize; j++)
			{
				if (minDistMat[i][j] > minDistMat[i][k] + minDistMat[k][j])
					minDistMat[i][j] = minDistMat[i][k] + minDistMat[k][j];
			}
		}
	}

	return minDistMat;
}