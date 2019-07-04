#include "StringPatternMatcher.h"

//computes the Longest prefix which is also a suffix for all indices
vector<int> StringPatternMatcher::PrefixFun(string pattern)
{
    int patternSize = pattern.size();
    vector<int> prefSufTable(patternSize);
    int k = 0;
    for (int i = 1; i < patternSize; i++)
    {
        while (k > 0 && pattern[k] != pattern[i])
            k = prefSufTable[k-1];
        if (pattern[k] == pattern[i])
            k = k+1;
        prefSufTable[i] = k;
    }
    return prefSufTable;
}

//KMP(Knuth-Morris-Pratt) algorithm for string searching in O(N+M)
bool StringPatternMatcher::KMP(string fullString, string pattern)
{
    int fullStringSize = fullString.size();
    int patternSize = pattern.size();
    if (patternSize == 0) return 0;
    int i = 0, j = 0;
    while (i < fullStringSize)
    {
        if (fullString[i] == pattern[j])
        {
            if (j == patternSize-1)
                return true;
            j++; i++;
        }
        else if(j == 0)
            i++;
        else
            j = this->PF[j-1];
    }
    return false;
}


StringPatternMatcher::StringPatternMatcher(string pattern)
{
    //Converting string to lowercase to match without case sensitivity
    for(int i=0; i<pattern.size(); i++)
        pattern[i] = tolower(pattern[i]);

    this->pattern = pattern;
    this->PF = PrefixFun(pattern);
}


bool StringPatternMatcher::patternExists(string fullString)
{
    return KMP(fullString, this->pattern);
}


void StringPatternMatcher::changePattern(string newPattern)
{
    this->PF = PrefixFun(newPattern);
}
