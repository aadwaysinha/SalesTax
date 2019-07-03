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

        bool isTokenValid(vector<string>);

        double customRoundTo(double, double);

        double calculateTax(double, double);

        friend ostream & operator << (ostream &out, const Item &I);

    public:
        Item();

        Item(string, string, int, double);

        double calculateSalesTax(double);

        double calculateImportTax(double);

        string getItemName();

        string getItemCategory();

        double getPrice();

        int getCurrentFreq();

        void updateCurrentFreq(int);

        void updateSalesTax(double perc = 10.0);

        void updateImportTax(double perc = 5.0);

        double getSalesTax();

        double getImportTax();

        void changeCategory(string);

        vector<string> tokenize(string);
};

#endif // ITEM_H
