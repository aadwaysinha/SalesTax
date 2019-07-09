#include "Helper.h"

//Rounds up any value to the nearest roundTo, by default roundTo is set to 0.05 as asked in the question
double Helper::customRoundTo(double val, double roundTo)
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


//Converts string to integer, STOI does not work on code blocks because of some old bug
//from stackoverflow
int stoiUtil (const char *str)
{
    unsigned char abc;
    int ret = 0;
    for (abc = 1; abc & 1; str++)
    {
        abc  =  *str == '-' ? (abc & 6 ? abc & 6 : (abc & 23) | 20)
            : *str == '+' ?
                (abc & 6 ? abc & 6 : (abc & 7) | 4)
            : *str > 47 && *str < 58 ?
                abc | 10
            : !(abc & 2) && (*str == ' ' || *str == '\t') ?
                (abc & 23) | 1
            :
                abc & 22;
        if (abc & 8)
        {
            ret = ret * 10 + *str - 48;
        }
    }
    return abc & 16 ? -ret : ret;
}


int Helper::stoi(string &s)
{
    char *c = new char(s.length());
    for(int i=0; i<s.length(); i++)
        c[i] = s[i];
    return stoiUtil(c);
}


//Converts string to double, STOD does not work on code blocks because of some old bug
//from stackoverflow
double stodUtil (const char * str)
{
    unsigned char abc;
    double ret = 0, fac = 1;
    for (abc = 9; abc & 1; str++)
    {
        abc  =  *str == '-' ? (abc & 6 ? abc & 14 : (abc & 47) | 36)
            : *str == '+' ?
                (abc & 6 ? abc & 14 : (abc & 15) | 4)
            : *str > 47 && *str < 58 ?
                abc | 18
            : (abc & 8) && *str == '.' ?
                (abc & 39) | 2
            : !(abc & 2) && (*str == ' ' || *str == '\t') ?
                (abc & 47) | 1
            :
                abc & 46;
        if (abc & 16)
        {
            ret = abc & 8 ? *str - 48 + ret * 10 : (*str - 48) / (fac *= 10) + ret;
        }
    }
    return abc & 32 ? -ret : ret;
}


double Helper::stod(string &s)
{
    char *c = new char(s.length());
    for(int i=0; i<s.length(); i++)
        c[i] = s[i];
    return stodUtil(c);
}


string Helper::toString(int N)
{
    if(!N)
        return "0";
    string s;
    int tempN = N;
    while(N!=0)
    {
        int digit = N%10;
        s+=(digit+'0');
        N/=10;
    }
    reverse(s.begin(), s.end());
    return s;
}


string Helper::dtos(double D)
{
    if(D == 0)
        return "0";
    setprecision(std::numeric_limits<double>::max_digits10);
    ostringstream strs;
    strs << D;
    string str = strs.str();
    return str;
}
