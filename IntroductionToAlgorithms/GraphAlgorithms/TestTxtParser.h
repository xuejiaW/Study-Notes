#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>

using namespace std;

string ReadTestTxt(const char* filePath)
{
	string line;

	ifstream testTxt(filePath);
	if (testTxt.is_open())
	{
		if (getline(testTxt, line))
			return line;
		else
			return "";

		testTxt.close();
	}
	else
	{
		cout << "ERROR: open test file failed" << endl;
		return "";
	}
}

int ParserTestContent(string content,vector<int>& uList,vector<int>& vList,vector<float>& weightList)
{
	regex expression("\([0-9]+,[0-9]+,[0-9\.]+\)");
	smatch matchResult;
	set<int> uSet;//Used to calculate vertex count

	while (std::regex_search(content, matchResult, expression))
	{
		string result = matchResult[0];
		int firstCommaIndex = result.find_first_of(',');
		int lastCommaIndex = result.find_last_of(',');

		int uIndex = stoi(result.substr(0, firstCommaIndex));
		int vIndex = stoi(result.substr(firstCommaIndex + 1, lastCommaIndex - firstCommaIndex - 1));
		float edgeWeight = stof(result.substr(lastCommaIndex + 1));

		uSet.insert(uIndex);
		uList.push_back(uIndex);
		vList.push_back(vIndex);
		weightList.push_back(edgeWeight);

		content = matchResult.suffix().str();
	}

	return uSet.size();
}
