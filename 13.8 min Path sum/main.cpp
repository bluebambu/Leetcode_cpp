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
    /////////// Leetcode passed /////////////////
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        vector<vector<int>> dp=grid;

        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                // dp[i][j] = grid[i][j] + min( dp[i-1][j], dp[i][j-1] )
                int x = i-1>=0? dp[i-1][j] : INT_MAX;
                int y = j-1>=0? dp[i][j-1] : INT_MAX;
                if(x==INT_MAX && y==INT_MAX) continue;
                // this assumption is specifically for dp[0][0] !! Necessary!
                dp[i][j] += min(x, y);
            }
        }
        return dp[m-1][n-1];
    }

};

int main()
{
    Solution a;

}
