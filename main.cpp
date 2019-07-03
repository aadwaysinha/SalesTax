#include<iostream>
#include "StringPatternMatcher.h"
#include "Tests.h"
#include "Item.h"
#include "CSVHandler.h"
#include "Store.h"
using namespace std;

int main()
{

    Tests *test = new Tests();
    test->runAllTests();
    cout<<"All tests ran successfully and no bug was found.\n";

    Store *store = new Store("Aadways");
    cout<<"Data fetched\n";
    store->addItems();
    store->printAllItems();
}
