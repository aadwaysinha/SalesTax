#include<iostream>
#include "StringPatternMatcher.h"
#include "Tests.h"
#include "Item.h"
using namespace std;

int main()
{

    Tests *test = new Tests();
    test->runAllTests();
    cout<<"All tests ran successfully and no bug was found.\n";


    

}
