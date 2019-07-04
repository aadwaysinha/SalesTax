#ifndef ITEM_H
#define ITEM_H
#include<iostream>
#include<vector>
#include<algorithm>
#include "StringPatternMatcher.h"
#include "Helper.h"
using namespace std;

class Item
{
    private:
        string itemName;        //Name of the item
        double price;           //Price of the item
        string category;        //Category of the item, must be in (book, food, medical, other)
        int freq;               //Quantity
        double salesTax;        //Sales tax on this item
        double importTax;       //Import tax on this item
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

        bool isTokenValid(vector<string>);              //Validate order

        double calculateTax(double, double);            //calculate any tax on any price, base tax calculator

        friend ostream & operator << (ostream &out, const Item &I);

    public:
        Item();     //do not delete this

        Item(string, string, int, double);              //parameterized constructor for creating items

        double calculateSalesTax(double);               //calculates sales tax on any item

        double calculateImportTax(double);              //calculates import tax on any item

        string getItemName();

        string getItemCategory();

        double getPrice();

        int getCurrentFreq();

        void updateCurrentFreq(int);                    //Changes quantity of any item present after transactions

        void updateSalesTax(double perc = 10.0);

        void updateImportTax(double perc = 5.0);

        double getSalesTax();

        double getImportTax();

        void changeCategory(string);                

        vector<string> tokenize(string);
};

#endif // ITEM_H
