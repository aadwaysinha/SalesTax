#ifndef BOOK_H
#define BOOK_H
#include<iostream>
using namespace std;


class Book
{
    public:
        const int bookID;
        string bookName;
        Book(int ID, string name);
        void printBook();
    protected:

    private:
};

#endif // BOOK_H
