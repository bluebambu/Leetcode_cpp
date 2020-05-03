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
///////////////// leetcode TLE, DP, similar to LIS  //////////
    int jump(vector<int>& nums) {
        if(nums.empty()) return 0;

        vector<int> dp(nums.size(), 0);
        dp[0]=0;

        for(int i=1; i<dp.size(); ++i){
            int minval=INT_MAX;
            for(int j=0; j<i; ++j){
                if(j==0 && nums[0]>=i)  // case j==0 is very special, take care
                    minval = min(minval, dp[j]);
                else if(dp[j] && nums[j]+j >= i)
                    minval = min(minval, dp[j]); // can not +1 here

            }
            dp[i] = minval==INT_MAX? 0 : minval+1;  // +1 here
        }

        return  dp[nums.size()-1];
    }

    ////////////// leetcode passed, BFS ///////////////////
    /**
    I try to change this problem to a BFS problem, where nodes in level i are all the nodes
     that can be reached in i-1th jump. for example. 2 3 1 1 4 , is 2|| 3 1|| 1 4 ||

    clearly, the minimum jump of 4 is 2 since 4 is in level 3. my ac code.
    **/

    int jump(vector<int>& nums) {
        if(nums.size() < 2) return 0;
        int level=0;
        int curmax=0, i=0, nextmax=0;

        while(curmax>=i){
            ++level;
            for(;i<=curmax; ++i){
                nextmax=max(nextmax, nums[i]+i);

                if(nextmax>=nums.size()-1) return level;
            }
            curmax=nextmax;
        }
        return 0;
    }

};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    a.flatten(tree);


}
