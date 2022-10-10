#pragma once
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::string;

//Base Class
class Orders
{
private:
        const string name = "Order";
        string effect;
public:
    virtual string getName();
    string getEffect();
    void setEffect(string effect);
    bool validate();
    void execute();
    Orders();
    ~Orders();
    //Copy constructor
    Orders(const Orders& ord);
    //Assignment operator
    Orders& operator=(const Orders& ord);
};



//Free Stream Insertion Operator Declaration
ostream& operator<<(ostream& os, Orders& ord);


//OrdersList Class
class OrdersList
{
private:
    vector<Orders*> listOfOrders;
public:
    //An add method to add the orders in the OrdersList
    void addToListOfOrders(Orders* ord);
    vector<Orders*> getListOfOrders();
    void move(int startIndex, int endIndex);
    void remove(Orders* ord);
    void remove(int removingIndex);
    OrdersList();
    ~OrdersList();
    //Copy constructor
    OrdersList(const OrdersList& ordL);
    //Assignment Operator
    OrdersList& operator=(const OrdersList& ordL);
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
    Deploy();
    ~Deploy();
    //Copy constructor
    Deploy(const Deploy& dpl): Orders(dpl) {};
    //Assignment operator
    Deploy& operator=(const Deploy& dpl) {};
};



/**********************************************************/

//Advance subclass
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
    Advance();
    ~Advance();
    //Copy constructor
    Advance(const Advance& adv): Orders(adv) {};
    //Assignment operator
    Advance& operator=(const Advance& adv) {};
};


/**********************************************************/

//Bomb subclass
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
    Bomb();
    ~Bomb();
    //Copy constructor
    Bomb(const Bomb& bmb): Orders(bmb) {};
    //Assignment operator
    Bomb& operator=(const Bomb& bmb) {};
};


/**********************************************************/

//Blockade subclass
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
    Blockade();
    ~Blockade();
    //Copy constructor
    Blockade(const Blockade& bkd): Orders(bkd) {};
    //Assignment operator
    Blockade& operator=(const Blockade& bkd) {};
};


/**********************************************************/

//Airlift subclass
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
    Airlift();
    ~Airlift();
    //Copy constructor
    Airlift(const Airlift& air): Orders(air) {};
    //Assignment operator
    Airlift& operator=(const Airlift& air) {};
};


/**********************************************************/

//Negotiate subclass
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
    Negotiate();
    ~Negotiate();
    //Copy constructor
    Negotiate(const Negotiate& ngt): Orders(ngt) {};
    //Assignment operator
    Negotiate& operator=(const Negotiate& ngt) {};
};

/**********************************************************/

//Stream insertion operators for the sublcasses of the Order class
ostream& operator<<(ostream& os, Deploy& dpl);
ostream& operator<<(ostream& os, Advance& adv);
ostream& operator<<(ostream& os, Bomb& bmb);
ostream& operator<<(ostream& os, Blockade& bkd);
ostream& operator<<(ostream& os, Airlift& air);
ostream& operator<<(ostream& os, Negotiate& ngt);
