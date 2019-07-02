#ifndef STORE_H
#define STORE_H
#include<iostream>
#include<unordered_map>
#include "Item.h"
#include "Cart.h"
#include "CSVHandler.h"
#include<string>
using namespace std;

class Store
{
    private:
        static int storeNumber;
        string storeName;
        const int storeID;
        unordered_map<string, unordered_map<string, Item>> items;   // Maps different Maps of items to different categories
                                                                    //category1 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...} 
                                                                    //category2 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...} 
                                                                    //category3 --> {Map[itemName1]_{item1}, Map[itemName2]_{item2}, Map[itemName3]_{item3}...} 


        void toLower(string &s);

    public:
        Store(string);

        void addItems();

        void buyStuff();

        ~Store();

    protected:

};

#endif // STORE_H
