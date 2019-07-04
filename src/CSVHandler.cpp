#include "CSVHandler.h"

void CSVHandler::loadData(Store &store)
{
    //Getting items from the store by reference, in this the data will be loaded from the csv
    unordered_map<string, unordered_map<string, Item>> &items = store.getItems();

    H = new Helper();

    //Generating name of the csv file which should be opened
    string storeID = H->toString(store.getStoreID());
    string fileName = "store" + storeID + ".csv";

    //Opening the csv file
    ifstream reader(fileName);

    if(reader.is_open())
    {
        string itemName, category, freq, price;

        while(reader.good())
        {
            getline(reader, itemName, ',');
            getline(reader, category, ',');
            getline(reader, freq, ',');
            getline(reader, price, '\n');

            if(!itemName.length())
                break;

            Item *it = new Item(itemName, category, H->stoi(freq), H->stod(price));

            //If category does not exist, initialize it with an empty map of {itemName, item}
            string currentCategory = it->getItemCategory();
            string currentName = it->getItemName();

            H->toLower(currentCategory);
            H->toLower(currentName);

            if(items.find(currentCategory) == items.end())
            {
                //category does not exist in the store yet, so add the category first
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

    return;
}


void CSVHandler::writeData(Store &store)
{
    unordered_map<string, unordered_map<string, Item>> items = store.getItems();

    //Generating name of the csv file which should be opened
    string storeID = H->toString(store.getStoreID());
    string fileName = "store" + storeID + ".csv";

    //Opening the csv file
    ofstream writer(fileName, ios::out);

    string name, category, freq, price;

    for(auto itr = items.begin(); itr!=items.end(); itr++)
    {
        category = itr->first;
        for(auto itr2 = items[itr->first].begin() ; itr2 != items[itr->first].end(); itr2++)
        {
            name = itr2->second.getItemName();
            category = itr2->second.getItemCategory();
            freq = H->toString(itr2->second.getCurrentFreq());
            price = H->dtos(itr2->second.getPrice());
            writer << name << ",";
            writer << category << ",";
            writer << freq << ",";
            writer << price << "\n";
        }
    }
    writer.close();
}



void CSVHandler::loadData(Market &market)
{
    H = new Helper();

    ifstream reader("market.csv");

    if(reader.is_open())
    {
        string storeID, storeName;

        while(reader.good())
        {
            getline(reader, storeID, ',');
            getline(reader, storeName, '\n');

            if(storeName.empty())
                break;

            if(H->stoi(storeID))
                market.storeList.insert({H->stoi(storeID), storeName});
        }

        reader.close();
    }
}


//Updates market list whenever a new store is added
void CSVHandler::writeData(Market &market)
{
    H = new Helper();
    map<int, string> storeL = market.getStoreList();

    //Opening the csv file
    ofstream writer("market.csv", ios::out);

    string storeID, storeName;

    for(auto itr = storeL.begin(); itr!=storeL.end(); itr++)
    {
        storeID = H->toString(itr->first);
        storeName = itr->second;
        writer << storeID << ",";
        writer << storeName << "\n";
    }

    writer.close();
}
