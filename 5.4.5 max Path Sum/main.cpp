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
///////// leetcode passed //////////////////////////////////
    int maxPathSum(TreeNode* root) {
        sum = INT_MIN;
        pathSum(root);
        return sum;
    }

    int sum;
    int pathSum(TreeNode* node) {
        if (!node) return 0;
        int left = max(0, pathSum(node -> left));
        int right = max(0, pathSum(node -> right));
        sum = max(sum, left + right + node -> val);
        return max(left, right) + node -> val;
    }
///////////////////////////////////////////////////////

    int maxPathSum(TreeNode *root) {
        max_sum = INT_MIN;
        dfs(root);
        return max_sum;
    }

    int max_sum;
    int dfs(const TreeNode *root) {
        if (root == nullptr) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        int sum = root->val;
        if (l > 0) sum += l;
        if (r > 0) sum += r;
        max_sum = max(max_sum, sum);
        return max(r, l) > 0 ? (max(r, l) + root->val) : root->val;
    }

//////// lc passed, clear thought  ///////////
    int max_res=INT_MIN;

    int maxPathSum(TreeNode *root) {
        dfs(root);
        return max_res;
    }

    int dfs(TreeNode* root){
        if(!root) return 0;

        int cur=root->val;

        int left=dfs(root->left);
        int right=dfs(root->right);

        int m=max(max(left+cur, right+cur), max(cur, left+right+cur)); /// four values comparison
        /// don't have to consider "left" or "right" solely, because they have been considered in dfs(root->left) and dfs(right child) !!!!!
        max_res=max(m, max_res); /// update final result;
        return max(max(left+cur, right+cur), cur); /// return needs to be chosen from 3 options: left+cur, right+cur, cur. Don't miss the cur.
    }
};


int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(-3);
    TreeNode* tree = new TreeNode(5,new TreeNode(4),
                                    new TreeNode(8));
    /*      6
        3       8
     1    4   7    9

    */

    cout<<a.maxPathSum(tree);


}
