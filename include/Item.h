#ifndef ITEM_H
#define ITEM_H
#include<iostream>
#include<vector>
#include "StringPatternMatcher.h"
#include "Helper.h"
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
        Helper *H;

        //Operator overloading for finding an Item in an unordered_set of Items by its name.
        bool operator == (const Item& otherItem) 
        {
            return this->itemName == otherItem.itemName;
        }

        bool operator<(const Item& otherItem) const
        {
            return this->itemName < otherItem.itemName ? true : false;
        }

        double customRoundTo(double, double);

        double calculateTax(double, double);

        friend ostream & operator << (ostream &out, const Item &I); 

    public:
        Item(string, string, int, double);
        
        double getSalesTax();

        double getImportTax();

        string getItemName();

        string getItemCategory();

        double getPrice();

        int getCurrentFreq();

        void updateCurrentFreq(int);

        vector<string> tokenize(string);

        ~Item();

        Item(const Item& other);
};

#endif // ITEM_H
