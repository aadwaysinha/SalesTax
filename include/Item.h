#ifndef ITEM_H
#define ITEM_H
#include<iostream>
using namespace std;

class Item
{
    private:
        string itemName;
        double price;
        string category;
        int freq;
        double salesTax;
        double importTax;

        //Operator overloading for finding an Item in an unordered_set of Items by its name.
        bool operator == (const Item *ITEM) const
        {
            return this->itemName == ITEM->itemName;
        }

    public:
        Item();
        ~Item();
        Item(const Item& other);
};

#endif // ITEM_H
