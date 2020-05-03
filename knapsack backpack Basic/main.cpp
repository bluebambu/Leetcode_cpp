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

/*


Given n items with size Ai, an integer m denotes the size of a backpack. How full you can fill this backpack?
Notice

You can not divide any item into small pieces.


 Example

If we have 4 items with size [2, 3, 5, 7], the backpack size is 11, we can select [2, 3, 5], so that the max size we can fill this backpack is 10. If the backpack size is 12. we can select [2, 3, 7] so that we can fulfill the backpack.

You function should return the max size we can fill in the given backpack.
Challenge

O(n x m) time and O(m) memory.

O(n x m) memory is also acceptable if you do not know how to optimize memory.

*/

class Solution
{
public:
    ///////////  passed lintcode, not pass big data test  /////////////
    int backPack(int m, vector<int> A) {
        // write your code here
        int n=A.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0) );

        for(int i=1; i<n+1; ++i){
            for(int j=1; j<=m; ++j){
                int x = j-A[i-1]>=0 ? ( dp[i-1][j-A[i-1]] + A[i-1]) : 0;
                dp[i][j] = max(dp[i-1][j], x) ;
            }
        }

        return dp[n][m];
    }

    ////////////////// O(m) memory, lintcode passed  ////////////////////////
    int backPack(int m, vector<int> A) {
        // write your code here
        int n=A.size();
        vector<int> dp(m+1, 0);

        for(int i=1; i<n+1; ++i){
            for(int j=m; j>0; --j){
            // loop must be from high to low m value!!!!
                int x = j-A[i-1]>=0 ? (dp[j-A[i-1]] + A[i-1]) : 0;
                dp[j] = max(dp[j], x) ;
            }
        }

        return dp[m];
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
