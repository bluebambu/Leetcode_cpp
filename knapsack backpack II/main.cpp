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


Given n items with size Ai and value Vi, and a backpack with size m. What's the maximum value can you put into the backpack?
Notice

You cannot divide item into small pieces and the total size of items you choose should smaller or equal to m.
Have you met this question in a real interview?
Example

Given 4 items with size [2, 3, 5, 7] and value [1, 5, 2, 4], and a backpack with size 10. The maximum value is 9.

*/

class Solution
{
public:
    ////////// lintcode passed  ////////////////////
    int backPackII(int m, vector<int> A, vector<int> V) {
        // write your code here

        int n=A.size();
        vector<int> dp(m+1, 0);

        for(int i=1; i<=n; ++i){
            for(int j=m; j>0; --j){
                int x = j-A[i-1]>=0 ? (dp[j-A[i-1]]+V[i-1]) : 0;
                dp[j]=max(dp[j], x);
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
