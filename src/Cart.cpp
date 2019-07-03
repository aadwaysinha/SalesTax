#include "Cart.h"

Cart::Cart(Store &store)
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

        cout<<"This is your order: ";
        for(int i=0; i<3; i++)
            cout<<"'"+order[i]+"' ";
        cout<<endl;




        //Category of the item hasnt been classified yet
        item2bBought = new Item(order[1], "TBD", H->stoi(order[0]), H->stod(order[2]));


        //////TESTING
        cout<<*item2bBought<<endl;

        //Searching for the category which this item belongs to
        for(int i=0; i<this->category.size(); i++)
        {
            cout<<"searching in "<<category[i]<<"...\n";
            unordered_map<string, Item> &currentCategory = allItems[category[i]];
            cout<<"CP1\n";


            if(currentCategory.find(item2bBought->getItemName()) == currentCategory.end())
                continue;
            else
            {
                cout<<"CP2\n";
                //Category of the item needs to be changed from "TBD" to category[i]
                item2bBought->changeCategory(category[i]);

                Item &item = currentCategory[item2bBought->getItemName()];

                cout<<item<<endl;

                if(item.getCurrentFreq() < H->stoi(order[0]))
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
                {
                    cout<<"IN THE BUCKET!!!!!!\n";
                    this->bucket.push(*item2bBought);
                }

                //Now this loop needs to end because we found the category and we have bought this item
                break;
            }
        }
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
