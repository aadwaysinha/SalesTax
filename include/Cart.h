#ifndef CART_H
#define CART_H
#include<iostream>
#include<queue>
#include<vector>
#include "Store.h"
#include "Item.h"
#include "Helper.h"
using namespace std;


class Cart
{
    private:
        double total;
        double totalBill;
        double totalTax;
        queue<Item> bucket;
        vector<string> category;
        Store *store;
        Helper *H;

    public:
        Cart(Store &);
        
        queue<Item>& getBucket();

        void addToCart();

        void generateBill();


        ~Cart();

    protected:

};

#endif // CART_H
