#include "Store.h"

Store::Store(string storeName, int storeID)
{
    //storeNumber is a static variable, that is it belongs to the whole class, not to any single object
    //Using storeNumber to create storeIDs on the go
    this->storeID = storeID;
    this->storeName = storeName;
    H = new Helper();
    CSVHandler *loader = new CSVHandler();
    loader->loadData(*this);                      //Passing this store to the loader by reference
                                                  //to fetch all the data of items from the store{id}.csv file
}


unordered_map<string, unordered_map<string, Item>>& Store::getItems()
{
    return this->items;
}


//Adds items to any stores and saves its state in the csv files
void Store::addItems()
{
    cout<<"Time to add some new items in the store!"<<endl<<endl;
    cout<<"To stop, enter 'Stop' and press enter\n";
    while(1)
    {
        cin.seekg(0,ios::end);
        cin.clear();
        string category;
        cout<<"Enter category: (or stop) ";
        getline(cin, category);

        H->toLower(category);

        if(category == "stop")
            break;

        cout<<"\nItemName: ";
        string itemName;

        double price;
        int freq;

        getline(cin, itemName);
        H->toLower(itemName);


        cout<<"\nFreq: ";
        cin>>freq;
        cout<<"\nPrice: ";
        cin>>price;
        cout<<endl;


        if(this->items.find(category) == this->items.end())
        {
            //category doesn't exist in the store yet, so add the category first
            //and then add the item to it
            this->items[category] = {};     //an empty shelf for new category
        }

        //By now, the category must exist in the store
        unordered_map<string, Item> &currentCategory = this->items[category];

        if(currentCategory.find(itemName) != currentCategory.end())
        {
            //If similar item already exists in the store, then increase its frequency by
            //adding current item's freq to it
            int oldFreq = currentCategory[itemName].getCurrentFreq();
            currentCategory[itemName].updateCurrentFreq(oldFreq + freq);
        }
        else
        {
            //If similar item does not exist in the store, add the current item to the store
            Item *newItem = new Item(itemName, category, freq, price);

            unordered_map<string, Item> &current = this->items[category];

            current[itemName] = *newItem;
        }

        cout<<"Item has been created and will be saved once you stop entering more item\n";
        cout<<"Wish to continue? (y/n)\n";
        char c;
        cin>>c;
        c = tolower(c);
        if(c == 'n')
            break;
    }

    CSVHandler *writer = new CSVHandler();
    writer->writeData(*this);

    //Once the data has been entered we need to close the file
    //and load it once more to avoid data inconsistency
    CSVHandler *loader = new CSVHandler();
    loader->loadData(*this);
}


//Buy items here
//Takes care of saving the states of items and store after all the transactions
void Store::buyStuff()
{
    
    
    /*
    
        Additional feature

    cout<<"-=-=-=-=-=-=-=-=-=-=- M E N U -=-=-=-=-=-=-=-=-=-=-\n\n";


    if(this->items.empty())
    {
        cout<<"Ah, this store is empty right now\n\n";
        cout<<"-=-=-=-=-=-=-=-=-=-=- M E N U -=-=-=-=-=-=-=-=-=-=-\n\n";
        return;
    }

    this->printAllItems();

    cout<<"-=-=-=-=-=-=-=-=-=-=- M E N U -=-=-=-=-=-=-=-=-=-=-\n\n";

    */


    //Creating a cart object
    Cart *cart = new Cart(*this);
    
    
    /*

        Additional feature

    while(1)
    {
        cart->addToCart();
        cout<<"You sure you done? (Y/N)\n";
        string choice;
        cin>>choice;
        H->toLower(choice);
        if(choice == "y")
            break;
    }

    */

    //Calling addToCart which allows to buy stuff
    cart->addToCart();

    //Generating bill
    cart->generateBill();

    //Updating the store because of recent transactions
    CSVHandler *writer = new CSVHandler();
    writer->writeData(*this);
}


string Store::getStoreName()
{
    return this->storeName;
}


int Store::getStoreID()
{
    return this->storeID;
}



//Pretty prints all the items
void Store::printAllItems()
{
    //TO print all the items in a kinda OKAY looking format, we'll need some padding
    int namePadding = 0;
    int pricePadding = 0;
    for(auto itr = this->items.begin(); itr!=this->items.end(); itr++)
    {
        for(auto itr2 = this->items[itr->first].begin() ; itr2 != this->items[itr->first].end(); itr2++)
        {
            namePadding = max(namePadding, (int)itr2->second.getItemName().length());
            pricePadding = max(pricePadding, (int)(H->toString(itr2->second.getPrice()).length()));
        }
    }

    namePadding += 4;
    pricePadding += 4;

    //Padding for header-> ITEM______PRICE______QUANTITY
    string itemHeaderPad(namePadding - 4, ' ');
    string priceHeaderPad(pricePadding - 5, ' ');

    cout<<"ITEM"<<itemHeaderPad<<"PRICE"<<priceHeaderPad<<"QUANTITY\n\n";

    for(auto itr = this->items.begin(); itr!=this->items.end(); itr++)
    {
        for(auto itr2 = this->items[itr->first].begin() ; itr2 != this->items[itr->first].end(); itr2++)
        {
            string name = itr2->second.getItemName();
            string namePad(namePadding - name.length(), ' ');
            string price = H->dtos(itr2->second.getPrice());
            string pricePad(pricePadding - price.length(), ' ');
            int freq = itr2->second.getCurrentFreq();
            cout<<name<<namePad<<price<<pricePad<<freq<<endl;
        }
    }


}


void Store::updateFreq(string category, string itemName, int newFreq)
{
    this->items[category][itemName].updateCurrentFreq(newFreq);
}


//Deallocates memory from heap
Store::~Store()
{
    delete this;
}
