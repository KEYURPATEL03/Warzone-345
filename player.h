#include <string>
#include <vector>
#include <iostream>
#include "dummyOrder.cpp" //This is a dummy order class for now, will be removed in next iterations

using namespace std;

class Player {

public:
    Player();       //constructor
    Player(string name, vector<string*> t, vector<string*> h,vector<Order*>); //constructor with parameters
    Player(const Player&); //copy constructor
    ~Player(); //desturctor
    void toAttack(); 
    void toDefend();
    void issueOrder(string);
    vector<Order*> getOrderList(); //This will return order list
    void print();					//this will print the orders that needs to be executed

private:
    string name;
    vector<string*> terriorty;
    vector<string*> Card;
    vector<Order*> ol;
};