#include "player.cpp"

void testPlayers(){         //This method creates the players and demonstrates the functionality

    vector<Order*> lst;
	vector<string*> hand;
	vector<string*> territory;
    vector<string*> card;

	string s1 = "canada";
	string s2 = "USA";
    string s3 = "africa";

	territory.push_back(&s1);
	territory.push_back(&s2);
    territory.push_back(&s3);
	hand = territory;
	
	string s5 = "bomb";
	string s6 = "spy";

	card.push_back(&s5);
	card.push_back(&s6);

	string name = "ramesh";

	Player* p1 = new Player(name,territory,card,lst);
	(*p1).issueOrder("reinforce");
	(*p1).issueOrder("attack");
	(*p1).print();
	(*p1).toAttack();
	(*p1).toDefend();

	Player* p2 = new Player(*p1);
	cout << endl;
	(*p2).toAttack();
}

int main() 
{
    testPlayers();

    return 0;
}
