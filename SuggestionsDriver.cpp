//	File Name: SuggestionsDriver.cpp
//		This driver will demonstrate a search with suggestions

#include <iostream>
#include "Food.h"
#include "List.h"
#include "BST.h"

// function declarations
void readInt(int& input);
void readChar(char &input);

//array of foods to put in linked list. 
Food FoodBank[] = { Food("Banana", 105), Food("Broccoli", 35), Food("Cake, 1oz", 80), Food("Fried Chicken, 1 piece", 144), 
	Food("Blackberries, 1 cup", 62), Food("Salmon, 3oz", 99), Food("Baked Potato", 94), Food("Celery, 1 cup", 16), 
	Food("Rice, White, 1 cup", 151), Food("Apple", 95), Food("Grapefruit",  52), Food("Carrot", 1), Food("Milk, 1oz", 18),
	Food("Peas, 1/2 cup", 137), Food("Steak, 3oz", 109), Food("Bran Muffin", 178), Food("Honey, 1tbsp", 64), Food("Crumble Cake", 1110)};

using namespace std;

int main()
{
	List<Food> lst1;

	for (int i = 0; i < sizeof(FoodBank) / sizeof(FoodBank[0]); i++)
		lst1.addNode(FoodBank[i]);

	cout << "Here is the list of foods: \n";
	lst1.sortAscending();
	lst1.printList(cout);

	cout << "\nDemonstration 1: " << endl;
	cout << "\nIf I want to search ""Salmon, 3oz"" I can enter ""Salmon"" and this is what happens: \n";
 	string searchResult = lst1.search("Salmon");
	cout << searchResult << endl;
	
	cout << "\nDemonstration 2: " << endl;
	cout << "\nIf I enter a value that is not a match but genrates close matches like ""camel"", I get this: " << endl;
	searchResult = lst1.search("camel");
	cout << searchResult << endl;

	cout << "\nDemonstration 3: " << endl;
	cout << "\nIf I enter a value like ""Phantom"" that does not return a match I get this: " << endl; 
	searchResult = lst1.search("Phantom");
	cout << searchResult << endl;

	try
	{
		cout << "\nWould you like to add a food? (Y/N): ";
		char response;
		readChar(response);
		while (toupper(response) == 'Y')
		{
			cout << "\nPlease enter the food name: ";
			string tempName;
			getline(cin, tempName);
			cout << "\nPlease enter the calories for this food: ";
			int tempCal;
			readInt(tempCal);
			Food newFood(tempName, tempCal);
			lst1.addNode(newFood);
			cout << "\nWould you like to enter another food? (Y/N): ";
			readChar(response);
		}
		cout << "Would you like to search for a food? (Y/N): ";
		readChar(response);
		while (toupper(response) == 'Y')
		{
			cout << "Please enter a food to search. Enter Q to quit: "; 
			string tempName;
			getline(cin, tempName);
			string searchResponse = lst1.search(tempName);
			cout << searchResponse << endl;
			cout << "Would you like to search another food? (Y/N): ";
			readChar(response);
		}
		
	}
	catch (bad_alloc & ex)
	{
		cerr << "Memory error: " << ex.what() << endl;
		return 1; // EXIT_FAILURE - changed for g++
	}

	cin.get();

	return 0;
}

void readInt(int& input)
{
	while (!(cin >> input))
	{
		cin.clear();
		cin.ignore(BUFFER, '\n');
		cout << "Invalid Input.";
	}
	cin.clear();
	cin.ignore(BUFFER, '\n');
}

void readChar(char &input)
{
	cin >> input;
	while (toupper(input) != 'Y' && toupper(input) != 'N')
	{
		cin.clear();
		cin.ignore(BUFFER, '\n');
		cout << "Please enter Y or N: ";
		cin >> input;
	}
	cin.clear();
	cin.ignore(BUFFER, '\n');
}