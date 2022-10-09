#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Order                 //This is a dummy class and will be removed in next iteration
{
    private:
	    string name;

    public:
	    Order();
	    Order(string);
	    ~Order();
	    string result();
};
