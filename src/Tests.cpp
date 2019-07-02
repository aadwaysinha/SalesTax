#include "Tests.h"


Tests::Tests()
{
    //Item::Item(string itemName, string category, int frequency, double price)
    this->item = new Item("testItem", "testCategory,", 12, 34.55);
    this->spm = new StringPatternMatcher("pattern");
}








//All the tests for Item class are over here
void Tests::testForItem()
{
    assert(this->item->getItemName().length() != 0);
    assert(this->item->getItemCategory().length() != 0);
    assert(this->item->getPrice() >= 0);

    if(this->item->getPrice() > 0)
    {
        //There should be some check on sales tax as it MIGHT just be zero sometimes
        //Example: if price of item is 0.2,  0.2*10/100 -> 0.02 ---rounding off to nearest 0.05---> we get 0.
        assert(1);

        //check tax for imported goods here. Again, MIGHT just be zero sometimes.
        assert(1);
    }
}







//All the tests for StringPatternMatcher class are over here
void Tests::testForStringPatternMatcher()
{
    //Should return true
    assert(this->spm->patternExists("pattern exists here"));

    //Should return false
    assert(!this->spm->patternExists("patterDoesnt exists here"));
}








void Tests::runAllTests()
{
    this->testForItem();
    this->testForStringPatternMatcher();
}


//Deallocate memory from heap
Tests::~Tests()
{
    delete item;
    delete spm;
    delete this;
}
