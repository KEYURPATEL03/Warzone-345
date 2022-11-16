#include <iostream>
#include <string>
#include "Orders.h"
#include <algorithm>
#include <utility>
#include <cstdlib>
using namespace std;
using std::endl;
using std::ostream;
using std::string;
using std::move;

/**********************************************************/
// ORDER
/**********************************************************/

//Default constructor:
Orders::Orders()
{
    //Here we are telling what should be done when we create an object of type Orders. (same logic for the other constructors)
      cout << "An Order object has been created." << endl;
}

//Deconstructor:
Orders::~Orders()
{
    //Here we are telling what should be done when an object of type Orders is done being used. (same logic for the other destructors)
    cout << "Destructor deleted the Orders object!" << endl;
}

//Getter method getIsExecuted for Orders:
bool Orders::getIsExecuted() const {
    return executed;
}
//Setter method setIsExecuted for Orders:
void Orders::setIsExecuted(bool isExec) {
    this->executed = isExec;
}
//Getter method getEffect for Orders:
string Orders::getEffect() {
    return this->effect;
}
string Orders::stringToLog()
{
    return "Order: " + getName() + ", Effect: " + getEffect();
}
void Orders::setEffect(string ordersEffect) {
    effect = std::move(ordersEffect);
}

//Stream Insertion Operator Definition for the Orders class:
ostream& operator<<(ostream& os, Orders& ord){
    os << "An Order has been created" << endl;
    return os;
}

//Copy Constructor:
Orders::Orders(const Orders& ord) = default;

//Assignment Operator:
Orders& Orders::operator= (const Orders& ord) = default;

/**********************************************************/
// ORDERS LIST
/**********************************************************/

OrdersList::OrdersList()
{
    cout << "OrdersList has been created!" << endl;
}

OrdersList::OrdersList(Player* ordersListCurrentPlayer, vector<Orders*>& ordL) {
    this->ordersListCurrentPlayer = ordersListCurrentPlayer;
    this->ordersList = ordersList;
    this->Attach(ordersListCurrentPlayer->getGameEngine()->_observer);
}

void OrdersList::setOrdersList(vector<Orders*>& ordL) {
    this->ordersList = ordL;
}

//Removing order by index
bool OrdersList::removeOrder(int index) {
    cout << "Trying to remove order " + ordersList.at(index)->getName() + " from the list" << endl;
    if (index < 0 || index >= ordersList.size()) {
        cout << "Index specified not in range of vector size" << endl;
        return false;
    }
    //Handling the case where the last index needs to be removed
    else if (index + 1 == ordersList.size()) {
        ordersList.pop_back();
        cout << "Last order in list was removed!" << endl;
        return true;
    }
    else {
        ordersList.erase(ordersList.begin() + index);
        cout << "The order was successfully removed!" << endl;
        return true;
    }
}


//Moving orders from one index to another (rotate algorithm)
bool OrdersList::move(int i, int j) {
    cout << "Trying to move order " << ordersList.at(i)->getName() << " from position " << i << " to position " << j << " in the list." << endl;
    if (i < 0 || i >= ordersList.size() || j < 0 || j >= ordersList.size()) {
        cout << "The specified index is not in range of the vector size!" << endl;
        return false;
    }
    else {
        if (i > j) {
            rotate(ordersList.rend() - i - 1, ordersList.rend() - i, ordersList.rend() - j);
        }
        else {
            rotate(ordersList.begin() + i, ordersList.begin() + 1, ordersList.begin() + j + 1);
        }
        cout << "The order position was successfully switched!" << endl << endl;
        return true;
    }
}



//Stream insertion operator overload (printing all the names of the orders)
ostream& operator<<(ostream& os, OrdersList& ordersList) {
    cout << "Printing out the ordersList of " + ordersList.ordersListCurrentPlayer->getName() << endl;
    for (auto& it : ordersList.ordersList) {
        cout << it->getName() + " -> ";
    }
    return os << "END" << endl;
}

void OrdersList::addOrders(Orders* ord) {
    this->ordersList.push_back(ord);
    Notify(this);
}

void OrdersList::removeOrder(Orders* ord) {
    ordersList.erase(remove(ordersList.begin(), ordersList.end(), ord), ordersList.end());
}


//stringToLog from ILoggable
string OrdersList::stringToLog()
{
    string outputString = "Inserted ";
    Orders* ord = ordersList.back();
    outputString += "Order: " + ord->getName() + "";
    outputString += " into the list.";
    return outputString;
}

//Destructor for OrdersList (deleting each order pointer before clearing the vector)
OrdersList::~OrdersList() {
    for (auto it : ordersList) {
        delete it;
    }
    ordersList.clear();
    this->Detach();
    cout << "Destructor deleted the OrdersList object!" << endl;
}

/**********************************************************/
// DEPLOY
/**********************************************************/

Deploy::Deploy(/* args */)
{
    cout << "The Deploy Order was made." << endl;
}

Deploy::Deploy(Player* currentPlayer, int numOfArmies, Territory* targetTerr, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->numOfArmies = numOfArmies;
    this->targetTerr = targetTerr;
}

void Deploy::setNumOfArmies(int armyNum) {
    this->numOfArmies = armyNum;
}

int Deploy::getNumOfArmies() const {
    return this->numOfArmies;
}

void Deploy::setTargetTerritory(Territory* targetTerr) {
    this->targetTerr = targetTerr;
}

Territory* Deploy::getTargetTerritory() {
    return this->targetTerr;
}

string Deploy::getName() { return name; }

//Stream insertion operator overload
ostream& operator<< (ostream& os, Deploy& dpl) {
    string dO = "Deploy order\n";
    if (dpl.getIsExecuted()) {
        return os << dO + dpl.getEffect();
    }
    else return os << dO;
}

//Assignment operator overload
Deploy& Deploy::operator = (const Deploy& dpl) {
    //Shallow copying data members of the deploy class since no new data members are being added.
    if (&dpl != this) {
        this->gameEng = dpl.gameEng;
        this->Attach(dpl.gameEng->_observer);
        this->currentPlayer = dpl.currentPlayer;
        this->numOfArmies = dpl.numOfArmies;
        this->targetTerr = dpl.targetTerr;
    }
    return *this;
}

//Validate method checking if currentPlayer owns target territory and if the number of armies is valid
bool Deploy::validate() {
    cout << "Deploy Order validation is in progress...\n" << endl;
    if (targetTerr == nullptr) {
        cout << "INVALID: The target territory points to NULL!" << endl;
        return false;
    }
    if (getIsExecuted()) {
        cout << "INVALID: Order is already executed!" << endl;
        return false;
    }
    if (currentPlayer->ownsTerritory(getTargetTerritory()) && getNumOfArmies() > 0) {
        cout << "Deploy order has been validated!" << endl;
        return true;
    }
    //If the target territory does not belong to the player that issued the order, the order is invalid.
    cout << "Deploy order is invalid since " + currentPlayer->getName() + " does not own " + targetTerr->getName() + " territory!" << endl;
    return false;
}

void Deploy::execute() {
//The deploy method being executed if the validation passes
    if (Deploy::validate()) {
        cout << "Executing the deploy order..." << endl;
        //If the target territory belongs to the player that issued the deploy order, the selected number of army units is added to the number of army units on that territory.
        int oldNumOfArmies = getTargetTerritory()->getNumberOfArmies();
        int newNumOfArmies = getTargetTerritory()->getNumberOfArmies() + numOfArmies;
        getTargetTerritory()->setNumberOfArmies(newNumOfArmies);
        //Setting the message that will then be printed:
        setEffect(currentPlayer->getName() + " has deployed " + to_string(getNumOfArmies()) +
            " armies to territory " + targetTerr->getName() + ". Old army count = " + to_string(oldNumOfArmies) + ".New army count = " + to_string(getTargetTerritory()->getNumberOfArmies())
            + "\n");
        cout << getEffect();
        setIsExecuted(true);
    }
    else {
        setEffect("The deploy order failed to execute!\n");
        cout << getEffect();
    }
    Notify(this);
}
//Copy constructor
Deploy::Deploy(const Deploy& dpl) {
    //Shallow copy of the data members for the deploy class since no new data members are being added.
    this->gameEng = dpl.gameEng;
    this->Attach(dpl.gameEng->_observer);
    this->currentPlayer = dpl.currentPlayer;
    this->targetTerr = dpl.targetTerr;
    this->numOfArmies = dpl.numOfArmies;
}

Deploy::~Deploy() {
    currentPlayer = nullptr;
    targetTerr = nullptr;
    gameEng = nullptr;
    this->Detach();
};

/**********************************************************/
// ADVANCE
/**********************************************************/

Advance::Advance(/* args */)
{
    cout << "The Advance Order was made." << endl;
}

Advance::Advance(Player* currentPlayer, int i, Territory* sourceTerr, Territory* targetTerr, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->numOfArmies = i;
    this->sourceTerr = sourceTerr;
    this->targetTerr = targetTerr;

}

int Advance::getNumOfArmies() const {
    return numOfArmies;
}

void Advance::setNumOfArmies(int n) {
    this->numOfArmies = n;
}

Territory* Advance::getTargetTerritory() {
    return targetTerr;
}

void Advance::setTargetTerritory(Territory* targetTerr) {
    targetTerr = targetTerr;
}

Territory* Advance::getSourceTerritory() {
    return sourceTerr;
}
void Advance::setSourceTerritory(Territory* sourceTerr) {
    sourceTerr = sourceTerr;
}

string Advance::getName() { return name; }

//Stream insertion operator overload
ostream& operator<< (ostream& os, Advance& adv) {
    string aO = "Advance order\n";
    if (adv.getIsExecuted()) {
        return os << aO + adv.getEffect();
    }
    else return os << aO;
}

//Advance order valid only if target territory is the neighbour of the source territory
bool Advance::validate() {
    cout << "Advance Order validation is in progress...\n" << endl;
    if (sourceTerr == nullptr || targetTerr == nullptr) {
        cout << "INVALID:Either source or target territory points to NULL!" << endl;
        return false;
    }
    //Checking if diplomacy card was used last turn
    if (cannotBeAttacked) {
        cout << "Advance order invalid. Negotiate order was used last turn"
            << " between " + currentPlayer->getName() + "and " + targetTerr->getOwner()->getName() << endl;
        return false;
    }
    if (getIsExecuted()) {
        cout << "Order already executed" << endl;
        return false;
    }
    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if (!currentPlayer->ownsTerritory(sourceTerr)) {
        cout << "Advance order not valid" << endl;
        cout << "Source territory does not belong to " + currentPlayer->getName() << endl;
        return false;
    }
    //If the target territory is not adjacent to the source territory, the order is invalid.
    bool isTargetAdj = false;
    for (auto it : getTargetTerritory()->getAdjacentTerritories()) {
        if (it == sourceTerr) {
            isTargetAdj = true;
        }
    }
    if (!isTargetAdj) {
        cout << "Advance order not valid" << endl;
        cout << "Target territory (" + getTargetTerritory()->getName() + ") not adjacent to source territory(" + sourceTerr->getName() + ")" << endl;
        return false;
    }
    //If the source territory does not have enough armies
    if (sourceTerr->getNumberOfArmies() < getNumOfArmies()) {
        cout << "INVALID:Not enough armies from source to advance to target territory!" << endl;
        return false;
    }
    cout << "Advance order is validated!" << endl;
    return true;
}
//After validating, we're checking if the target territory is our territory or if it's enemy territory before executing.
void Advance::execute() {
    if (Advance::validate()) {
        //If the source and target territory both belong to the player that issued the order, the army units are moved from the source to the target territory.
        if (currentPlayer->ownsTerritory(targetTerr)) {
            cout << "Executing advance order" << endl;
            //Moving armies from source to target territory
            int initialSourceArmy = sourceTerr->getNumberOfArmies();
            int initialTargetArmy = targetTerr->getNumberOfArmies();
            targetTerr->setNumberOfArmies(initialTargetArmy + numOfArmies);
            sourceTerr->setNumberOfArmies(initialSourceArmy - numOfArmies);
            setEffect(currentPlayer->getName() + " has moved " + to_string(getNumOfArmies()) + " armies from " + sourceTerr->getName()
                + " territory to " + targetTerr->getName() + " territory \n");
            cout << getEffect();
        }
  
        /*If the target territory belongs to another player than the player that issued the advance order, an attack is
          simulated when the order is executed. An attack is simulated by the following battle simulation
          mechanism:
          1. Each attacking army unit involved has 60% chances of killing one defending army. At the same time,
          each defending army unit has 70% chances of killing one attacking army unit.
          2. If all the defender's armies are eliminated, the attacker captures the territory. The attacking army units
          that survived the battle then occupy the conquered territory.
          3. A player receives a card at the end of his turn if they successfully conquered at least one territory
          during their turn, i.e. a player cannot receive more than one card per turn.*/
        else {
            Player* enemy = targetTerr->getOwner();
            for (auto it : enemy->cannotAttack) {
                if (it == currentPlayer) {
                    cout << "You cannot attack this player's territory for the remainder of this turn" << endl;
                    return;
                }
            }
            cout << "Executing advance order" << endl;

            cout << "Attack between " + currentPlayer->getName() + " and " + enemy->getName() + " initiated" << endl;

            //Random int from 1 to 100
            int randNumber = rand() % 100 + 1;
            //Reducing source army
            if (sourceTerr->getNumberOfArmies() - numOfArmies < 0) {
                //If we don't have enough army in the source territory:
                sourceTerr->setNumberOfArmies(0);
                numOfArmies = sourceTerr->getNumberOfArmies();
            }
            else sourceTerr->setNumberOfArmies(sourceTerr->getNumberOfArmies() - numOfArmies);
            int attackingArmy = numOfArmies;
            int defendingArmy = targetTerr->getNumberOfArmies();
            for (int i = 0;; i++) {
                if (randNumber <= 60) {
                    defendingArmy--;
                }
                if (randNumber <= 70) {
                    attackingArmy--;
                }
                if (defendingArmy <= 0) {
                    cout << currentPlayer->getName() + " won the battle and has captured territory " + targetTerr->getName()
                        << " successfully" << endl;
                    cout << "Number of armies on defeated target territory is now " << attackingArmy << endl;
                    //The attacker captures the target territory
                    targetTerr->setNumberOfArmies(attackingArmy);
                    targetTerr->getOwner()->removeOwnedTerritory(targetTerr);
                    currentPlayer->addOwnedTerritory(targetTerr);
                    //A player receives a card at the end of his turn if they successfully conquered at least one territory during their turn.
                    if (!currentPlayer->receivedCardThisTurn) {
                        currentPlayer->getHand()->addHand(gameEng->deck->draw());
                        currentPlayer->receivedCardThisTurn = true;
                    }
                    setEffect(currentPlayer->getName() + " won battle against "
                        + enemy->getName() + "and takes " + targetTerr->getName() + " territory!\n");
                    setIsExecuted(true);

                    return;
                }
                if (attackingArmy <= 0) {
                    //Nothing happens: Battle is lost
                    cout << currentPlayer->getName() + " lost the battle" << endl;
                    cout << "Remaining number of armies on enemy territory is " << targetTerr->getNumberOfArmies() << endl;
                    setEffect(currentPlayer->getName() + " attacks " + enemy->getName() + " territory " +
                        targetTerr->getName() + " and lost.");
                    setIsExecuted(true);

                    return;
                }
                randNumber = rand() % 100 + 1;
            }
        }
    }
    else {
        setEffect("The advance call was not executed since it was invalid\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}
//Assignment operator overload
//Shallow copying data members of the advance class since no new data members are being added.
Advance& Advance::operator=(const Advance& adv) {
    if (&adv != this) {
        this->gameEng = adv.gameEng;
        this->Attach(adv.gameEng->_observer);
        this->currentPlayer = adv.currentPlayer;
        this->targetTerr = adv.targetTerr;
        this->sourceTerr = adv.sourceTerr;
        this->numOfArmies = adv.numOfArmies;
    }
    return *this;
}

Advance::Advance(const Advance& adv) {
    this->gameEng = adv.gameEng;
    this->Attach(adv.gameEng->_observer);
    this->currentPlayer = adv.currentPlayer;
    this->targetTerr = adv.targetTerr;
    this->sourceTerr = adv.sourceTerr;
    this->numOfArmies = adv.numOfArmies;
}

//Destructor
Advance::~Advance() {
    currentPlayer = nullptr;
    targetTerr = nullptr;
    sourceTerr = nullptr;
    gameEng = nullptr;
    this->Detach();
    cout << "Destructor deleted the Advance object!" << endl;
};

/**********************************************************/
// BOMB
/**********************************************************/

Bomb::Bomb(/* args */)
{
    cout << "The Deploy Order was made." << endl;
}

Bomb::Bomb(Player* currentPlayer, Territory* targetTerr, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->targetTerr = targetTerr;
}

Territory* Bomb::getTargetTerritory() {
    return targetTerr;
}

void Bomb::setTargetTerritory(Territory* targetTerr) {
    targetTerr = targetTerr;
}

string Bomb::getName() { return name; }

//Stream insertion operator overload
ostream& operator<< (ostream& os, Bomb& bmb) {
    string bO = "Bomb order\n";
    if (bmb.getIsExecuted()) {
        return os << bO + bmb.getEffect();
    }
    else return os << bO;
}

bool Bomb::validate() {
    cout << "Bomb Order validation is in progress...\n" << endl;
    if (targetTerr == nullptr) {
        cout << "Target territory points to NULL" << endl;
        return false;
    }
    if (getIsExecuted()) {
        cout << "Order already executed" << endl;
        return false;
    }
    //If the target belongs to the player that issued the order, the order is invalid.
    if (currentPlayer->ownsTerritory(targetTerr)) {
        cout << "Target belongs to order owner. Cannot bomb it" << endl;
        return false;
    }
    //If the target territory is not adjacent to one of the territory owned by the player issuing the order, then the order is invalid.
    bool isTargetAdj = false;
    for (auto it : targetTerr->getAdjacentTerritories()) {
        if (currentPlayer->ownsTerritory(it)) isTargetAdj = true;
    }
    if (!isTargetAdj) {
        cout << "Bomb order invalid --> No territory owned adjacent to target territory!" << endl;
        return false;
    }
    cout << "Bomb order is valided!" << endl;
    return true;

}
//If validation passes, checking if the target territory is owned by player before executing
void Bomb::execute() {
    if (Bomb::validate()) {
        cout << "Executing bomb order" << endl;
        //If the order is valid, half of the army units are removed from this territory:
        targetTerr->setNumberOfArmies(targetTerr->getNumberOfArmies() / 2);
        setEffect("Successfully bombed " + targetTerr->getName() + " territory\n");
        cout << getEffect();
        setIsExecuted(true);

    }
    else {
        setEffect("The bomb order was not executed since it was invalid\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}

//Assignment operator overload
//Shallow copying data members of the bomb class since no new data members are being added.
Bomb& Bomb::operator=(const Bomb& bmb) {
    this->gameEng = bmb.gameEng;
    this->Attach(bmb.gameEng->_observer);
    this->currentPlayer = bmb.currentPlayer;
    this->targetTerr = bmb.targetTerr;
    return *this;
}

Bomb::Bomb(const Bomb& bmb) {
    this->gameEng = bmb.gameEng;
    this->Attach(bmb.gameEng->_observer);
    this->currentPlayer = bmb.currentPlayer;
    this->targetTerr = bmb.targetTerr;
}

//Destructor
Bomb::~Bomb() {
    currentPlayer = nullptr;
    targetTerr = nullptr;
    gameEng = nullptr;
    this->Detach();
    cout << "Destructor deleted the Bomb object!" << endl;
};


/**********************************************************/
// BLOCKADE
/**********************************************************/

Blockade::Blockade(/* args */)
{
    cout << "The Blockade Order was made." << endl;
}

Blockade::Blockade(Player* currentPlayer, Territory* targetTerr, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->targetTerr = targetTerr;

}

void Blockade::setTargetTerritory(Territory* targetTerr) {
    targetTerr = targetTerr;
}

Territory* Blockade::getTargetTerritory() {
    return targetTerr;
}

string Blockade::getName() { return name; }

//Stream insertion operator overload
ostream& operator <<(ostream& strm, Blockade& bkd) {
    string blO = "Blockade order\n";
    if (bkd.getIsExecuted()) {
        return strm << blO + bkd.getEffect();
    }
    else return strm << blO;
}


bool Blockade::validate() {
    cout << "Blockade Order validation is in progress...\n" << endl;
    if (getTargetTerritory() == nullptr) {
        cout << "INVALID:Target territory points to NULL" << endl;
        return false;
    }
    if (getIsExecuted()) {
        cout << "INVALID:Blockade order already executed" << endl;
        return false;
    }
    //If the target territory belongs to an enemy player, the order is declared invalid.
    if (!currentPlayer->ownsTerritory(targetTerr)) {
        cout << "INVALID: Target territory belongs to an enemy player!" << endl;
        return false;
    }
    cout << "Blockade order is validated!" << endl;
    return true;
}

//After validation passes, the execution happens
void Blockade::execute() {
    if (Blockade::validate()) {
        cout << "Executing blockade order" << endl;
        //If the target territory belongs to the player issuing the order, the number of army units on the territory is doubled and the ownership 
        //of the territory is transferred to the Neutral player, which must be created if it does not already exist.
        targetTerr->setNumberOfArmies(targetTerr->getNumberOfArmies() * 2);
        gameEng->getNeutralPlayer()->addOwnedTerritory(targetTerr);
        currentPlayer->removeOwnedTerritory(targetTerr);
        setEffect("Successfully doubled the number of armies in " + targetTerr->getName() + " territory" +
            " and ownership changed to neutral player\n");
        cout << getEffect();
        setIsExecuted(true);
    }
    else {
        setEffect("The blockade order was not executed\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}

//Assignment operator overload
//Shallow copying data members of the blockade class since no new data members are being added.
Blockade& Blockade::operator=(const Blockade& bkd) {
    if (&bkd != this) {
        this->gameEng = bkd.gameEng;
        this->Attach(bkd.gameEng->_observer);
        this->currentPlayer = bkd.currentPlayer;
        this->targetTerr = bkd.targetTerr;
    }
    return *this;
}

Blockade::Blockade(const Blockade& bkd) {
    this->gameEng = bkd.gameEng;
    this->Attach(bkd.gameEng->_observer);
    this->currentPlayer = bkd.currentPlayer;
    this->targetTerr = bkd.targetTerr;
}

//Destructor
Blockade::~Blockade() {
    currentPlayer = nullptr;
    targetTerr = nullptr;
    gameEng = nullptr;
    this->Detach();
    cout << "Destructor deleted the Blockade object!" << endl;
};

/**********************************************************/
// AIRLIFT
/**********************************************************/

Airlift::Airlift(/* args */)
{
    cout << "The Airlift Order was made." << endl;
}

Airlift::Airlift(Player* currentPlayer, int n, Territory* sourceTerr, Territory* targetTerr, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->numOfArmies = n;
    this->sourceTerr = sourceTerr;
    this->targetTerr = targetTerr;
}

int Airlift::getNumOfArmies() const {
    return numOfArmies;
}

void Airlift::setNumOfArmies(int numOfArmies) {
    this->numOfArmies = numOfArmies;
}

Territory* Airlift::getTargetTerritory() {
    return targetTerr;
}

void Airlift::setTargetTerritory(Territory* targetTerr) {
    targetTerr = targetTerr;
}

Territory* Airlift::getSourceTerritory() {
    return sourceTerr;
}
void Airlift::setSourceTerritory(Territory* sourceTerr) {
    sourceTerr = sourceTerr;
}

string Airlift::getName() { return name; }

//Stream insertion operator overload
ostream& operator<< (ostream& os, Airlift& air) {
    string aO = "Airlift order\n";
    if (air.getIsExecuted()) {
        return os << aO + air.getEffect();
    }
    else return os << aO;
}
//Airlift order valid if source territory is owned by currentPlayer
bool Airlift::validate() {
    cout << "Airlift Order validation is in progress...\n" << endl;
    if (getTargetTerritory() == nullptr || getSourceTerritory() == nullptr) {
        cout << "Either target territory or source territory points to NULL" << endl;
        return false;
    }
    if (getIsExecuted()) {
        cout << "Order already executed" << endl;
        return false;
    }
    //If the source territory does not belong to the player that issued the order, the order is invalid.
    if (!currentPlayer->ownsTerritory(sourceTerr)) {
        cout << "Airlift order not valid -- " + currentPlayer->getName() +
            " does not own " + sourceTerr->getName() + "(source) territory" << endl;
        return false;
    }
    //If the target territory does not belong to the player that issued the order, the order is invalid.
    else if (!currentPlayer->ownsTerritory(targetTerr)) {
        cout << "Airlift order not valid -- " + currentPlayer->getName() +
            " does not own " + targetTerr->getName() + " target territory" << endl;
        return false;
    }
    cout << "Airlift order is validated!" << endl;
    return true;
}

//If the validation passes, the airlift order is executed
void Airlift::execute() {
    if (Airlift::validate()) {
        cout << "Executing Airlift order" << endl;
        //If both the source and target territories belong to the player that issue the airlift order, then the selected number 
        //of army units is moved from the source to the target territory.
        targetTerr->setNumberOfArmies(targetTerr->getNumberOfArmies() + numOfArmies);
        sourceTerr->setNumberOfArmies(sourceTerr->getNumberOfArmies() - numOfArmies);
        setEffect("Successfully moved " + to_string(getNumOfArmies()) + " armies from " +
            sourceTerr->getName() + " to " + targetTerr->getName() + " territory via airlift\n");
        cout << getEffect();
        setIsExecuted(true);
    }
    else {
        setEffect("Airlift order has not been executed\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}

//Assignment operator overload
//Shallow copying data members of the airlift class since no new data members are being added.
Airlift& Airlift::operator=(const Airlift& air) {
    if (&air != this) {
        this->gameEng = air.gameEng;
        this->Attach(air.gameEng->_observer);
        this->currentPlayer = air.currentPlayer;
        this->sourceTerr = air.sourceTerr;
        this->targetTerr = air.targetTerr;
        this->numOfArmies = air.numOfArmies;
    }
    return *this;
}


Airlift::Airlift(const Airlift& air) {
    this->gameEng = air.gameEng;
    this->Attach(air.gameEng->_observer);
    this->currentPlayer = air.currentPlayer;
    this->sourceTerr = air.sourceTerr;
    this->targetTerr = air.targetTerr;
    this->numOfArmies = air.numOfArmies;
}

//Destructor
Airlift::~Airlift() {
    currentPlayer = nullptr;
    sourceTerr = nullptr;
    targetTerr = nullptr;
    gameEng = nullptr;
    this->Detach();
    cout << "Destructor deleted the Airlift object!" << endl;
};


/**********************************************************/
// NEGOTIATE
/**********************************************************/

Negotiate::Negotiate(/* args */)
{
    cout << "The Negotiate Order was made." << endl;
}

Negotiate::Negotiate(Player* currentPlayer, Player* otherPlayer, GameEngine* gameEng) {
    this->gameEng = gameEng;
    this->Attach(gameEng->_observer);
    this->currentPlayer = currentPlayer;
    this->otherPlayer = otherPlayer;
}


//Stream insertion operator overload
ostream& operator <<(ostream& os, Negotiate& ngt) {
    string nO = "Negotiate order\n";
    if (ngt.getIsExecuted()) {
        return os << nO + ngt.getEffect();
    }
    else return os << nO;
}

/*A negotiate order targets an enemy player. It results in the target player and the player issuing
  the order to not be able to successfully attack each others’ territories for the remainder of the turn. The negotiate
  order can only be created by playing the diplomacy card.*/
bool Negotiate::validate() {
    cout << "Negotiate Order validation is in progress...\n" << endl;
    if (otherPlayer == nullptr) {
        cout << "INVALID:Target Player points to NULL!" << endl;
    }
    if (getIsExecuted()) {
        cout << "INVALID:Negotiate order is already executed!" << endl;
        return false;
    }
    //If the target is the player issuing the order, then the order is invalid.
    if (currentPlayer == otherPlayer) {
        cout << "INVALID:You cannot negotiate with yourself!" << endl;
        return false;
    }
    cout << "Negotiate order is validated!" << endl;
    return true;
}

/*A negotiate order targets an enemy player. It results in the target player and the player issuing
  the order to not be able to successfully attack each others’ territories for the remainder of the turn. The negotiate
  order can only be created by playing the diplomacy card.*/
void Negotiate::execute() {
    //If the target is an enemy player, then the effect is that any attack that may be declared between 
    //territories of the player issuing the negotiate order and the target player will result in an invalid order.
    if (Negotiate::validate()) {
        cout << "Executing Negotiate order" << endl;
        currentPlayer->cannotAttack.push_back(otherPlayer);
        otherPlayer->cannotAttack.push_back(currentPlayer);

        setEffect("Attacking between " + currentPlayer->getName() + " and " + otherPlayer->getName() + " has been prevented until the end of the turn!\n");
        cout << getEffect();
        setIsExecuted(true);
    }
    else {
        setEffect("Negotiate order has not been executed!\n");
        cout << getEffect() << endl;
    }
    Notify(this);
}
//Shallow copying data members of the negotiate class since no new data members are being added.
Negotiate::Negotiate(const Negotiate& ngt) {
    this->gameEng = ngt.gameEng;
    this->Attach(ngt.gameEng->_observer);
    this->currentPlayer = ngt.currentPlayer;
    this->otherPlayer = ngt.otherPlayer;
}


Negotiate& Negotiate::operator=(const Negotiate& ngt) {
    if (&ngt != this) {
        this->gameEng = ngt.gameEng;
        this->Attach(ngt.gameEng->_observer);
        this->currentPlayer = ngt.currentPlayer;
        this->otherPlayer = ngt.otherPlayer;
    }
    return *this;
}

//Destructor
Negotiate::~Negotiate() {
    currentPlayer = nullptr;
    otherPlayer = nullptr;
    gameEng = nullptr;
    this->Detach();
    cout << "Destructor deleted the Negotiate object!" << endl;
};
string Negotiate::getName() { return name; }