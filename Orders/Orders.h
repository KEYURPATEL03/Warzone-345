#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../Game Engine/GameEngine.h"
#include "../Player/Player.h"
#include "../LoggingObserver/LoggingObserver.h"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;
using std::string;

class Territory;
class Deck;
class GameEngine;

//Base Class
class Orders : public ILoggable, public Subject
{
private:
    bool executed = false;
    string effect;
public:

    Orders();
    //Copy Constructor:
    Orders(const Orders& ord);
    //Destructor:
    ~Orders();
    //Assignment Operator:
    Orders& operator= (const Orders& ord);
    //Stream Insertion Operator Declaration:
    friend ostream& operator<< (ostream& os, Orders& ord);
    virtual bool validate() = 0;
    //Pure virtual function because of the keyword virtual and the =0
    virtual void execute() = 0;
    virtual string getName();
    void setIsExecuted(bool isExec);
    bool getIsExecuted() const;
    void setEffect(string eff);
    string getEffect();
    string stringToLog();
};


//OrdersList Class
class OrdersList : public ILoggable, public Subject {
private:

    Player* ordersListCurrentPlayer;
public:
    OrdersList();
    //Parametrized Constructor:
    explicit OrdersList(Player* ordersListCurrentPlayer, vector<Orders*>& ordersList);
    ~OrdersList();
    void setOrdersList(vector<Orders*>& ordersList);
    vector<Orders*> ordersList;
    bool removeOrder(int index);
    bool move(int i, int j);
    //Stream Insertion Operator Declaration:
    friend ostream& operator<< (ostream& os, OrdersList& ordersList);
    void addOrders(Orders* ord);
    void removeOrder(Orders* ord);

    string stringToLog();

};


/**********************************************************/

//The different types of orders are subclasses of the Orders class.
//The orders are : deploy, advance, bomb, blockade, airlift, negotiate

//Deploy subclass
class Deploy : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    string name = "Deploy";
    int numOfArmies;
    Territory* targetTerr;
public:
    Deploy();
    //Parametrized Constructor:
    Deploy(Player* currentPlayer, int numOfArmies, Territory* targetTerr, GameEngine* gameEng);
    //Copy Constructor:
    Deploy(const Deploy& dpl); 
    //Assignment Operator:
    Deploy& operator= (const Deploy& dpl);
    //Destructor:
    ~Deploy();
    void setNumOfArmies(int numOfArmies);
    int getNumOfArmies() const;
    string getName();
    void setTargetTerritory(Territory* targetTerr);
    Territory* getTargetTerritory();
    //Stream Insertion Operator Declaration:
    friend ostream& operator << (ostream& os, Deploy& dpl);
    bool validate();
    void execute();
};



/**********************************************************/

//Advance subclass
class Advance : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    string name = "Advance";
    int numOfArmies;
    Territory* sourceTerr;
    Territory* targetTerr;
public:
    Advance();
    //Parametrized Constructor:
    Advance(Player* currentPlayer, int numOfArmies, Territory* sourceTerr, Territory* targetTerr, GameEngine* gameEng);
    //Copy Constructor:
    Advance(const Advance& advance);
    //Destructor:
    ~Advance();
    //Assignment Operator:
    Advance& operator= (const Advance& advance);
    void setNumOfArmies(int numOfArmies);
    string getName();
    int getNumOfArmies() const;
    void setSourceTerritory(Territory* source);
    Territory* getSourceTerritory();
    void setTargetTerritory(Territory* target);
    Territory* getTargetTerritory();
    //Stream Insertion Operator Declaration:
    friend ostream& operator << (ostream& os, Advance& adv);
    bool cannotBeAttacked = false;
    bool validate();
    void execute();
};


/**********************************************************/

//Bomb subclass
class Bomb : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    string name = "Bomb";
    Territory* targetTerr;
public:
    Bomb();
    //Parametrized Constructor:
    explicit Bomb(Player* currentPlayer, Territory* targetTerr, GameEngine* gameEng);
    //Copy Constructor:
    Bomb(const Bomb& bmb);
    //Destructor:
    ~Bomb();
    //Assignment Operator:
    Bomb& operator= (const Bomb& bmb);
    void setTargetTerritory(Territory* targetTerr);
    string getName();
    Territory* getTargetTerritory();
    //Stream Insertion Operator Declaration:
    friend ostream& operator<< (ostream& os, Bomb& bmb);
    bool validate();
    void execute();
};


/**********************************************************/

//Blockade subclass
class Blockade : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    string name = "Blockade";
    Territory* targetTerr;
public:
    Blockade();
    //Parametrized Constructor:
    Blockade(Player* currentPlayer, Territory* targetTerr, GameEngine* gameEng);
    //Copy Constructor:
    Blockade(const Blockade& bkd);
    //Deconstructor:
    ~Blockade();
    //Assignment Operator:
    Blockade& operator= (const Blockade& bkd);
    string getName();
    void setTargetTerritory(Territory* targetTerr);
    Territory* getTargetTerritory();
    //Stream Insertion Operator Declaration
    friend ostream& operator<< (ostream& os, Blockade& bkd);
    bool validate();
    void execute();
};


/**********************************************************/

//Airlift subclass
class Airlift : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    string name = "Airlift";
    int numOfArmies;
    Territory* sourceTerr;
    Territory* targetTerr;
public:
    Airlift();
    //Parametrized Constructor:
    Airlift(Player* currentPlayer, int numOfArmies, Territory* sourceTerr, Territory* targetTerr, GameEngine* gameEng);
    //Copy Constructor
    Airlift(const Airlift& air);
    //Destructor:
    ~Airlift();
    //Assignment Operator:
    Airlift& operator= (const Airlift& air);
    void setNumOfArmies(int numOfArmies);
    int getNumOfArmies() const;
    void setSourceTerritory(Territory* sourceTerr);
    Territory* getSourceTerritory();
    void setTargetTerritory(Territory* targetTerr);
    Territory* getTargetTerritory();
    string getName();
    //Stream Insertion Operator Declaration:
    friend ostream& operator<< (ostream& os, Airlift& air);
    bool validate();
    void execute();
};


/**********************************************************/

//Negotiate subclass
class Negotiate : public Orders
{
private:
    GameEngine* gameEng;
    Player* currentPlayer;
    Player* otherPlayer;
    string name = "Negotiate";
public:
    Negotiate();
    //Parametrized Constructor:
    Negotiate(Player* currentPlayer, Player* otherPlayer, GameEngine* gameEng);
    //Copy Constructor
    Negotiate(const Negotiate& ngt);
    //Destructor:
    ~Negotiate();
    Negotiate& operator= (const Negotiate& ngt);
    string getName();
    friend ostream& operator<< (ostream& os, Negotiate& ngt);
    bool validate();
    void execute();
};

/**********************************************************/
