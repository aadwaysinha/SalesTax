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
    Tests *test = new Tests();
    test->runAllTests();
    cout<<"All tests ran successfully and no bug was found.\n";

    Market *market = new Market();

    market->loadMarket();

    char choice = 'n';
    cout<<"ENTER 'y' TO QUIT\n";

    do
    {
        cout<<"Choose from the following\n";
        cout<<"1 to enter a store\n";
        cout<<"2 to create a store\n\n";

        int mood;
        cin>>mood;

        switch(mood)
        {
            case 1 :
                {

                    //Choosing store
                    market->displayMarket();
                    cout<<"\n\nChoose storeID\n";
                    int storeID;
                    cin>>storeID;
                    string storeName = market->getStoreName(storeID);

                    //Initializing store and fetching items
                    Store *store = new Store(storeName, storeID);
                    cout<<"\nChoose action\n";
                    cout<<"1 to buy items\n";
                    cout<<"2 to add items\n\n";

                    int action;
                    cin>>action;

                    switch(action)
                    {
                        case 1 :
                            store->buyStuff();
                            break;
                        case 2:
                            store->addItems();
                            break;
                        default:
                            cout<<"Sorry, that action did not exist\n";
                    }
                }
        }

    cout<<"Wish to quit?\n";
    cin>>choice;

    }while(choice!='y');
}



/*
bugs:
    1. If price exceeds 6 digits it might lose some precision
*/

