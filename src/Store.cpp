#include "Store.h"

Store::Store(string storeName) : storeID(storeNumber)
{
    //storeNumber is a static variable, that is it belongs to the whole class, not to any single object
    //Using storeNumber to create storeIDs on the go
    storeNumber += 1;
    this->storeName = storeName;

    CSVHandler loader(*this);       //Passing this store to the loader by reference 
                                    //to fetch all the data of items from the store{id}.csv file
}


void Store::toLower(string &s)      //In place changes in the string
{
    for(int i=0; i<s.length(); i++)
        s[i] = tolower(s[i]);
}


void Store::addItems()
{
    cout<<"Time to add some new items in the store!"<<endl<<endl;
    cout<<"To stop, enter 'Stop' and press enter";
    while(1)
    {
        string category;
        cout<<"Enter category"<<endl;
        cin>>category;

        toLower(category);

        if(category == "stop")
            break;

        string itemName;
        int price, freq;

        cin>>itemName>>price>>freq;

        toLower(itemName);

        if(this->items[category].find(itemName) == this->items[category].end())
        {
            Item *currentItem = new Item(itemName, category, freq, price);
            this->items[category].insert({itemName, currentItem});
        }
        
    }
}

//Deallocates memory from heap
Store::~Store()
{
    delete this;
}
