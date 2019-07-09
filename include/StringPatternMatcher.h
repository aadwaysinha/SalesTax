#ifndef STRINGPATTERNMATCHER_H
#define STRINGPATTERNMATCHER_H
#include<iostream>
#include<vector>
#include<string>
#include"Helper.h"
using namespace std;


class StringPatternMatcher
{
    private:
        string pattern;
        vector<int> PF;

        vector<int> PrefixFun(string);

        bool KMP(string, string);           //KMP string matching in O(N+M)
                                            //not particularly useful in the case of 'imported'
                                            //but just in case.


    public:
        StringPatternMatcher(string);

        bool patternExists(string);         //Tells if the pattern exists in the given string

        void changePattern(string);
};

#endif // STRINGPATTERNMATCHER_H
