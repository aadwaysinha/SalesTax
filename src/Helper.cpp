#include "Helper.h"

Helper::Helper()
{
    //ctor
}


//Rounds up any value to the nearest roundTo, by default roundTo is set to 0.05 as asked in the question
double Helper::customRoundTo(double val, double roundTo = 0.05)
{
    double roundToDivisor = 1/roundTo;
    double roundedTimesX = round(val * roundToDivisor);
    double rounded = roundedTimesX / roundToDivisor;
    return rounded;
}


//Converts all the characters in the string to lower case
void Helper::toLower(string &s)      //In place changes in the string
{
    for(int i=0; i<s.length(); i++)
        s[i] = tolower(s[i]);
}


Helper::~Helper()
{
    //dtor
}
