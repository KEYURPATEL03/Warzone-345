#include <iostream>
#include <string>
#include "Orders.h"
#include "OrdersDriver.h"
using namespace std;
using std::endl;
using std::ostream;
using std::string;

Orders::Orders()
{
    //Here we are telling what should be done when we create an object of type Orders
      cout << "An Order object has been created." << endl;
}

Orders::~Orders()
{
    cout << "Destructor deleted the Orders object!" << endl;
}

OrdersList::OrdersList()
{
    cout << "OrdersList has been created!" << endl;
}

OrdersList::~OrdersList()
{
    cout << "Destructor deleted the OrdersList object!" << endl;
}

Deploy::Deploy(/* args */)
{
    cout << "The Deploy Order was made." << endl;
}

Deploy::~Deploy()
{
    cout << "Destructor deleted the Deploy object!" << endl;
}

Advance::Advance(/* args */)
{
    cout << "The Advance Order was made." << endl;
}

Advance::~Advance()
{
    cout << "Destructor deleted the Advance object!" << endl;
}

Bomb::Bomb(/* args */)
{
    cout << "The Deploy Order was made." << endl;
}

Bomb::~Bomb()
{
    cout << "Destructor deleted the Bomb object!" << endl;
}

Blockade::Blockade(/* args */)
{
    cout << "The Blockade Order was made." << endl;
}

Blockade::~Blockade()
{
    cout << "Destructor deleted the Blockade object!" << endl;
}

Airlift::Airlift(/* args */)
{
    cout << "The Airlift Order was made." << endl;
}

Airlift::~Airlift()
{
    cout << "Destructor deleted the Airlift object!" << endl;
}

Negotiate::Negotiate(/* args */)
{
    cout << "The Negotiate Order was made." << endl;
}

Negotiate::~Negotiate()
{
    cout << "Destructor deleted the Negotiate object!" << endl;
}

//Stream Insertion Operator Definition
ostream& operator<<(ostream& os, Orders& ord){
    os << "This is an "<< ord.getName() <<" object." << endl;
    if(ord.getEffect() != ""){
        os << ord.getEffect() << endl;
    }
    return os;
}


ostream& operator<<(ostream& os, Deploy& dpl){
    os << "This is a "<< dpl.getName() <<" object." << endl;
    if(dpl.getEffect() != ""){
    os << dpl.getEffect() << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, Advance& adv){
    os << "This is an "<< adv.getName() <<" object." << endl;
    if(adv.getEffect() != ""){
    os << adv.getEffect() << endl;
    }
    return os;  
}
ostream& operator<<(ostream& os, Bomb& bmb){
    os << "This is a "<< bmb.getName() <<" object." << endl;
    if(bmb.getEffect() != ""){
    os << bmb.getEffect() << endl;
    }
    return os;  
}
ostream& operator<<(ostream& os, Blockade& bkd){
    os << "This is a "<< bkd.getName() <<" object." << endl;
    if(bkd.getEffect() != ""){
    os << bkd.getEffect() << endl;
    }
    return os;  
}
ostream& operator<<(ostream& os, Airlift& air){
    os << "This is an "<< air.getName() <<" object." << endl;
    if(air.getEffect() != ""){
    os << air.getEffect() << endl;
    }
    return os;  
}
ostream& operator<<(ostream& os, Negotiate& ngt){
    os << "This is a "<< ngt.getName() <<" object." << endl;
    if(ngt.getEffect() != ""){
    os << ngt.getEffect() << endl;
    }
    return os;  
}


//Getter methods for the Orders class
string Orders::getName() {
    return this->name;
}

string Orders::getEffect() {
    return this->effect;
}

//Setter methods for the Orders class
void Orders::setEffect(string ordersEffect) {
    effect = ordersEffect;
}

//Getter method for the different type of orders (for getting the name information):

string Deploy::getName() {
    return this->name;
}
string Advance::getName() {
     return this->name;
}
string Bomb::getName() {
     return this->name;
}
string Blockade::getName() {
     return this->name;
}
string Airlift::getName() {
     return this->name;
}
string Negotiate::getName() {
     return this->name;
}

//Getter method for the different type of orders (for getting the execute information):

string Deploy::getEffect() {
    return this->effect;
}
string Advance::getEffect() {
     return this->effect;
}
string Bomb::getEffect() {
     return this->effect;
}
string Blockade::getEffect() {
     return this->effect;
}
string Airlift::getEffect() {
     return this->effect;
}
string Negotiate::getEffect() {
     return this->effect;
}

//Setter method for the different type of orders (for getting the execute information):

void Deploy::setEffect(string deployEffect) {
    effect = deployEffect;
}
void Advance::setEffect(string advanceEffect) {
    effect = advanceEffect;
}
void Bomb::setEffect(string bombEffect) {
    effect = bombEffect;
}
void Blockade::setEffect(string blockadeEffect) {
    effect = blockadeEffect;
}
void Airlift::setEffect(string airliftEffect) {
    effect = airliftEffect;
}
void Negotiate::setEffect(string negotiateEffect) {
    effect = negotiateEffect;
}

//Validate method for the orders:

bool Deploy::validate() {
    cout << "The deployment has been validated!" << endl;
    return true;
}

bool Advance::validate() {
    cout << "The advancement has been validated!" << endl;
    return true;
}

bool Bomb::validate() {
    cout << "The bomb has been validated!" << endl;
    return true;
}
bool Blockade::validate() {
    cout << "The blockade has been validated!" << endl;
    return true;
}
bool Airlift::validate() {
    cout << "The airlift has been validated!" << endl;
    return true;
}
bool Negotiate::validate() {
    cout << "The negotiation has been validated!" << endl;
    return true;
}

//Execute method for the orders:

void Deploy::execute() {
    if(Deploy::validate()){
    this->setEffect("The Deploy oder has been executed! This puts a certain number of army units on a target territory.");
    }
}
void Advance::execute() {
    if(Advance::validate()){
    this->setEffect("The Advance oder has been executed! This moves a certain number of army units from one territory (source territory) to another territory (target territory).");
    }
}
void Bomb::execute() {
    if(Bomb::validate()){
    this->setEffect("The Bomb oder has been executed! This destroys half of the army units located on a target territory. This order can only be issued if a player has the bomb card in their hand.");
    }
}
void Blockade::execute() {
    if(Blockade::validate()){
    this->setEffect("The Blockade oder has been executed! This triples the number of army units on a target territory and make it a neutral territory. This order can only be issued if a player has the blockade card in their hand.");
    }
}
void Airlift::execute() {
    if(Airlift::validate()){
    this->setEffect("The Airlift oder has been executed! This advances a certain number of army units from one from one territory (source territory) to another territory (target territory)." 
    "This order can only be issued if a player has the airlift card in their hand.");
    }
}
void Negotiate::execute() {
    if(Negotiate::validate()){
    this->setEffect("The Negotiate oder has been executed! This prevents attacks between the current player and another target player until the end of the turn. This order can only be issued if a player has the diplomacy card in their hand.");
    }
}

//OrdersList addToListOfOrders() function
void OrdersList::addToListOfOrders(Orders* ord){
    this->listOfOrders.push_back(ord);
}

//OrdersList getListOfOrders() function
list<Orders*> OrdersList::getListOfOrders(){
    return this->listOfOrders;
}

//OrdersList remove() function
void OrdersList::remove(Orders* ord){
    listOfOrders.remove(ord);
}

//Stream Insertion Operator Definition
ostream& operator<<(ostream& os, OrdersList& ordL){
    for(Orders* ord : ordL.getListOfOrders()){
        os << *ord;
    }
    return os;
}

