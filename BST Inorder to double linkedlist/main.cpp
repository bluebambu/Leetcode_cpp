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
    TreeNode* flatten(TreeNode* root){
        if(!root) return nullptr;
        if(!root->left && !root->right) return root;

        TreeNode* left=flatten(root->left);

        /// find the tail node of *left*
        if(left){
            TreeNode* p=left;
            while(p->right) p=p->right;
            p->right=root;
            root->left=p;
        }

        /// connect to the head node of *right*
        root->right=flatten(root->right);

        if(root->right) root->right->left=root;

        /// in case left is nullptr
        return left ? left : root;
    }


////////////// 乐神答案， ////////////////
    TreeNode* pre=nullptr;
    void flatten2(TreeNode* root){
        if(!root) return ;

        flatten(root->left);
        if(pre){
            pre->right = root;
            root->left = pre;
        }
        pre=root;
        flatten(root->right);
    }

};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),
                                    new TreeNode(8, nullptr, new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.flatten(tree);

    for(;b;b=b->right)
        cout<<b->val<<" ";
}
