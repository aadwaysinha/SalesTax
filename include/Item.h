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

        double customRoundTo(double, double);

        double calculateTax(double, double);

        friend ostream & operator << (ostream &out, const Item &c); 

    public:
        Item(string, string, int, double);
        
        double getSalesTax();

        double getImportTax();

        string getItemName();

        string getItemCategory();

        double getPrice();

        ~Item();
        Item(const Item& other);
};

#endif // ITEM_H
