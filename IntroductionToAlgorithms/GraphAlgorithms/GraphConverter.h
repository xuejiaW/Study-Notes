#pragma once

#include "AdjListGraph.h"
#include "AdjMatrixGraph.h"

AdjListGraph* ConvertToListGraph(AdjMatrixGraph* matrixGraph)
{
	AdjListGraph* listGraph = new AdjListGraph(matrixGraph->graphSize);
	float** graphEdges = (*matrixGraph).graphEdges;
	int graphSize = matrixGraph->graphSize;
	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			if (graphEdges[u][v] == INT_MAX)
				continue;
			listGraph->AddEdge(u, v, graphEdges[u][v]);
		}
	}
	return listGraph;
}

AdjMatrixGraph* ConvertToMatrixGraph(AdjListGraph* listGraph)
{
	AdjMatrixGraph* matrixGraph = new AdjMatrixGraph(listGraph->graphSize);
	vector<pair<int, float>>* listGraphEdges = listGraph->listGraph;

	for (int u = 0; u < listGraph->graphSize; u++)
	{
		for (int i = 0; i < listGraphEdges[u].size(); i++)
		{
			pair<int, float> node = listGraphEdges[u][i];
			matrixGraph->AddEdge(u, node.first, node.second);
		}
	}

	return matrixGraph;
}
