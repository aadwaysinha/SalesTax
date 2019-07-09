#ifndef STORE_H
#define STORE_H
#include<iostream>
#include<unordered_map>
#include<string>
#include<algorithm>
#include "Item.h"
#include "Cart.h"
#include "CSVHandler.h"
#include "Helper.h"
using namespace std;

class Store
{
    private:

        string storeName;       //Name of the store
        int storeID;            //ID of the store
        Helper *H;  
        unordered_map<string, unordered_map<string, Item>> items;   // Maps different Maps of items to different categories
                                                                    //category1 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}
                                                                    //category2 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}
                                                                    //category3 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}

    public:

        Store(string, int);

        unordered_map<string, unordered_map<string, Item>>& getItems();

        void buyStuff();        //Buy items from the store and save the state

        string getStoreName();  

        int getStoreID();

        void updateFreq(string, string, int);   //Update item list after transactions take place

        ~Store();

    protected:

};

#endif // STORE_H
