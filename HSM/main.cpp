// HSM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Action.h"


int main()
{
	std::cout << "Hello World!\n";

	Action* ActionList = new Action(0);
	Action* EntryActions = new Action(100);
	Action* ExitActions = new Action(200);

	for (int i = 1; i < 10; i++)
	{
		Action* pNode = new Action(i);
		ActionList->pushback(pNode);
	}
	std::cout << " " << std::endl;

	for (int i = 101; i < 110; i++)
	{
		Action* pNode = new Action(i);
		EntryActions->pushback(pNode);
	}
	std::cout << " " << std::endl;

	for (int i = 201; i < 210; i++)
	{
		Action* pNode = new Action(i);
		ExitActions->pushback(pNode);
	}

	std::cout << " " << std::endl;

	ActionList->DisplayList();
	EntryActions->DisplayList();
	ExitActions->DisplayList();

	std::cout << " " << std::endl;

	Action* MergedActions = new Action();
	MergedActions->pushback(ActionList);
	MergedActions->pushback(EntryActions);
	MergedActions->pushback(ExitActions);

	MergedActions->DisplayList();


	int j = 0;
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
