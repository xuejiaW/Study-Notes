#pragma once

#include <iostream>
#include "AdjMatrixGraph.h"
using namespace std;

vector<float> DijkstraShortest(AdjMatrixGraph* graph, int source)
{

	vector<int> touchedVertex;
	vector<float> shortestDist(graph->graphSize);
	float** graphEdges = graph->graphEdges;

	//Init
	touchedVertex.push_back(source);
	//shortestDist[0] = 0;//0 for go to himself

	for (int i = 0; i < graph->graphSize; i++)
	{
		if (i == source)
		{
			shortestDist[i] = 0;
			continue;
		}

		shortestDist[i] = graphEdges[source][i];
	}

	for (int v = 1; v < graph->graphSize - 1; v++)
	{
		int minDist = INT_MAX;
		int minVertex = INT_MAX;

		//Find min vertex Index
		for (int i = 0; i < graph->graphSize; i++)
		{
			bool notTouched = find(touchedVertex.rbegin(), touchedVertex.rend(), i) == touchedVertex.rend();
			if (notTouched && shortestDist[i] < minDist)
			{
				minVertex = i;
				minDist = shortestDist[i];
			}
		}
		touchedVertex.push_back(minVertex);


		//Update shortest Dist for each vertex
		for (int i = 0; i < graph->graphSize; i++)
		{
			//Not need to update already touched Vertex
			bool notTouched = find(touchedVertex.rbegin(), touchedVertex.rend(), i) == touchedVertex.rend();
			if (notTouched && graphEdges[minVertex][i] != INT_MAX
				&& graphEdges[minVertex][i] + shortestDist[minVertex] < shortestDist[i])
				shortestDist[i] = graphEdges[minVertex][i] + shortestDist[minVertex];
		}
	}

	return shortestDist;
}

