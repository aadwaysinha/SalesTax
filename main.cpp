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

    Store *store = new Store("Aadway's");
    cout<<"Data fetched\n";



    store->buyStuff();

}



/*
bugs:
    1. If price exceeds 6 digits it might lose some precision
*/

