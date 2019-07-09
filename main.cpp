#include<iostream>
#include "StringPatternMatcher.h"
#include "Tests.h"
#include "Item.h"
#include "CSVHandler.h"
#include "Store.h"
#include "Market.h"
using namespace std;

int main()
{

    //Comment out to skip tests
    //Tests *test = new Tests();
    //test->runAllTests();
    //cout<<"All tests ran successfully and no bug was found.\n\n";

    Market *market = new Market();

    market->loadMarket();

    int storeID = 1;

    string storeName = market->getStoreName(storeID);

    Store *store = new Store(storeName, storeID);

    store->buyStuff();

}



/*
Issues:
    1. If price exceeds 6 digits it might lose some precision
*/

