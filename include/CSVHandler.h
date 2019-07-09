#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <stdlib.h>
#include<unordered_map>
#include "Store.h"
#include "Helper.h"
#include "Item.h"
#include "Market.h"
using namespace std;

class Store;
class Market;

class CSVHandler
{
    private:
        Helper *H;

    public:

        //loads all the items of a store
        void loadData(Store &store);

        //overriding lodaData for loading market metadata
        void loadData(Market &market);

        //writes data to store files
        void writeData(Store &store);

};

#endif // CSVHANDLER_H
