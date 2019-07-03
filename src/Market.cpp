#include "Market.h"

void Market::loadMarket()
{
    CSVHandler *loader = new CSVHandler();

    loader->loadData(*this);
}


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
