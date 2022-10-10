#include <iostream>
#include "Orders.h"
#include "OrdersDriver.h"
using namespace std;
using std::cout;
using std::endl;
using std::ostream;

OrdersDriver::OrdersDriver(/* args */)
{
}

OrdersDriver::~OrdersDriver()
{
}

    void testOrdersLists() {
        //Declaring the different types of orders:
         Deploy* deployOrder = new Deploy();
         Advance* advanceOrder = new Advance();
         Bomb* bombOrder = new Bomb();
         Blockade* blockadeOrder = new Blockade();
         Airlift* airliftOrder = new Airlift();
         Negotiate* negotiateOrder = new Negotiate();

         //Declaring the List of Orders object:
         OrdersList ordersListObj;

         //Adding inside the List of Orders object one of each type of Order:
         ordersListObj.addToListOfOrders(deployOrder);
         ordersListObj.addToListOfOrders(advanceOrder);
         ordersListObj.addToListOfOrders(bombOrder);
         ordersListObj.addToListOfOrders(blockadeOrder);
         ordersListObj.addToListOfOrders(airliftOrder);
         ordersListObj.addToListOfOrders(negotiateOrder);

         //Testing the printing of the list of Orders:
         cout << ordersListObj << endl;
         //Testing the removal of an order from the list of Orders (using the index):
         ordersListObj.remove(2);
         //Testing the printing of the list of Orders after the removal of an Order:
         cout << ordersListObj << endl;
         //Testing move method:
         ordersListObj.move(0, 4);
        //Testing the printing of the list of Orders after the move method was used:
         cout << ordersListObj << endl;

        //To avoid memory leak we are deleting the pointers.
        delete deployOrder;
        delete advanceOrder;
        delete bombOrder;
        delete blockadeOrder;
        delete airliftOrder;
        delete negotiateOrder;

    }
