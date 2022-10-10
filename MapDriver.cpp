// Warzone.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std; 
#include "map.h"


void testLoadMaps() {
	Map* gameMap = MapLoader::readMap();

	delete gameMap;
};


int main()
{
	//create two territories to build a map
	string terr1Name = "aName";
	string terr2Name = "anotherName";

	vector<Territory*> aVect; //to create a territory, must have a vector of territory?
	vector<Territory*> anotherVect ; //to create a territory, must have a vector of territory?

	Territory* aTerritory = new Territory(terr1Name);
	Territory* anotherTerritory = new Territory(terr2Name);

	//have same address..
	cout << "\n\n " << (*aTerritory).adjacentTerritoriesVct << endl;
	cout << "\n\n " << ( * anotherTerritory).adjacentTerritoriesVct << endl;

	cout << "address of territory object " << aTerritory << endl;
	cout << "address of territory object " << anotherTerritory << endl;
	
	//creates the map
	Map* aMap = new Map();
	aMap->addTerritory(*aTerritory);
	aMap->addTerritory(*anotherTerritory);

	aTerritory->addTerritory(*anotherTerritory);
	anotherTerritory->addTerritory(*aTerritory);

	testLoadMaps();
	return 0;
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
