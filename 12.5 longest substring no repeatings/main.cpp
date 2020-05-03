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
    int lengthOfLongestSubstring(string s){
        const int MAX_SIZE=26;
        int last[MAX_SIZE]={0};
        int max_len=0;
        int start=0;

        fill(last, last+MAX_SIZE, -1);

        for(int i=0; i<s.size();++i){
            if(last[s[i]-'a']>=start){
                max_len = max(max_len, i-start);
                start=last[s[i]-'a']+1;
            }
            last[s[i]-'a']=i;
        }

        return max(s.size()-start, max_len); // 别忘了最后一次，例如"abcd"
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.permute3(intset);

    for(auto i:b)
    {for(auto j: i)
            cout<<j<<" ";
     cout<<endl;
    }
}
