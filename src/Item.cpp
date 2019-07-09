#include "Item.h"

//Do not remove this constructor
Item::Item()
{}


//Parameterized constructor for creating items
Item::Item(string itemName, string category, int frequency, double price) : salesTax(0.0), importTax(0.0)
{
    this->itemName = itemName;
    this->category = category;
    this->price = price;
    this->freq = frequency;
    this->salesTax = this->calculateSalesTax(10.0);
    this->importTax = this->calculateImportTax(5.0);
    this->H = new Helper();
}


//Returns (T*P/100) tax T on any item of price P
double Item::calculateTax(double price, double taxPercentage)
{
    return H->customRoundTo(price * taxPercentage / 100.0, 0.05);
}


//Sales tax charged on any item of price P is its 10%
double Item::calculateSalesTax(double perc)
{
    if(this->category == "book" || this->category == "medical" || this->category == "food")
        return 0.0;
    return this->calculateTax(this->price, perc);
}


//Calculates import tax on any good. If it wasnt imported, returns 0
double Item::calculateImportTax(double perc)
{
    //If the item has been imported, consumer needs to pay an additional 5% tax

    //Using KMP search algorithm to check if the itemName contains the token ' imported ' anywhere (imported with padding)
    //Although KMP won't be useful for this particular word 'imported' as it doesn't have any common prefix and suffix
    //but just in case.
    StringPatternMatcher *spm = new StringPatternMatcher("imported");

    //If the item has ' imported ' in its name it means that it was imported
    //and the consumer will have to pay 5% extra tax.
    return spm->patternExists(this->itemName) ? calculateTax(this->price, perc) : 0.0;

}


//Used in addToCart of Cart
void Item::updateSalesTax(double perc)
{
    this->salesTax = this->calculateSalesTax(perc);
}


//Used in addToCart of Cart
void Item::updateImportTax(double perc)
{
    this->salesTax = this->calculateImportTax(perc);
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


double Item::getSalesTax()
{
    return this->salesTax;
}

double Item::getImportTax()
{
    return this->importTax;
}

void Item::updateName(string newName)
{
    this->itemName = newName;
}

//Used in Cart class while ordering item, checks if the input was valid or not
bool Item::isTokenValid(vector<string> token)
{
    //Must have three elements: Freq, itemName, price
    if(token.size() != 3)
        return false;

    for(int i=0; i<3; i++)
        if(token[i].size() == 0)
            return false;

    for(int i=0; i<token[0].length(); i++)
        if(!(token[0][i] >= '0' && token[0][i] <= '9'))
            return false;

    int freq = H->stoi(token[0]);
    double price = H->stod(token[2]);

    //Frequency must be in this range, if not then it must be an invalid token
    if(!(freq >= 0 && freq <= INT_MAX))
        return false;

    //Price must be in this range, if not then it must be an invalid token
    if(!(price >= 0 && price <= INT_MAX))
        return false;

    return true;
}


//Helps in tokenizing the order
vector<string> Item::tokenize(string S)
{
    //Getting the price from the right side
    int right = S.length()-1;

    //Trimming from right side, removing spaces
    while(S[right] == ' ')
        right--;

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

    //Trimming from left side, removing spaces
    while(S[left] == ' ')
        left++;

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
