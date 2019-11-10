// GraphAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AdjListGraph.h"
#include "TestTxtParser.h"
#include "AdjMatrixGraph.h"

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

	AdjMatrixGraph matrixGraph(adjlistGraphic);
	matrixGraph.PrintAdjMatrix();

	//std::cout << "Hello World!\n";

	//AdjListGraph adjlistGraphic(5);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
