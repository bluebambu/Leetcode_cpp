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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};


class Solution
{
public:
//////// Leetcode passed ////////////
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return 0;
        int m=obstacleGrid.back().size();
        int n=obstacleGrid.size();

        int dp[m]={1};

        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                if(obstacleGrid[i][j]==1)
                    dp[j]=0;
                else if(j>0)
                    dp[j]+=dp[j-1];
            }
        }

        return dp[m-1];
    }

////////////////////////////////////////////////
    int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.back().size();
        int n=obstacleGrid.size();

        vector<int> dp(m, 0);
        dp[0] = obstacleGrid[0][0] ? 0 : 1;
        // 这一句是必需的 ！

        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j){
                dp[j] = obstacleGrid[i][j] ? 0 : (j>0 ? (dp[j]+dp[j-1]) : dp[j]);
            }
        }

        return dp[m-1];

    }

};


class Solution2 {
public:
    //// TLE ...

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int result=0;
        dfs(obstacleGrid, 0, 0, result);
        return result;
    }

    void dfs(vector<vector<int>>& obstacleGrid, int x, int y, int& result){
        if(x>=obstacleGrid.size() || y>=obstacleGrid[0].size() || obstacleGrid[x][y]==1) return;
        if(x==obstacleGrid.size()-1 && y==obstacleGrid[0].size()-1){
            ++result;
            return;
        }

        dfs(obstacleGrid, x+1, y, result);
        dfs(obstacleGrid, x, y+1, result);
    }
};

int main()
{
    Solution2 a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    vector<vector<int>> map{
                          {0,0,0,0,0,1},
                          {0,1,0,1,1,0},
                          {0,0,0,1,0,0}
                                };
    cout<<a.uniquePathsWithObstacles(map);


}
