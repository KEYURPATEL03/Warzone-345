#pragma once
#include <iostream>
#include <string>
#include <list>
using std::cout;
using std::endl;
using std::list;
using std::ostream;
using std::string;

//Base Class
class Orders
{
private:
        const string name = "Order";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Orders(/* args */);
    ~Orders();

};

//Free Stream Insertion Operator Declaration
ostream& operator<<(ostream& os, Orders& ord);


//OrdersList Class
class OrdersList
{
private:
    list<Orders*> listOfOrders;
public:
    //An add method to add the orders in the OrdersList
    void addToListOfOrders(Orders* ord);
    list<Orders*> getListOfOrders();
    void move();
    void remove(Orders* ord);
    OrdersList(/* args */);
    ~OrdersList();
};

//Free Stream Insertion Operator Declaration
ostream& operator<<(ostream& os, OrdersList& ordL);


/**********************************************************/

//The different types of orders are subclasses of the Orders class.
//The orders are : deploy, advance, bomb, blockade, airlift, negotiate

//Deploy subclass
class Deploy : public Orders
{
private:
    const string name = "Deploy";
    string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Deploy(/* args */);
    ~Deploy();
};



/**********************************************************/

//Advance sublcass
class Advance : public Orders
{
private:
    const string name = "Advance";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Advance(/* args */);
    ~Advance();
};


/**********************************************************/

//Bomb sublcass
class Bomb : public Orders
{
private:
    const string name = "Bomb";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Bomb(/* args */);
    ~Bomb();
};


/**********************************************************/

//Blockade sublcass
class Blockade : public Orders
{
private:
    const string name = "Blockade";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Blockade(/* args */);
    ~Blockade();
};


/**********************************************************/

//Airlift sublcass
class Airlift : public Orders
{
private:
    const string name= "Airlift";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Airlift(/* args */);
    ~Airlift();
};


/**********************************************************/

//Negotiate sublcass
class Negotiate : public Orders
{
private:
    const string name= "Negotiate";
        string effect;
public:
    string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Negotiate(/* args */);
    ~Negotiate();
};

/**********************************************************/

//Stream insertion operators for the sublcasses of the Order class
ostream& operator<<(ostream& os, Deploy& dpl);
ostream& operator<<(ostream& os, Advance& adv);
ostream& operator<<(ostream& os, Bomb& bmb);
ostream& operator<<(ostream& os, Blockade& bkd);
ostream& operator<<(ostream& os, Airlift& air);
ostream& operator<<(ostream& os, Negotiate& ngt);
