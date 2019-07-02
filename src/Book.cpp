#include "Book.h"

Book::Book(int ID, string name) : bookID(ID), bookName(name) {}


void Book::printBook()
{
    cout<<"ID: "<<this->bookID<<endl;
    cout<<"Name: "<<this->bookName<<endl;
}
