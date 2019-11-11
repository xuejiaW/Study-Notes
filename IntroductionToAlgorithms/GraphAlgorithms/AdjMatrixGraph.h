#pragma once

#include <iostream>
#include "AdjListGraph.h";
#include <climits>
#include <iomanip>
using namespace std;

class AdjMatrixGraph
{
public:
	AdjMatrixGraph(int graphSize);
	~AdjMatrixGraph();

	void AddEdge(int u, int v, float weight);

	int graphSize = 0;
	float** graphEdges;
private:
};

