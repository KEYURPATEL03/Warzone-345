#include "player.h"

using namespace std;

Player::Player() 		//default constructor
{
	string name;
	vector<string*> terriorty;
	vector<string*> Card;
	vector<Order*> ol;
}

Player::Player(string name, vector<string*> territory, vector<string*> Card,vector<Order*> ol)  //constructor with parameters
{
	this->name = name;				
	this->terriorty = territory;
	this->Card = Card;
	this->ol = ol;
}

Player::Player(const Player& p) 		//copy constructor
{	
	this->name = p.name;
	this->terriorty = p.terriorty;
	this->Card = p.Card;
	this->ol = p.ol;

}

Player::~Player() 					//destructor
{
	name.clear();
	terriorty.clear();
	Card.clear();					
	for (auto order : ol)
	{
		delete order;
	}
	ol.clear();

	
}

void Player::toAttack()								//returns list of territories to be attacked
{
	for (int a = 0; a < terriorty.size(); a++) 
	{
		cout << *terriorty[a] << " ";
	}
	
}

void Player::toDefend() 							//returns list of territories to be defended
{
	for (int a = 0; a < terriorty.size(); a++)
	{
		cout << *terriorty[a] << " ";
	}
	
}

void Player::issueOrder(string order) 				//put a new order in player's list of existing orders
{
	Order *a = new Order(order);

	ol.push_back(a);

}

vector<Order*> Player::getOrderList() 				//returns order list
{

	return ol;
}


void Player::print() 								
{

	vector<Order*>::iterator it = ol.begin();
	for (; it != ol.end(); it++)
	{
		cout << (*it)->result() << " ";
	}
	cout << endl;
}