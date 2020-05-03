#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    vector<string> anagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> group;

        for(auto s : strs)
        {
            string key = s;
            sort(key.begin(), key.end());

            group[key].push_back(s);
        }

        vector<string> result;
        for(auto i : group)
        {
            if(i->second.size()>1)
            {
                result.insert(result.end, it->second.begin(), it->second.end());
            }
        }

        return result;
    }
//////////////////////////// Leetcode Passed/////////////
// 要求字母升序
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> helper;

        for(auto& i:strs){
            auto j=i;
            sort(j.begin(), j.end());
            helper[j].push_back(i);
        }

        for(auto& i:helper){
            sort(i.second.begin(), i.second.end());
            result.push_back(i.second);
        }

        return result;
    }
};

int main()
{
    Solution a;
    string b("");

    auto c=a.isPalindrome(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
