#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

class Helper
{
    public:
        Helper();

        void toLower(string &s);

        double customRoundTo(double, double);

        string toString(int N);

        int stoi(string);

        double stod(string);

        ~Helper();

    protected:

    private:
};

#endif // HELPER_H
