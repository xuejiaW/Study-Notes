#pragma once

#include <iostream>
#include "AdjMatrixgraph.h"
using namespace std;

void DijkstraShortest(AdjMatrixGraph* graph, int source)
{

	vector<int> touchedVertex;
	vector<float> shortestDist(graph->graphSize);
	vector<vector<int>> shortestPath(graph->graphSize);
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
		if (shortestDist[i] != INT_MAX)
		{
			shortestPath[i].push_back(source);
			shortestPath[i].push_back(i);
		}
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
			{
				shortestDist[i] = graphEdges[minVertex][i] + shortestDist[minVertex];
				shortestPath[i] = shortestPath[minVertex];
				shortestPath[i].push_back(minVertex);
			}
		}
	}

	for (int i = 0; i < shortestDist.size(); i++)
	{
		cout << "min is " << shortestDist[i] << endl;
	}
}

