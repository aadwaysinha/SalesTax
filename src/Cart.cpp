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

    unordered_map<string, unordered_map<string, Item>> &allItems = this->store->getItems();
    while(1)
    {

        cout<<"Enter\n";

        vector<string> order;
        Item *item2bBought; 
        bool toBeSkipped = false;
        string s;
        
        while(order.size() != 3)
        {
            getline(cin, s);
            H->toLower(s);
            if(s == "quit")
            {
                toBeSkipped = true;
                break;
            }
            order = item2bBought->tokenize(s);

            if(order.size()!=3)
                cout<<"Wrong format, please enter again\n";             
        }
        

        //User chose to not buy anything
        if(toBeSkipped) 
            break;

        //Category of the item hasnt been classified yet
        item2bBought = new Item(order[1], "TBD", stoi(order[0]), stod(order[2]));

        //Searching for the category which this item belongs to
        for(int i=0; i<this->category.size(); i++)
        {
            auto itr = allItems[category[i]].find(order[1]);

            if(itr != allItems[category[i]].end())
            {

                //Category of the item needs to be changed from "TBD" to category[i]
                item2bBought->changeCategory(category[i]);
                
                Item &item = itr->second;
                if(item.getCurrentFreq() < stoi(order[0]))
                {
                    cout<<"Store has got only "<<item.getCurrentFreq()<<" of these, do you want to buy them all or skip?\n";
                    string choice;
                    cout<<"Type (skip/all) and press enter\n";
                    cin>>choice;

                    H->toLower(choice);

                    if(choice == "skip")
                    {
                        toBeSkipped = true;
                        break;
                    }
                    else
                    {

                        //If the item is present in ample amount then we can add it to our cart,
                        //while doing this, we also need to reduce the freq of them being bought
                        //from the store

                        item2bBought->updateCurrentFreq(item.getCurrentFreq());
                        int oldFreq = allItems[category[i]][order[1]].getCurrentFreq();
                        allItems[category[i]][order[1]].updateCurrentFreq(oldFreq - item2bBought->getCurrentFreq());
                    }                    
                }

                if(!toBeSkipped)
                    this->bucket.push(*item2bBought);


                //Now this loop needs to end because we found the category and we have bought this item
                break;
            }
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
