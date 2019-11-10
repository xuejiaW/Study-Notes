#include "AdjListGraph.h"

void AdjListGraph::AddEdge(int u, int v, float weight)
{
	if (u > graphSize - 1)
		cout << "Error Graphic Size" << endl;

	listGraph[u].push_back(make_pair(v, weight));
}

void AdjListGraph::PrintListGraphic()
{
	for (int u = 0; u < graphSize; u++)
	{
		cout << "Node" << u << " with :" << endl;
		for (int i = 0; i < listGraph[u].size(); i++)
		{
			pair<int, float> node = listGraph[u][i];
			cout << "v is " << node.first << " weight is " << node.second << endl;
		}
	}
}

AdjListGraph::AdjListGraph(int size)
{
	this->graphSize = size;
	listGraph = new vector<pair<int, float>>[size];
}

AdjListGraph::~AdjListGraph()
{
	delete[] listGraph;
}