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
	AdjMatrixGraph(AdjListGraph* listGraph);
	~AdjMatrixGraph();

	void AddEdge(int u, int v, float weight);
	void PrintAdjMatrix();

	int graphSize;
	float** graphEdges;
private:
};

