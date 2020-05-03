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


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int f=0, result=-9999;
        for(int i=0; i<nums.size();++i){
            f=max(f+nums[i],nums[i]);
            result=max(result,f);
        }

        return result;
    }
/////////////////////////////////
    int maxSubArray(vector<int>& nums) {
        int maxsub=INT_MIN;
        vector<int> dp(nums.size(), 0);

        for(int i=nums.size()-1; i>=0; --i){
            if( i==nums.size()-1 || dp[i+1]<0){
                dp[i]=nums[i];
            }else{
                dp[i]=dp[i+1]+nums[i];
            }
            maxsub=max(maxsub, dp[i]);
        }

        return maxsub;
    }
    //////////// leetcode passed  /////////////
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        int maxlen=nums[0];
        vector<int> dp=nums;

        for(int i=1; i<n; ++i){
            dp[i]= dp[i-1]>0 ? dp[i-1]+dp[i] : dp[i];
            maxlen=max(maxlen, dp[i]);
        }
        return maxlen;
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
