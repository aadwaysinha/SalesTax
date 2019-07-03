#ifndef STORE_H
#define STORE_H
#include<iostream>
#include<unordered_map>
#include<string>
#include "Item.h"
#include "Cart.h"
#include "CSVHandler.h"
#include "Helper.h"
using namespace std;

class Store
{
    private:
        string storeName;
        int storeID;
        Helper *H;
        unordered_map<string, unordered_map<string, Item>> items;   // Maps different Maps of items to different categories
                                                                    //category1 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}
                                                                    //category2 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}
                                                                    //category3 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...}

    public:
        static int storeNumber;

        Store(string);

        unordered_map<string, unordered_map<string, Item>>& getItems();

        void addItems();

        void buyStuff();

        string getStoreName();

        int getStoreID();

        void printAllItems();

        ~Store();

    protected:

};

#endif // STORE_H
