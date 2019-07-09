#ifndef CART_H
#define CART_H
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<iomanip>
#include<conio.h>
#include "Store.h"
#include "Item.h"
#include "Helper.h"
using namespace std;

class Store;

class Cart
{
    private:

        double total;               //sum of all the base prices in the cart
        double totalTax;            //sum of all taxes(sales + import) for the items in the cart
        queue<Item> bucket;         //A queue to store all the items
        vector<string> category;    //category vector, always has 4 categories: book, medical, food, other
                                    //needs to be maintained for searching optimization 
        Store *store;               //store to which this cart belongs to
        Helper *H;

    public:

        Cart(Store &store);

        queue<Item>& getBucket();

        void addToCart();           //BUY here, main function for buying items from any store

        void generateBill();        //generates the bill

        ~Cart();
};

#endif // CART_H
