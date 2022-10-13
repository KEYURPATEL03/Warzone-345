#include <iostream>
#include <vector>
#include "Orders.h"
using namespace std;


const string cardTypes[5] = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

class Card {
private:
	string type;
public:
	Card();
	Card(string);
	bool operator ==(Card);
	bool operator !=(Card);
	Card& operator =(Card);
	string getType();
	Order play(); // returns an order
};

class Hand {
	vector<Card> hand;
public:
	void addCard(Card);
	bool isEmpty();
	Card useCard();
	void printHand();
};

class Deck {
	vector<Card> deck;
public:
	void addCard(Card);
	void generateDeck(int);
	Card draw();
	bool isEmpty();
	void printDeck();
};