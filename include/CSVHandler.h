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
using namespace std;

class Store;

class CSVHandler
{
    private:
        Helper *H;

    public:

        void loadData(Store &store);

        void writeData(Store &store);

};

#endif // CSVHANDLER_H
