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


void Store::addItems()
{
    cout<<"Time to add some new items in the store!"<<endl<<endl;
    cout<<"To stop, enter 'Stop' and press enter\n";
    while(1)
    {
        cin.seekg(0,ios::end);
        cin.clear();
        string category;
        cout<<"Enter category: ";
        getline(cin, category);

        H->toLower(category);

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
            cout<<"ALREADY PRESENT!!\n";
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
        if(c == 'y')
            break;
    }

    CSVHandler *writer = new CSVHandler();
    writer->writeData(*this);
}



void Store::buyStuff()
{
    cout<<"-=-=-=-=-=-=- M E N U -=-=-=-=-=-=-\n\n";

    this->printAllItems();

    Cart *cart = new Cart(*this);
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
    cart->generateBill();

    //NOT saving these transactions intentionally 
}


string Store::getStoreName()
{
    return this->storeName;
}


int Store::getStoreID()
{
    return this->storeID;
}


void Store::printAllItems()
{
    for(auto itr = this->items.begin(); itr!=this->items.end(); itr++)
    {
        cout<<"Category: "<<itr->first<<endl;
        for(auto itr2 = this->items[itr->first].begin() ; itr2 != this->items[itr->first].end(); itr2++)
            cout<<itr2->second<<endl;
        cout<<endl;
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
