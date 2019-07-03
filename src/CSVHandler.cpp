#include "CSVHandler.h"

CSVHandler::CSVHandler(Store &store)
{

    //Getting items from the store by reference, in this the data will be loaded from the csv
    unordered_map<string, unordered_map<string, Item>> items = store.getItems();

    H = new Helper();

    //Generating name of the csv file which should be opened
    string storeID = H->toString(store.getStoreID());
    string fileName = "store" + storeID + ".csv";

    //Opening the csv file
    ifstream reader(fileName);

    if(reader.is_open())
    {
        cout<<"found file\n";
        string itemName, category, freq, price;

        while(reader.good())
        {
            getline(reader, itemName, ',');
            getline(reader, category, ',');
            getline(reader, price, ',');
            getline(reader, freq, '\n');

            if(!itemName.length())
                break;

            Item *it = new Item(itemName, category, H->stoi(freq), H->stod(price));

            //If category doesnt exist, init it with an empty map of {itemName, item}
            string currentCategory = it->getItemCategory();
            string currentName = it->getItemName();

            H->toLower(currentCategory);
            H->toLower(currentName);

            if(items.find(currentCategory) == items.end())
            {
                //category doesn't exist in the store yet, so add the category first
                //and then add the item to it
                items[category] = {};     //an empty shelf for new category
            }

            unordered_map<string, Item> &nextMap = items[currentCategory];

            if(nextMap.find(currentName) != nextMap.end())
            {
                //If similar item already exists in the store, then increase its frequency by
                //adding current item's freq to it
                int oldFreq = nextMap[currentName].getCurrentFreq();
                nextMap[currentName].updateCurrentFreq(oldFreq + it->getCurrentFreq());
            }
            else
            {
                //If similar item does not exist in the store, add the current item to the store
                unordered_map<string, Item> &nextNextMap = items[currentCategory];
                nextNextMap[currentName] = *it;
            }
        }
        
        reader.close();
    }
}


CSVHandler::CSVHandler(Store &store, vector<Item> newItems)
{

}


CSVHandler::~CSVHandler()
{
    //dtor
}
