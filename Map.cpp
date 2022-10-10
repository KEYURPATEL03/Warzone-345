#pragma once

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "Map.h"

//default constructor for territory class
Territory::Territory() {
	string tmp = "";
	name = &tmp;
	std::vector<Territory*> *vect = new vector<Territory*>;
	adjacentTerritoriesVct = vect;
	cout << this-> name <<" Territory created using default constructor" << endl;
};
Territory::Territory(string n) : name(&n) {
	std::vector<Territory*> *vect = new vector<Territory*>;
	adjacentTerritoriesVct = vect;
	cout <<this->name << " Territory created using parameterized constructor 1" << endl;
};
//creates a territory from a string and a vector of territory
Territory::Territory(string n, std::vector<Territory*> &a) : name(&n), adjacentTerritoriesVct(&a) {
	cout << this->name <<" Territory created using parameterized constructor 2" << endl;
}

Territory::Territory(const Territory& t) : name(t.name) {
	std::vector<Territory*> tmp(*t.adjacentTerritoriesVct);
	adjacentTerritoriesVct = &tmp;
	cout << this->name << " Territory created using copy constructor" << endl;
}

Territory& Territory::operator=(const Territory& t) {
	this->name = new string(*(t.name));
	return *this;
}

Territory::~Territory() {
	delete adjacentTerritoriesVct;
}


string Territory::getName() {
	return *name;
}

std::vector<Territory*> Territory::getAdjacentTerritoriesVct() {
	return *adjacentTerritoriesVct;
}

void Territory::addTerritory(Territory& territory) {
	(*adjacentTerritoriesVct).push_back(&territory);
	cout << "added " << territory.getName() << " to adjacent territories of " << getName() << endl;
}

ostream& operator<<(ostream& o, Territory& t)
{
	o << "name of terrritory: " << *t.name;
	return o;
}
Map::Map() {
	string tmp = "";
	name = &tmp;
	//creating a vector of pointer of territories
	std::vector<Territory *> vect;
	territories = &vect;
	cout << " Map created using default constructor" << endl;
}

Map::Map(string n):name(&n) {
	//creating a vector of pointer of territories
	std::vector<Territory*> vect;
	territories = &vect;
	cout << " Map created using parameterized constructor 1" << endl;
}
Map::Map(string n, std::vector<Territory*> &m) : name(&n) {
	territories = &m;
	cout << " Map created using parameterized constructor" << endl;
}

Map::Map(const Map& m) {
	std::vector<Territory*> tmp(*m.territories);
	territories = &tmp;
	cout << " Map created using copy constructor" << endl;
}

Map::~Map() {
	delete territories;
}

Territory* Map::getTerritory(string n)
{
	for (auto& t : *territories)
		if (t->getName() == *name)
			return t;
	return nullptr;
}

void Map::setName(string n) {
	this->name = &n;
}
void Map::addTerritory(Territory &territory) {
	(*territories).push_back(&territory);
	cout << "added " << territory.getName() << " to map" << endl;
}

ostream& operator<<(ostream& o, Map& m)
{
	o << "name of map: " << *m.name;
	return o;
}

Map* MapLoader::readMap()
{
	Map* gameMap = new Map();
	string line;
	string path;
	string s;
	string name;
	string q = "y";
	ifstream mapReader;
	//get the file name and open the file for read
	while (q == "y")
	{
		cout << "Please enter the map name: ";
		cin >> path;

		mapReader.open(path);
		if (!mapReader.is_open()) {
			cout << "failed to open " << path << endl;
			cout << "Do you want to try again? (y/n) ";
			cin >> q;
		}
		else
			q = "n";
	}
	if (!mapReader.is_open()) {
		cout << "Program ended" << endl;
		exit(0);
	}
	//read the file until the end
	while (!mapReader.eof()) {
		getline(mapReader, line, '\n');
		//skip continent section to territories
		if (line == "[Territories]") {
			s = ",";
			name = "";
			while (!mapReader.eof()) {
				getline(mapReader, line, '\n');
				if (line == "")
					continue;
				vector<string> tInfo;
				int start = 0;
				int end = 0;
				int len = line.length();
				string tempName;
				string d = ",";
				while (end >= 0) {
					end = line.find(d);
					tInfo.push_back(line.substr(start, end));
					line = line.substr(end + 1, len - end + 1);
				}
				std::vector<Territory*> *vect = new vector<Territory*>;
				Territory* t = new Territory(tInfo[0], *vect);
				//add territory to map
				gameMap->addTerritory(*t);
				//add adjacent territories
				
				

			}
		}
	}
	mapReader.clear();
	mapReader.seekg(0);
	//add adjacent territories after all territories have been created
	while (!mapReader.eof()) {
		if (line == "[Territories]") {
			s = ",";
			name = "";
			while (!mapReader.eof()) {
				getline(mapReader, line, '\n');
				if (line == "")
					continue;
				vector<string> tInfo;
				int start = 0;
				int end = 0;
				int len = line.length();
				string tempName;
				string d = ",";
				while (end >= 0) {
					end = line.find(d);
					tInfo.push_back(line.substr(start, end));
					line = line.substr(end + 1, len - end + 1);
				}
				for (int i = 4; i < tInfo.size(); i++) {
					Territory* t = gameMap->getTerritory(tInfo[0]);
					gameMap->getTerritory(t->getName())->addTerritory(*gameMap->getTerritory(tInfo[i]));
				}
			}
		}
	}
	mapReader.close();
	//if no valid info for the map then return null pointer

	cout << "All loaded." << endl;
	//gameMap->showAllContinents();
	//cout << "\n\n" << "Validating map" << endl;
	//if (gameMap->validate())
	//{
	//	cout << "This is a valid map." << endl;
	//	delete gameMap;
	//	return nullptr;
	//}
	//else
	//{
	//	cout << "The map is invalid." << endl;
	//	return gameMap;
	//}
	return nullptr;
}