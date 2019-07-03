#ifndef CSVHANDLER_H
#define CSVHANDLER_H
#include<iostream>
#include<fstream>
#include "Store.h"
using namespace std;

class CSVHandler
{
    private:
        fstream readIt;
        fstream writeIt;

    public:
        CSVHandler(Store &store);

        virtual ~CSVHandler();

    protected:

};

#endif // CSVHANDLER_H
