#include "AdjMatrixGraph.h"

void AdjMatrixGraph::AddEdge(int u, int v, float weight)
{
	graphEdges[u][v] = weight;
}

AdjMatrixGraph::AdjMatrixGraph(AdjListGraph* adjListGraph) :AdjMatrixGraph(adjListGraph->graphSize)
{
	//Convert from Adjacency list to Adjacency Matrix
	vector<pair<int, float>>* listGraph = adjListGraph->listGraph;
	for (int u = 0; u < graphSize; u++)
	{
		for (int i = 0; i < listGraph[u].size(); i++)
		{
			pair<int, float> node = listGraph[u][i];
			this->AddEdge(u, node.first, node.second);
		}
	}
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
	for (int i = 0; i < graphSize; i++)
		free(graphEdges[i]);
	free(graphEdges);
}