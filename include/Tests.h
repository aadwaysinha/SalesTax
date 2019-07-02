#ifndef TESTS_H
#define TESTS_H
#include "Item.h"
#include "StringPatternMatcher.h"
#include<iostream>
#include<assert.h>
using namespace std;

class Tests
{

    private:
        Item *item;
        StringPatternMatcher *spm;

        void testForItem();
        void testForStringPatternMatcher();

    public:
        Tests();

        void runAllTests();

        ~Tests();

    protected:

};

#endif // TESTS_H
