#ifndef MARKET_H
#define MARKET_H
#include<iostream>
#include<sstream>
#include<fstream>
#include<map>
#include "CSVHandler.h"
#include "Helper.h"
using namespace std;

class Market
{
    private:
        map<int, string> storeList;
        Helper *H;

        friend class CSVHandler;

    public:
        void loadMarket();

        void displayMarket();

        string getStoreName(int);

        map<int, string> getStoreList();

};

#endif // MARKET_H
