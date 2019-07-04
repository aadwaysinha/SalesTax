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
    // Tests *test = new Tests();
    // test->runAllTests();
    // cout<<"All tests ran successfully and no bug was found.\n\n";

    Market *market = new Market();

    market->loadMarket();

    char choice = 'n';

    do
    {
        cout<<"Choose from the following\n";
        cout<<"1 to enter a store\n";
        cout<<"2 to create a store\n\n";

        cout<<"Choice: ";
        int mood;
        cin>>mood;

        switch(mood)
        {
            case 1 :
                {

                    //Choosing store
                    cout<<endl;
                    market->displayMarket();
                    cout<<"\n\nChoose storeID\n\n";
                    int storeID;
                    cout<<"StoreID: ";
                    cin>>storeID;
                    string storeName = market->getStoreName(storeID);

                    //Initializing store and fetching items
                    Store *store = new Store(storeName, storeID);
                    cout<<"\nChoose action\n";
                    cout<<"1 to buy items\n";
                    cout<<"2 to add items\n\n";
                    cout<<"Action: ";
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
                break;

            case 2 :
                {
                    cout<<"\n\nEnter name of your store\n";
                    string storeName;
                    cin>>storeName;

                    //fetching maximum storeID from the market
                    map<int, string> storeL = market->getStoreList();
                    int lastStoreID = 1;
                    for(auto itr = storeL.begin(); itr != storeL.end(); itr++)
                        lastStoreID = max(lastStoreID, itr->first);

                    //maximum + 1
                    int storeID = lastStoreID + 1;


                    //Creating store and inserting items into it
                    Store *store = new Store(storeName, storeID);
                    CSVHandler *creator = new CSVHandler();
                    creator->writeData(*store);
                    store->addItems();

                    cout<<"\n\nNew store has been created\n\n";

                    //updating market because of a new store
                    market->updateStoreList(storeID, storeName);
                    market->writeData();
                    market->loadMarket();
                }
                break;

            default :
                cout<<"That choice did not exist\n";

        }

    cout<<"Wish to quit? (y/n)\n";
    cin>>choice;
    cout<<endl<<endl;
    }while(choice!='y');

}



/*
Issues:
    1. If price exceeds 6 digits it might lose some precision
*/

