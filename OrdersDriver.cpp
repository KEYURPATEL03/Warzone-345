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
         Deploy* deployOrder = new Deploy();
         Advance* advanceOrder = new Advance();
         Bomb* bombOrder = new Bomb();
         Blockade* blockadeOrder = new Blockade();
         Airlift* airliftOrder = new Airlift();
         Negotiate* negotiateOrder = new Negotiate();

         OrdersList ordersListObj;

         ordersListObj.addToListOfOrders(deployOrder);
         ordersListObj.addToListOfOrders(advanceOrder);
         ordersListObj.addToListOfOrders(bombOrder);
         ordersListObj.addToListOfOrders(blockadeOrder);
         ordersListObj.addToListOfOrders(airliftOrder);
         ordersListObj.addToListOfOrders(negotiateOrder);

         //NOT WORKING
         cout << ordersListObj << endl;
//         ordersListObj.remove(deployOrder);
//        cout << ordersListObj << endl;

    }
