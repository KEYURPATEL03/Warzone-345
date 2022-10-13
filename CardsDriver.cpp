#include <iostream>
#include "Cards.h"
#include "Orders.h"
using namespace std;

//free function that creates a deck of cards of all diff kinds
void testCards() {
    Deck d;
    Hand h;
    cout << "Generating deck..." << endl;
    d.generateDeck(5);
    d.printDeck();
    h.printHand();
    cout << "-----------------------------------------------------------" << endl;
    while(!d.isEmpty()) {
        h.addCard(d.draw());
    }
    cout << "Creating hand..." << endl;
    d.printDeck();
    h.printHand();

    while(!h.isEmpty()) {
        Card c = h.useCard();
        Order o = c.play(); // use this order to add it to the orderlist of player
        d.addCard(c);
    }

    cout << "-----------------------------------------------------------" << endl;
    cout << "Playing hand..." << endl;
    d.printDeck();
    h.printHand();
}

int main()
{
    testCards();
	return 0;
}