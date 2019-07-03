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
        fstream readIt;
        fstream writeIt;
        Helper *H;

    public:
        CSVHandler(Store &s);   //Constructor for loader

        CSVHandler(Store &s, vector<Item>);   //Constructor for writer

        virtual ~CSVHandler();

    protected:

};

#endif // CSVHANDLER_H
