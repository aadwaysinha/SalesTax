#include "Store.h"

Store::Store(string storeName) : storeID(storeNumber)
{
    //storeNumber is a static variable, that is it belongs to the whole class, not to any single object
    //Using storeNumber to create storeIDs on the go
    storeNumber += 1;
    this->storeName = storeName;
    H = new Helper();
    CSVHandler loader(*this);       //Passing this store to the loader by reference
                                    //to fetch all the data of items from the store{id}.csv file
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

        H->toLower(category);

        if(category == "stop")
            break;

        string itemName;
        int price, freq;

        cin>>itemName>>price>>freq;

        H->toLower(itemName);


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

            currentCategory.insert({itemName, *newItem});
        }

        cout<<"Item has been created and will be saved once you stop entering more item\n";
    }
}



void Store::buyStuff()
{
    Cart *cart = new Cart(*this);
    while(1)
    {
        cart->addToCart();
        cout<<"You sure you done? (Y/N)\n";
        char choice;
        cin>>choice;
        tolower(choice);
        if(choice == 'n')
            break;
    }
    cart->generateBill();
    delete cart;
}



//Deallocates memory from heap
Store::~Store()
{
    delete this;
}
