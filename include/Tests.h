#ifndef TESTS_H
#define TESTS_H
#include "Item.h"
#include "StringPatternMatcher.h"
#include "Cart.h"
#include "CSVHandler.h"
#include "Store.h"
#include<iostream>
#include<assert.h>
using namespace std;


//Testing all features here
class Tests
{

    private:
        Item *item;
        StringPatternMatcher *spm;

        void testForItem();
        void testForStringPatternMatcher();
        void testStoreAndCart();
        void testTax();


    public:
        Tests();

        void runAllTests();

        ~Tests();

    protected:

};

#endif // TESTS_H
