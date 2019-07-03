#include "Cart.h"

Cart::Cart(Store &store)
{
    //ctor
    H = new Helper();
}


queue<Item>& Cart::getBucket()
{
    return this->bucket;
}


void Cart::addToCart()
{
    //print menu by cout<<Store

    cout<<"To stop, type 'quit' and press enter";
    
    cout<<"Make sure you order in this format: {Number of item} {item} {price}"<<endl;
    cout<<"Example: \n1 imported bottle of perfume at 27.99 \n1 bottle of perfume at 18.99"<<endl;

    while(1)
    {
        vector<string> order;
        Item *item2bBought; 
        while(order.size() != 3)
        {
            string s;
            getline(cin, s);
            H->toLower(s);
            if(s == "quit")
                break;
            order = item2bBought->tokenize(s);
        }
        
    }

}



void Cart::generateBill()
{
    while(!this->bucket.empty());
    {
        Item &frontItem = this->bucket.front();
        cout<<frontItem;
        this->total += frontItem.getPrice();
        this->totalTax += frontItem.getSalesTax() + frontItem.getImportTax();
        this->bucket.pop();
    }
    cout<<"Sales Taxes: "<<this->totalTax<<endl;
    cout<<"Total: "<<this->total + this->totalTax<<endl;
}





Cart::~Cart()
{
    //dtor
}
