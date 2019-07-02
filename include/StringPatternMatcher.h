#ifndef STRINGPATTERNMATCHER_H
#define STRINGPATTERNMATCHER_H
#include<iostream>
#include<vector>
#include<string>
using namespace std;


class StringPatternMatcher
{
    private:
        string pattern;
        vector<int> PF;

        vector<int> PrefixFun(string);

        bool KMP(string, string);


    public:
        StringPatternMatcher(string);

        bool patternExists(string);

        void changePattern(string);
};

#endif // STRINGPATTERNMATCHER_H
