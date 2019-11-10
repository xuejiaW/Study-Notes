#pragma once

#include <iostream>
#include "AdjMatrixgraph.h"
using namespace std;

void FloydWarshallShortest(AdjMatrixGraph* matrixGraph)
{
	int graphSize = matrixGraph->graphSize;
	float** minDist = (float**)malloc(sizeof(float*) * graphSize);
	float** graphEdges = matrixGraph->graphEdges;
	for (int i = 0; i < graphSize; i++)
		minDist[i] = (float*)malloc(sizeof(float) * graphSize);


	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			if (u == v)
				minDist[u][v] = 0;
			else
				minDist[u][v] = graphEdges[u][v];

		}
	}

	for (int k = 0; k < graphSize; ++k)
	{
		for (int i = 0; i < graphSize; ++i)
		{
			for (int j = 0; j < graphSize; j++)
			{
				if (minDist[i][j] > minDist[i][k] + minDist[k][j])
					minDist[i][j] = minDist[i][k] + minDist[k][j];
			}
		}
	}

	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			cout << minDist[u][v] << " ";
			//if (u == v)
			//	minDist[u][v] = 0;
			//else
			//	minDist[u][v] = graphEdges[u][v];
		}
		cout << endl;
	}


	for (int i = 0; i < graphSize; i++)
		free(minDist[i]);

	free(minDist);
}