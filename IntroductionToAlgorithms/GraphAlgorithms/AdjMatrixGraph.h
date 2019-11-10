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
	AdjMatrixGraph(AdjListGraph listGraph);
	~AdjMatrixGraph();

	void AddEdge(int u, int v, float weight);
	void PrintAdjMatrix();

private:
	int graphSize;
	float** matrixGraph;
};

void AdjMatrixGraph::AddEdge(int u, int v, float weight)
{
	matrixGraph[u][v] = weight;
}

void AdjMatrixGraph::PrintAdjMatrix()
{
	cout.setf(ios::left);
	cout << "Adjacency Matrix" << endl;
	cout << setw(7) << "";
	for (int u = 0; u < graphSize; u++)
	{
		cout << setw(7) << u;
	}
	cout << endl;
	for (int u = 0; u < graphSize; u++)
	{
		cout << setw(7) << u;
		for (int v = 0; v < graphSize; v++)
		{
			cout << setiosflags(ios::fixed);
			cout << setprecision(1);
			if (matrixGraph[u][v] == INT_MAX)
				cout << setw(7) << ".";
			else
				cout << setw(7) << matrixGraph[u][v];
		}
		cout << endl;
	}
}

AdjMatrixGraph::AdjMatrixGraph(AdjListGraph adjListGraph) :AdjMatrixGraph(adjListGraph.graphSize)
{
	//Convert from Adjacency list to Adjacency Matrix
	vector<pair<int, float>>* listGraph = adjListGraph.listGraph;
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
	matrixGraph = (float**)malloc(sizeof(float*) * graphSize);
	for (int i = 0; i < graphSize; i++)
		matrixGraph[i] = (float*)malloc(sizeof(float) * graphSize);
	for (int u = 0; u < graphSize; u++)
	{
		for (int v = 0; v < graphSize; v++)
		{
			matrixGraph[u][v] = INT_MAX;
		}
	}
}

AdjMatrixGraph::~AdjMatrixGraph()
{
	for (int i = 0; i < graphSize; i++)
		free(matrixGraph[i]);
	free(matrixGraph);
}