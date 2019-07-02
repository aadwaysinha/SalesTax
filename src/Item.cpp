#include "Item.h"
#include "StringPatternMatcher.h"
#include<cmath>

Item::Item(string itemName, string category, int frequency, double price)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
    this->salesTax = this->getSalesTax();
    this->importTax = this->getImportTax();
}


//Rounds up any value to the nearest roundTo, by default roundTo is set to 0.05 as asked in the question
double Item::customRoundTo(double val, double roundTo = 0.05)
{
    double roundToDivisor = 1/roundTo;
    double res1 = (val * roundToDivisor) / roundToDivisor;
    int res2 = res1 * 100;
    double res3 = round((double)res2)/100.0;
    return res3;
}


//Returns (T*P/100) tax T on any item of price P
double Item::calculateTax(double price, double taxPercentage)
{
    return customRoundTo(price * taxPercentage / 100.0);
}


//Sales tax charged on any item of price P is its 10%
double Item::getSalesTax()
{
    return this->calculateTax(this->price, 10.0);
}


double Item::getImportTax()
{
    //If the item has been imported it needs to pay an additional 5% tax

    //Using KMP search algorithm to check if the itemName contains the token ' imported ' anywhere (imported with padding)
    //Although KMP won't be useful for this particular word 'imported' as it doesn't have any common prefix and suffix
    //but just in case.
    StringPatternMatcher *spm = new StringPatternMatcher(" imported ");

    //If the item has
    return spm->patternExists(this->itemName) ? calculateTax(this->price, 5.0) : 0;

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


Item::~Item()
{
    //dtor
}

Item::Item(const Item& other)
{
    //copy ctor
}

