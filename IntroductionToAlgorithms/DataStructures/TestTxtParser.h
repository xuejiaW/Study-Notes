#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


string ReadTestTxt()
{
	string line;

	ifstream testTxt("./testSearch.txt");
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

void ParserTestContent(string content, vector<string>& commandList, vector<int>& valueList)
{
	cout << "content is " << content << endl;
	regex expression("((insert )|(delete )|(search ))[0-9]+");
	smatch matchResult;
	while (std::regex_search(content, matchResult, expression))
	{
		string result = matchResult[0];
		commandList.push_back(result.substr(0, 6));
		valueList.push_back(stoi(result.substr(6)));
		content = matchResult.suffix().str();
	}
}
