#include "AdjMatrixGraph.h"

void AdjMatrixGraph::AddEdge(int u, int v, float weight)
{
	graphEdges[u][v] = weight;
}


AdjMatrixGraph::AdjMatrixGraph(int graphSize)
{
	this->graphSize = graphSize;
	graphEdges = (float**)malloc(sizeof(float*) * graphSize);
	for (int i = 0; i < graphSize; i++)
		graphEdges[i] = (float*)malloc(sizeof(float) * graphSize);
	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			graphEdges[u][v] = INT_MAX;
		}
	}
}

AdjMatrixGraph::~AdjMatrixGraph()
{
	if (graphSize == 0)
		return;

	for (int i = 0; i < graphSize; i++)
		free(graphEdges[i]);
	free(graphEdges);
}