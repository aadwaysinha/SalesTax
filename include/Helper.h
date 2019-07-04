#ifndef HELPER_H
#define HELPER_H
#include<iostream>
#include<cmath>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;


//Helper has misc functions which are being used throughout the project at various places
class Helper
{
    public:

        void toLower(string &s);                    //STRING -> string

        double customRoundTo(double, double);       //round any value to its nearest X

        string toString(int N);                     //integer to string

        int stoi(string &s);                        //string to integer

        double stod(string &s);                     //string to double

        string dtos(double D);                      //double to string

};

#endif // HELPER_H
