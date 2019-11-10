#pragma once

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class AdjListGraph
{
public:
	AdjListGraph(int size);
	~AdjListGraph();

	void AddEdge(int u, int v, float weight);
	void PrintListGraphic();

	vector<pair<int, float>>* listGraph;
	int graphSize;
private:
};