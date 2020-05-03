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
    bool CheckBalance(TreeNode* root)
    // LeetCode, Balanced Binary Tree
    // 时间复杂度 O(n)，空间复杂度 O(logn)
    {
        return balanceHeight(root) >=0;
    }

    int balanceHeight(TreeNode* node)
    {
        if(node==nullptr) return 0;

        int left  = balanceHeight(node->left);
        int right = balanceHeight(node->right);

        if(left <0 || right<0 || abs(left-right)>1) return -1;

        return max(left, right)+1;
    }
///////// leetcode passed, ////////
    bool isBalanced(TreeNode* root){
        return check(root)!=-1;
    }

    int check(TreeNode* root){
        if(!root) return 0;

        int left=check(root->left);
        int right=check(root->right);
        if(right==-1 || left==-1) return -1;

        return abs(left-right)>1 ? -1 : max(left,right)+1;
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, nullptr, nullptr),new TreeNode(8, new TreeNode(7, new TreeNode(3), new TreeNode(4)), new TreeNode(9, new TreeNode(3), new TreeNode(4))));

    /*      6
        3       8
              7    9
            3  4  3  4

    */

    auto b = a.CheckBalance(tree);

        cout<<b<<" ";
}
