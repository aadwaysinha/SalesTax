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


//Buy items here
//Takes care of saving the states of items and store after all the transactions
void Store::buyStuff()
{

    //Creating a cart object
    Cart *cart = new Cart(*this);

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



void Store::updateFreq(string category, string itemName, int newFreq)
{
    this->items[category][itemName].updateCurrentFreq(newFreq);
}


//Deallocates memory from heap
Store::~Store()
{
    delete this;
}
