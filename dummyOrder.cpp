#include "dummyOrder.h"

Order::Order() 
{
	string name;

}

Order::Order(string name) 
{
	this->name = name;

}

Order::~Order() 
{
	name.clear();
}

string Order::result() 
{
	return name;
}