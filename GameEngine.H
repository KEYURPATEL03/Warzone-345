//written by keyur patel

#pragma once //preprocessor directive used to prevent header files from being included multiple times.

#include <iostream> //preprocessor directive used to import input/output functions
#include <string>   //preprocessor directive to use std::string

using namespace std;    //using the standard library in the c++

class GameEngine{

    public:
    GameEngine(); //default constructor

    GameEngine(const GameEngine& p); //copy constructor

    GameEngine& operator = (const GameEngine& p);

    friend std::ostream& operator<<(std::ostream& stream, const GameEngine& p); //### ???

    std::string command;


    void startup();

    void start();
    void mapLoaded();
    void mapValidated();
    void playersAdded();

    void play();

    void assignReinforcement();
    void issueOrders();
    void executeOrders();
    void win();

    void testGameStates(); // a function which will allow the user to navigate through all the states.

    int state, numOfMaps, numOfPlayer;
    bool partHandler;



};

