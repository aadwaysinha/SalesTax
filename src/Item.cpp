#include "Item.h"


Item::Item()
{

}


Item::Item(string itemName, string category, int frequency, double price)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
    this->freq = frequency;
    this->salesTax = this->getSalesTax();
    this->importTax = this->getImportTax();
    this->H = new Helper();
}


//Returns (T*P/100) tax T on any item of price P
double Item::calculateTax(double price, double taxPercentage)
{
    return H->customRoundTo(price * taxPercentage / 100.0, 0.05);
}


//Sales tax charged on any item of price P is its 10%
double Item::getSalesTax()
{
    if(this->category == "book" || this->category == "medical" || this->category == "food")
        return 0;
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
    cout<<"ITEM: "<<I.freq<<" "<<I.itemName<<" belonging to "<<I.category<<" priced at "<<I.price<<" ST: "<<I.salesTax<<" IT: "<<I.importTax<<endl;
}


int Item::getCurrentFreq()
{
    return this->freq;
}


void Item::changeCategory(string cat)
{
    this->category = cat;
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


bool Item::isTokenValid(vector<string> token)
{
    //Must have three elements: Freq, itemName, price
    if(token.size() != 3)
        return false;

    for(int i=0; i<3; i++)
        if(token[i].size() == 0)
            return false;

    int freq = H->stoi(token[0]);
    int price = H->stod(token[2]);

    //Frequency must be in this range, if not then it must be an invalid token
    if(!(freq >= 0 && freq <= INT_MAX))
        return false;

    //Price must be in this range, if not then it must be an invalid token
    if(!(price >= 0 && price <= INT_MAX))
        return false;

    return true;
}


vector<string> Item::tokenize(string S)
{
    //Getting the price from the right side
    int right = S.length()-1;
    string price = "";
    while(right>=0 && S[right]!=' ')
    {
        price += S[right];
        right--;
    }
    reverse(price.begin(), price.end());

    //right pointer should go as input format will always have 'at' between itemName and price
    right -= 3;


    //Getting the frequency from the left side
    int left = 0;
    string freq;
    while(left<S.length() && S[left]!=' ')
    {
        freq += S[left];
        left++;
    }

    //Now from current left to current right(both exclusive), all the characters
    //must be a part of the item name
    string itemName;
    for(int i=left+1; i<=right-1; i++)
        itemName += S[i];

    vector<string> tokenized = {freq, itemName, price};

    if(isTokenValid(tokenized))
        return tokenized;

    else
        return {};
}
