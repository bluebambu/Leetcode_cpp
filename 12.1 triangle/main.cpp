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
    ////////// Leetcode passed ////////////////////
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()<1) return 0;
        if(triangle.size()<2) return triangle[0][0];

        int n=triangle.size(), m=triangle[n-1].size();
        vector<int> dp=triangle[n-1];

        for(int i=triangle.size()-2; i>=0; --i){
            for(int j=0 ; j<triangle[i].size(); ++j ){
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
    }

    ////////// Leetcode passed ////////////////////
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()<1) return 0;
        if(triangle.size()<2) return triangle[0][0];

        int n=triangle.size(), m=triangle[n-1].size();
        vector<vector<int>> dp=triangle;

        for(int i=dp.size()-2; i>=0; --i){
            for(int j=0 ; j<dp[i].size(); ++j ){
                dp[i][j] += min(dp[i+1][j], dp[i+1][j+1]);
            }
        }
        return dp[0][0];
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
