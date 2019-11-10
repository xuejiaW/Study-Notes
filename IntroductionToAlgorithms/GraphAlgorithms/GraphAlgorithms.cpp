// GraphAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjListGraph.h"
#include "TestTxtParser.h"
#include "AdjMatrixGraph.h"
#include "DijkstraShortest.h"

int main()
{
	string content = ReadTestTxt();
	vector<int> uList, vList;
	vector<float> weightList;
	int vertexCount = ParserTestContent(content, uList, vList, weightList);
	std::cout << "Graphic count " << vertexCount << endl;


	AdjListGraph adjlistGraphic(vertexCount);
	for (int i = 0; i < uList.size(); i++)
	{
		adjlistGraphic.AddEdge(uList[i], vList[i], weightList[i]);
	}

	//adjlistGraphic.PrintListGraphic();

	AdjMatrixGraph matrixGraph(&adjlistGraphic);
	matrixGraph.PrintAdjMatrix();
	DijkstraShortest(&matrixGraph,1);

}

