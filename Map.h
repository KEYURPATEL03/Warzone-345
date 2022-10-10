#ifndef MAP_H
#define MAP_H
#include <string>
#include <set>
#include <vector>
using namespace std;

class Territory {
private:
public:
	std::string* name;
	//pointer to a vector of pointer of territory objects
	std::vector<Territory *> *adjacentTerritoriesVct;
	//Constructors (default, parameterized and copy)
	Territory();
	Territory(string n);
	Territory(string n, std::vector<Territory*>&a);
	Territory(const Territory& t);
	~Territory();
	Territory& operator=(const Territory& t);
	friend ostream& operator<<(ostream& o, Territory& t);
	string getName();
	std::vector<Territory*> getAdjacentTerritoriesVct();
	void addTerritory(Territory& territory);
};

class Map
{
private:
public:
	std::vector<Territory *> *territories;
	string *name;
	//Constructors (default, parameterized and copy)
	Map();
	Map(string n);
	Map(string n, std::vector<Territory*>&t);
	Map(const Map& m);
	~Map();

	Territory* getTerritory(string n);
	void setName(string n);

	void addTerritory(Territory &territory);
};

class MapLoader {
private:
public:
	Map *theMap;
	static Map* readMap();
};



/*
verification made in map constructor ? (connected graph) 
map is a vector of territory
territory is a string and a vector of adjacent territories
*/

#endif