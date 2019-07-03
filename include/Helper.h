#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;

class Helper
{
    public:

        void toLower(string &s);

        double customRoundTo(double, double);

        string toString(int N);

        int stoi(string &s);

        double stod(string &s);

        string dtos(double D);

    protected:

    private:
};

#endif // HELPER_H
