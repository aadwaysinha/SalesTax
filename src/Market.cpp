#include "Market.h"

//Loads store list from market.csv
void Market::loadMarket()
{
    CSVHandler *loader = new CSVHandler();

    loader->loadData(*this);
}


//displays all the stores
void Market::displayMarket()
{
    cout<<"STORE ID"<<"\t"<<"STORE NAME\n";
    map<int, string> &SL = this->storeList;
    for(auto itr = SL.begin(); itr!=SL.end(); itr++)
        cout<<itr->first<<"\t\t"<<itr->second<<endl;
}



string Market::getStoreName(int storeID)
{
    return this->storeList[storeID];
}


map<int, string> Market::getStoreList()
{
    return this->storeList;
}


//used whenever a new store is added in the list
void Market::updateStoreList(int storeID, string storeName)
{
    this->storeList.insert({storeID, storeName});
}
