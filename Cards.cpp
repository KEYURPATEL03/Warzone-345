#include "Cards.h"

//default constructor 
Card::Card() {
	type = "airlift";
}
//parametized constructor 
Card::Card(string t)
{
	type = t;
}
//assignment operator
bool Card::operator==(Card a){
	return (type == a.type);
}

bool Card::operator!=(Card a){
	return (type != a.type);
}

Card& Card::operator=(Card a){
	type = a.type;
	return *this;
}
//getter 
string Card::getType(){
	return type;
}


// Play method creates an order and returns the order so that 
// it can be added to the players orderlist
Order Card::play(){

	//Create an object of type order
	Order order;

	// Create an order depending on the card (dummy order)


	return order; // return the order to be added to the player orderlist
}

void Deck::addCard(Card c)
{
	deck.push_back(c);
}

void Deck::generateDeck(int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		int randNum = rand() % 5;
		Card c(cardTypes[randNum]);
		addCard(c);
	}
}

/*draw() method that allows a player to draw a card at random from the cards remaining 
in the deck and place it in their hand of cards.*/

Card Deck::draw()
{
	srand(time(0));
    int index = rand() % deck.size();
	Card c = deck.at(index);
	deck.erase(deck.begin() + index);
	return c;
}

bool Deck::isEmpty()
{
	if (deck.size() == 0)
		return true;
	return false;
}

void Deck::printDeck()
{
	cout << "Deck --> ";
	for(int i = 0; i < deck.size(); i++) {
		cout << deck.at(i).getType() << " ";
	}
	cout << endl;
}

void Hand::addCard(Card c)
{
	hand.push_back(c);
}

bool Hand::isEmpty()
{
	if (hand.size() == 0)
		return true;
	return false;
}

Card Hand::useCard()
{
	Card c = hand.front();
	hand.erase(hand.begin());
	return c;
}

void Hand::printHand()
{
	cout << "Hand --> ";
	for(int i = 0; i < hand.size(); i++) {
		cout << hand.at(i).getType() << " ";
	}
	cout << endl;
}