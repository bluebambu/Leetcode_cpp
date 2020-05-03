#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
/////////////////////  Leetcode passed ///////////////////////
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return string();
        if(strs.size()==1) return strs[0];

        int j=0;
        for(; j<strs[0].size(); ++j){
            for(int i=1; i<strs.size(); ++i){
                if(j>=strs[i].size() || strs[i][j]!=strs[0][j])
                    return strs[0].substr(0,j);
            }
        }
        return strs[0];
    }


    string longestCommonPrefix2(vector<string>& strs) {
        if (strs.size()==0) return "";
        int len=strs[0].size();
        int i,j;

        int p=strs[1].size();
        strs[0][p]=strs[1][p];

        for (i=1; i<strs.size();i++){
            for (j=0; j<len;j++){
                if (strs[i-1][j]!=strs[i][j]){
                // 我觉得会溢出，但是实测得到，
                // strs[2][p] = \0;
                    if (j<len)
                        len=j;
                    break;
                }
            }
        }

        cout<<int(strs[1][p]);

        return strs[0].substr(0,len);
    }
};


int main()
{
    Solution a;

    vector<string> intset {"aldskfjlajsdflkjs", "aldskf"};

    auto b = a.longestCommonPrefix2(intset);

    cout<<b;

}
