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
inline int max(int a, int b){return a>b?a:b;}

class Solution
{
public:
    int longestConsecutive(const vector<int> &num)
    {
        unordered_map<int, bool> used;

        for(auto i:num) used[i] = false;

        int longest =0;

        for(auto i:num)
        {
            if(used[i]) continue;

            int length=1;

            used[i]=true;

            for(int j=i+1;used.find(j)!=used.end();++j)
            {
                used[j]=true;
                ++length;
            }

            for(int j=i-1;used.find(j)!=used.end();--j)
            {
                used[j]=true;
                ++length;
            }

            longest = max(longest, length);
        }

        return longest;
    }

    int longestConsecutive2(const vector<int> &num)
    {
        unordered_map<int, bool> used;
        int maxlen=0;

        for(int i : num) used[i]=true;

        for(int i:num)
        {
            if(!used[i]) continue;

            int len=1;

            for(int j=i+1; used.find(j)!=used.end();++j)
                {++len; used[j]=false;}

            for(int j=i-1;used.find(j)!=used.end();--j)
                {++len; used[j]=false;}

            maxlen = max(maxlen, len);
        }

        return maxlen;
    }

///////////////////// leetcode passed ///////////
    int longestConsecutive(vector<int>& nums) {
        if(nums.size()<2) return nums.size();

        unordered_map<int, bool> helper;
        int result=0;
        int maxresult=0;

        for(auto i:nums)
            helper[i]=true;

        for(auto j:helper){
            int val=j.first;
            result++;
            if(j.second){
                for( int i=val+1 ;helper.find(i)!=helper.end() && helper[i]; ++i){
                    result++;
                    helper[i]=false;
                }
                for(int i=val-1; helper.find(i)!=helper.end() && helper[i]; --i){
                    result++;
                    helper[i]=false;
                }
            }

            maxresult=max(maxresult, result);
            j.second=false;
            result=0;
        }

        return maxresult;
    }

};

int main()
{
    Solution a;
    const vector<int> b {1,299,54,2,645,4,6,3};
    int len_final = a.longestConsecutive2(b);
    cout<<"result = "<<len_final<<endl;

    for(int i=0;i<len_final;++i)
        cout<<b.at(i)<<",";
}
