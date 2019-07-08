#include "Cart.h"

//Constructor for Cart, initializes all the bills and the store through which this will be called
Cart::Cart(Store &store) : total(0.0), totalTax(0.0)
{
    this->store = &store;
    this->category = {"book", "medical", "food", "other"};
    H = new Helper();
}


//Returns a queue which contains all the items which were added to the cart
queue<Item>& Cart::getBucket()
{
    return this->bucket;
}


//Add to cart function is called when user chooses to buy items ftom the store
void Cart::addToCart()
{
    //print menu by cout<<Store
    /*

        Additional

    cout<<"\n\nTo stop, type 'quit' and press enter\n\n";

    cout<<"Make sure you order in this format: {Number of item} {item} at {price}\n\n"<<endl;
    cout<<"Example: \n1 imported bottle of perfume at 27.99 \n1 bottle of perfume at 18.99\n\n"<<endl;


    cout<<"Type 'quit' and press enter to stop buying\n\n(repeat if not a valid order)\n";

    */

    unordered_map<string, unordered_map<string, Item>> &allItems = this->store->getItems();

    while(1)
    {

        cin.clear();

        // cout<<"\n\n\nEnter details (or quit)\n";

        //order will store the tokenized form of data which is entered by user while ordering
        vector<string> order;

        Item *item2bBought;

        string s;

        //some booleans to take care of the flow of control
        bool toBeSkipped = false;
        bool itemFound = false;


        //DO-WHILE loop to enter the data UNLESS it has been inserted in the correct format
        do
        {

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


        //Category of the item hasnt been classified yet so it is set to TBD for now
        item2bBought = new Item(order[1], "TBD", H->stoi(order[0]), H->stod(order[2]));


        //Searching for the category which this item belongs to
        for(int i=0; i<this->category.size(); i++)
        {

            //fetching all the items of the current category by reference
            unordered_map<string, Item> &currentCategory = allItems[category[i]];


            if(currentCategory.find(item2bBought->getItemName()) == currentCategory.end())
                continue;
            else
            {
                //Found the category in which this item is kept in the store
                //Update all the taxes as tax is dependent on category
                //Category of the item needs to be changed from "TBD" to category[i]
                item2bBought->changeCategory(category[i]);
                item2bBought->updateSalesTax();
                item2bBought->updateSalesTax();
                itemFound = true;


                //The item with which out order item matches with
                //By reference because we might change the quantity after buying
                Item &item = currentCategory[item2bBought->getItemName()];


                /*

                        Additional feature

                //If number of items ordered is greater than present in the store
                //give the option to buy all or skip the item
                if(item.getCurrentFreq() < H->stoi(order[0]))
                {
                    cout<<"\nStore has got only "<<item.getCurrentFreq()<<" of these, do you want to buy them all or skip?\n";
                    string choice;
                    cout<<"\nType (skip/all) and press enter\n";
                    getline(cin, choice);

                    H->toLower(choice);

                    if(choice == "skip")
                    {
                        toBeSkipped = true;
                        break;
                    }

                    //Since the user has decided to buy all the items, add them to cart
                    //and make the quantity of this item at the store zero
                    item2bBought->updateCurrentFreq(item.getCurrentFreq());
                    this->store->updateFreq(category[i], order[1], 0);
                }
                else
                {

                    */

                    //If the item is present in ample amount then we can add it to our cart,
                    //while doing this, we also need to reduce the freq of them being bought
                    //from the store

                    int oldFreq = allItems[category[i]][order[1]].getCurrentFreq();
                    this->store->updateFreq(category[i], order[1], oldFreq - item2bBought->getCurrentFreq());

                    /*
                }

                */

                //Now this loop needs to end because we found the category and we have bought this item
                break;
            }
        }

        bool itemAdded = false;
        if(itemFound && !toBeSkipped && item2bBought->getCurrentFreq() > 0)
        {
            itemAdded = true;
            this->bucket.push(*item2bBought);
        }

        /*

            Additional detail

        if(itemFound)
        {
            if(itemAdded)
                cout<<"Your item was added to the cart\n";
            else
                cout<<"Your item has been skipped\n";
        }
        else
            cout<<"Sorry, item not found";

        */
    }
}


//generate bill empties to bucket by popping each item one by one
//and adding it to the final bill of the cart
void Cart::generateBill()
{

    // cout<<"=-=-=-=-=-=-=-BILL-=-=-=-=-=-=-=\n\n";

    cout<<endl;
    queue<Item> &buck = this->bucket;


    while(!buck.empty())
    {
        Item frontItem = buck.front();
        double total4this = (frontItem.getCurrentFreq()*frontItem.getPrice());
        double totalTax4this = (frontItem.getSalesTax() + frontItem.getImportTax());
        totalTax4this *= frontItem.getCurrentFreq();
        cout<<frontItem.getCurrentFreq()<<" "<<frontItem.getItemName()<<": "<<total4this+totalTax4this<<endl;

        //updating tax and total(ie. sum of original price) for cart
        this->total += total4this;
        this->totalTax += totalTax4this;

        buck.pop();
    }
    cout<<"Sales Taxes: "<<this->totalTax<<endl;
    cout<<"Total: "<<this->total + this->totalTax<<endl<<endl<<endl;
}

//deallocates memory as soon as the scope gets over
Cart::~Cart()
{
    delete this;
}
