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

class Solution2 {
public:
    /// lc passed
    int sumNumbers(TreeNode* root) {
        int result=0;
        s(root, 0, result);
        return result;
    }

    void s(TreeNode* root, int upper, int& result){
        if(!root) return;
        if(!root->left && !root->right){
            result+= 10*upper + root->val;
            return;
        }
        s(root->left, 10*upper + root->val, result);
        s(root->right, 10*upper + root->val, result);
    }
};


class Solution
{
public:
///////////////// 错的答案。 root->val 等于 0 的时候错误！ ///////////
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        if(!root->left && !root->right) return root->val;
        int sum=0;

        if(root->left) {
            int left = sumNumbers(root->left)  ;
            int n=1;

            while(left/n){
                n*=10;
            }

            sum+=left+n*root->val;
        }

        if(root->right) {
            int right = sumNumbers(root->right)  ;
            int n=1;

            while(right/n){
                n*=10;
            }

            sum+=right+n*root->val;
        }
        return sum;
    }
///////////////////////////////////////////////
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }

    int helper(TreeNode* root, int prev){
        if(!root) return 0;
        if(!root->left && !root->right)
            return prev*10+(root->val);

        return helper(root->left, prev*10+(root->val)) + helper(root->right, prev*10+(root->val));
    }
/////////////////////////////////////////////////////

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
