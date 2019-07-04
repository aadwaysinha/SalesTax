#ifndef MARKET_H
#define MARKET_H
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include "CSVHandler.h"
#include "Helper.h"
using namespace std;


//Market stores the list of all the stores
//It is used to maintain the states of the store
class Market
{
    private:
        map<int, string> storeList;     //A list of all the stores
        Helper *H;      

        friend class CSVHandler;

    public:
        void loadMarket();

        void writeData();

        void displayMarket();

        string getStoreName(int);

        void updateStoreList(int, string);

        map<int, string> getStoreList();

};

#endif // MARKET_H
