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

    double currentPrice = this->item->getPrice();

    //There should be some check on sales tax as it MIGHT just be zero sometimes
    //Example: if price of item is 0.2,  0.2*10/100 -> 0.02 ---rounding off to nearest 0.05---> we get 0.
    if(currentPrice >= 0.25)
        assert(item->getSalesTax() > 0);


    Item *zeroSalesTaxItem = new Item("testItem2", "testCategory,", 12, 0.24);
    Item *zeroImportTaxItem = new Item("testItem3 imported", "testCategory,", 12, 0.49);
    Item *nonZeroImportTaxItem = new Item("testItem3 imported", "testCategory,", 12, 0.5);

}


//All the tests for StringPatternMatcher class are over here
void Tests::testForStringPatternMatcher()
{
    //Should return true
    assert(this->spm->patternExists("pattern exists here"));

    //Should return false
    assert(!this->spm->patternExists("patterDoesnt exists here"));
}


//Tests for store and cart
void Tests::testStoreAndCart()
{
    Store *s = new Store("testStore", 1);
    Cart *cart = new Cart(*s);

    queue<Item> buc = cart->getBucket();

    assert(buc.size() == 0);
}


//Test on tax calculation
void Tests::testTax()
{
    Item *i1 = new Item("book", "book", 34, 12.49);
    Item *i2 = new Item("music CD", "other", 34, 14.99);
    Item *i3 = new Item("chocolate bar", "food", 34, 0.85);

    Item *i4 = new Item("imported box of chocolates", "food", 34, 10.00);
    Item *i5 = new Item("imported bottle of perfume", "other", 34, 47.50);

    Item *i6 = new Item("imported bottle of perfume", "other", 34, 27.99);
    Item *i7 = new Item("bottle of perfume", "other", 34, 18.99);
    Item *i8 = new Item("packet of headache pills", "medical", 34, 9.75);
    Item *i9 = new Item("box of imported chocolates", "food", 34, 11.25);


    Helper *H = new Helper();

    //first order
    double taxOnItem1 = i1->getImportTax() + i1->getSalesTax();
    double taxOnItem2 = i2->getImportTax() + i2->getSalesTax();
    double taxOnItem3 = i3->getImportTax() + i3->getSalesTax();

    double tots1 = taxOnItem1 + taxOnItem2 + taxOnItem3 + i1->getPrice() + i2->getPrice() + i3->getPrice();
    double expected1 = 29.83;

    assert(taxOnItem1 + taxOnItem2 + taxOnItem3 - 1.50 == 0);
    assert((int)tots1*100 == (int)expected1*100);



    //second order
    double taxOnItem4 = i4->getImportTax() + i4->getSalesTax();
    double taxOnItem5 = i5->getImportTax() + i5->getSalesTax();

    double tots2 = taxOnItem4 + taxOnItem5 + i4->getPrice() + i5->getPrice();
    double expected2 = 65.15;

    assert(taxOnItem4 + taxOnItem5 - 7.65 == 0);
    assert((int)tots2*100 == (int)expected2*100);




    //third order
    double taxOnItem6 = i6->getImportTax() + i6->getSalesTax();
    double taxOnItem7 = i7->getImportTax() + i7->getSalesTax();
    double taxOnItem8 = i8->getImportTax() + i8->getSalesTax();
    double taxOnItem9 = i9->getImportTax() + i9->getSalesTax();


    double tots3 = taxOnItem6 + taxOnItem7 + taxOnItem8 + taxOnItem9 + i6->getPrice() + i7->getPrice() + i8->getPrice() + i9->getPrice();
    double expected3 = 74.68;
    double taxForLast = taxOnItem6 + taxOnItem7 + taxOnItem8 + taxOnItem9;

    assert((int)(taxForLast)*100 - (int)(6.70)*100 == 0);


    assert((int)tots3*100 == (int)expected3*100);


    //delete all the items
    delete i1;
    delete i2;
    delete i3;
    delete i4;
    delete i5;
    delete i6;
    delete i7;
    delete i8;
    delete i9;
}

void Tests::runAllTests()
{
    this->testForItem();
    this->testForStringPatternMatcher();
    this->testStoreAndCart();
    this->testTax();
}


//Deallocate memory from heap
Tests::~Tests()
{
    delete item;
    delete spm;
    delete this;
}
