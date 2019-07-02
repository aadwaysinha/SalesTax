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

    //Item::Item(string itemName, string category, int frequency, double price)
    Item *I = new Item("Harry imported Potter", "Books", 9, 47.50);
    cout<<*I;
    cout<<"ST: "<<I->getSalesTax()<<endl;
    cout<<"IT: "<<I->getImportTax()<<endl;

    int x;
    cin>>x;
    cout<<x;
}
