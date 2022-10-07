#include <iostream>
#include <vector>
using namespace std;

enum CardType {
	bomb,
	reinforcement,
	blockade,
	airlift,
	diplomacy
};

class Card {
private:
	CardType type;
public:
	Card();
	Card(CardType);
	bool operator ==(Card);
	bool operator !=(Card);
	Card& operator =(Card);
	CardType getType();
	Order play(); // returns an order
};

class Hand {
	vector<Card> hand;
public:
	void addCard(Card);
	bool isEmpty();
	Card useCard();
};

class Deck {
	vector<Card> deck;
public:
	void addCard(Card);
	void generateDeck(int);
	Card draw();
	bool isEmpty();
};