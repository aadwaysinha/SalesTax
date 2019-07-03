#include "Item.h"


Item::Item(string itemName, string category, int frequency, double price)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
    this->salesTax = this->getSalesTax();
    this->importTax = this->getImportTax();
    this->H = new Helper();
}


//Returns (T*P/100) tax T on any item of price P
double Item::calculateTax(double price, double taxPercentage)
{
    return H->customRoundTo(price * taxPercentage / 100.0);
}


//Sales tax charged on any item of price P is its 10%
double Item::getSalesTax()
{
    return this->calculateTax(this->price, 10.0);
}


double Item::getImportTax()
{
    //If the item has been imported, consumer needs to pay an additional 5% tax

    //Using KMP search algorithm to check if the itemName contains the token ' imported ' anywhere (imported with padding)
    //Although KMP won't be useful for this particular word 'imported' as it doesn't have any common prefix and suffix
    //but just in case.
    StringPatternMatcher *spm = new StringPatternMatcher(" imported ");

    //If the item has ' imported ' in its name it means that it was imported
    //and the consumer will have to pay 5% extra tax.
    return spm->patternExists(this->itemName) ? calculateTax(this->price, 5.0) : 0;

}


//Overriding outstream operator to print an item at once
//"<<" must be overloaded as a global function and if we want to allow them to access private data members of class, we must make them friend of that class.
ostream & operator << (ostream &out, const Item &I)
{
    cout<<"ITEM: "<<I.itemName<<" belonging to "<<I.category<<" priced at "<<I.price<<endl;
}


int Item::getCurrentFreq()
{
    return this->freq;
}


void Item::updateCurrentFreq(int newFreq)
{
    this->freq = newFreq;
}


string Item::getItemName()
{
    return this->itemName;
}


string Item::getItemCategory()
{
    return this->category;
}


double Item::getPrice()
{
    return this->price;
}


vector<string> Item::tokenize(string S)
{
    return {};
}



Item::~Item()
{
    delete this;
}

Item::Item(const Item& other)
{
    //copy ctor
}

