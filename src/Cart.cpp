#include "Cart.h"

Cart::Cart(Store &store) : total(0.0), totalBill(0.0), totalTax(0.0)
{
    this->store = &store;
    this->category = {"book", "medical", "food", "other"};
    H = new Helper();
}


queue<Item>& Cart::getBucket()
{
    return this->bucket;
}


void Cart::addToCart()
{
    //print menu by cout<<Store

    cout<<"To stop, type 'quit' and press enter\n\n";

    cout<<"Make sure you order in this format: {Number of item} {item} {price}\n\n"<<endl;
    cout<<"Example: \n1 imported bottle of perfume at 27.99 \n1 bottle of perfume at 18.99\n\n"<<endl;

    unordered_map<string, unordered_map<string, Item>> &allItems = this->store->getItems();


    cout<<allItems.size()<<endl;
    cout<<"Type 'quit' and press enter to stop buying\n\n";

    while(1)
    {

        cin.clear();
        cout<<"\n\n\nEnter details\n";

        vector<string> order;
        Item *item2bBought;
        bool toBeSkipped = false;
        string s;
        bool firstTry = true;
        bool itemFound = false;

        do
        {
            !firstTry ? cout<<"Wrong format, try again\n" : firstTry = false;
            getline(cin, s);
            H->toLower(s);
            if(s == "quit")
            {
                toBeSkipped = true;
                break;
            }
            order = item2bBought->tokenize(s);
        }
        while(order.size()!=3);

        //User chose to not buy anything
        if(toBeSkipped)
            break;

        //Category of the item hasnt been classified yet
        item2bBought = new Item(order[1], "TBD", H->stoi(order[0]), H->stod(order[2]));


        //Searching for the category which this item belongs to
        for(int i=0; i<this->category.size(); i++)
        {
            unordered_map<string, Item> &currentCategory = allItems[category[i]];

            if(currentCategory.find(item2bBought->getItemName()) == currentCategory.end())
                continue;
            else
            {
                //Category of the item needs to be changed from "TBD" to category[i]
                item2bBought->changeCategory(category[i]);
                item2bBought->updateSalesTax();
                item2bBought->updateSalesTax();
                itemFound = true;

                Item &item = currentCategory[item2bBought->getItemName()];

                cout<<item<<endl;

                if(item.getCurrentFreq() < H->stoi(order[0]))
                {
                    cout<<"Store has got only "<<item.getCurrentFreq()<<" of these, do you want to buy them all or skip?\n";
                    string choice;
                    cout<<"Type (skip/all) and press enter\n";
                    getline(cin, choice);

                    H->toLower(choice);

                    if(choice == "skip")
                    {
                        toBeSkipped = true;
                        break;
                    }
                    item2bBought->updateCurrentFreq(item.getCurrentFreq());
                }
                else
                {

                    //If the item is present in ample amount then we can add it to our cart,
                    //while doing this, we also need to reduce the freq of them being bought
                    //from the store

                    int oldFreq = allItems[category[i]][order[1]].getCurrentFreq();
                    this->store->updateFreq(category[i], order[1], oldFreq - item2bBought->getCurrentFreq());
                }
                //Now this loop needs to end because we found the category and we have bought this item
                break;
            }
        }
        bool itemAdded = false;
        if(!toBeSkipped && item2bBought->getCurrentFreq())
        {
            itemAdded = true;
            this->bucket.push(*item2bBought);
        }
        if(itemFound)
        {
            if(itemAdded)
                cout<<"Your item was added to the cart\n";
            else
                cout<<"Your item has been skipped\n";
        }
        else
            cout<<"Sorry, item not found";
    }
}



void Cart::generateBill()
{
    queue<Item> &buck = this->bucket;

    while(!buck.empty())
    {
        Item frontItem = buck.front();
        cout<<frontItem;
        this->total += (frontItem.getCurrentFreq()*frontItem.getPrice());
        this->totalTax += frontItem.getSalesTax() + frontItem.getImportTax();
        totalTax *= frontItem.getCurrentFreq();
        buck.pop();
    }
    cout<<"Sales Taxes: "<<this->totalTax<<endl;
    cout<<"Total: "<<this->total + this->totalTax<<endl;
}

Cart::~Cart()
{
    delete this;
}
