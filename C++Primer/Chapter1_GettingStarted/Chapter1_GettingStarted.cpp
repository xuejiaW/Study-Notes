// Chapter1_GettingStarted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
	std::cout << "/*";
	std::cout << "*/";
	//std::cout<</*"*/" */;//Compile Error
	std::cout <</* "*/" /* "/*" */;

	std::cout << std::endl << std::endl;
	int sum = 0;
	for (int i = -100; i <= 100; i++)
	{
		sum += i;
	}
	std::cout << "sum is " << sum << std::endl;

	std::cout << std::endl << std::endl;

	int value = 0;
	sum = 0;
	while (std::cin >> value)
	{
		sum += value;
	}

	std::cout << "sum is " << sum << std::endl;

}
