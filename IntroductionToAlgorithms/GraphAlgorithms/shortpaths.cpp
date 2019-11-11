// GraphAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjListGraph.h"
#include "TestTxtParser.h"
#include "AdjMatrixGraph.h"
#include "DijkstraShortest.h"
#include "FloydWarshallShortest.h"
#include "PrintFloatMatrix.h"
#include "GraphConverter.h"

int main(int argc, char* argv[])
{
	//Parser the testGraphText
	const char* filePath = argc > 1 ? argv[1] : "./testGraph.txt";
	string content = ReadTestTxt(filePath);
	vector<int> uList, vList;
	vector<float> weightList;
	int vertexCount = ParserTestContent(content, uList, vList, weightList);

	//Load content as AdjListGraph
	AdjListGraph adjlistGraphic(vertexCount);
	for (int i = 0; i < uList.size(); i++)
		adjlistGraphic.AddEdge(uList[i], vList[i], weightList[i]);
	//adjlistGraphic.PrintListGraphic();//Test adjListGraphic

	//Convert AdjlistGraph to AdjMatrixGraph
	AdjMatrixGraph* matrixGraph = ConvertToMatrixGraph(&adjlistGraphic);

	////Convert AdjMatrixGraph to AdjListGraph
	//AdjListGraph* adjlistGraph_converted = ConvertToListGraph(matrixGraph);
	//adjlistGraph_converted->PrintListGraphic();

	//Print AdjMatrixGraph
	cout << "Adjacency Matrix" << endl;
	PrintFloatMatrix(&(matrixGraph->graphEdges), matrixGraph->graphSize);

	cout << endl;

	//Show minimum dist from 0 using Dijkstra's algorithm
	vector<float> shortestDist = DijkstraShortest(matrixGraph, 0);
	cout << "Dijkstra's Algorithm" << endl;
	cout << "Shortest Paths from source" << endl;
	for (int i = 0; i < shortestDist.size(); i++)
	{
		cout << "0 --> " << i << " :  ";
		if (shortestDist[i] == INT_MAX)
			cout << ".";
		else
			cout << shortestDist[i];
		cout << endl;
	}

	cout << endl;

	//Show minumum dist from each vertic using Floyd-Warshall algorithm
	float** minDistMat = FloydWarshallShortest(matrixGraph);
	cout << "Floyd-Warshall Algorithm" << endl;
	PrintFloatMatrix(&minDistMat, matrixGraph->graphSize);

	//Free minDistMat
	for (int i = 0; i < matrixGraph->graphSize; i++)
		free(minDistMat[i]);

	free(minDistMat);
}

