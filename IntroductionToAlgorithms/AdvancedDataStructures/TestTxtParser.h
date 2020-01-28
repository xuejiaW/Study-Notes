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

int ParserTestContent(string content, vector<string>& commandList, vector<int>& valueList)
{

	regex expression("(insert [0-9]+)|(minimum)|(extract)");
	smatch matchResult;
	while (std::regex_search(content, matchResult, expression))
	{
		//cout << "enter " << endl;
		string result = matchResult[0];
		bool isInsert = result[0] == 'i';
		commandList.push_back(result.substr(0, isInsert ? 6 : 7));
		valueList.push_back(isInsert ? stoi(result.substr(6)) : 0);
		content = matchResult.suffix().str();
	}

	return 0;
}
