#include <iostream>
#include "Orders.h"
#include "OrdersDriver.h"
using namespace std;
using std::cout;
using std::endl;
using std::ostream;

int main() {
    testOrdersLists();
    //Testing the creation of one of the orders (deploy in this case)
    Deploy dpl;
    cout << "before" << endl;
    cout << dpl << endl;
    dpl.execute();
    cout << "After the execution" << endl;
    cout << dpl << endl;

    return 0;
}

