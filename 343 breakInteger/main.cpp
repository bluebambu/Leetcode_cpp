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
    ////////////  leetcode passed, analyse cases  n=7 ~ 10  /////////////
    int integerBreak(int n) {
        int dp[n+1]={0};

        dp[2]=1;
        dp[3]=2;

        for(int i=4; i<=n; ++i){
            dp[i]=1;
            int t=i/3;
            int s=i%3;

            if(s==0){
                while(t--) dp[i]*=3;
            }else if(s==1){
                while(--t) dp[i]*=3;
                dp[i]*=4;
            }else{
                while(t--) dp[i]*=3;
                dp[i]*=s;
            }
        }

        return dp[n];
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
