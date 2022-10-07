#include <iostream>
#include "Cards.h";
using namespace std;

//free function that creates a deck of cards of all diff kinds
void testCards() {
    Deck d;
    d.generateDeck(3);
    Hand h;
    while(!d.isEmpty()) {
        h.addCard(d.draw());
    }

    while(!h.isEmpty()) {
        Card c = h.useCard();
        Order o = c.play(); // use this order to add it to the orderlist of player
        d.addCard(c);
    }
}

int main()
{
    testCards();
	return 0;
}