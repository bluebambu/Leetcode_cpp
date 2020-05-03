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

/**
 Given a binary tree where all the right nodes are either leaf nodes with a sibling
 (a left node that shares the same parent node) or empty, flip it upside down and turn
 it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
       1
      / \
     2   3
    / \
   4   5

return the root of the binary tree [4,5,2,#,#,3,1].
4
/ \
5 2
  / \
 3 1

这题有一个重要的限制就是，整个数的任何一个右孩子都不会再生枝节，基本就是一个梳子的形状。

**/

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
    TreeNode* upsidedown(TreeNode* root) {
        if(!root) return nullptr;
        if(!root->left && !root->right) return root;

        TreeNode* top = upsidedown(root->left);

        TreeNode* left=root->left;

        if(left){
            left->left = root->right;
            left->right = root;
            root->left=nullptr;
            root->right=nullptr;
        }

        return top;
    }

    TreeNode* upsidedown2(TreeNode* root){
        TreeNode* cur=root, *next, *right=nullptr, *parent=nullptr;
        while(cur){
            next=cur->left;
            cur->left=right;
            right=cur->right;
            cur->right=parent;
            parent=cur;
            cur=next;
        }

        return parent;
    }

    ///////////////////////////////////////
    TreeNode* upsidedown3(TreeNode* root){
        if(!root) return nullptr;
        if(!root->left) return root;

        TreeNode* newroot = upsidedown3(root->left);

        if(root->left){
            root->left->left=root->right;
            root->left->right=root;
            root->left=nullptr;
            root->right=nullptr;
        }

        return newroot;
    }

    /////////////////////////////////////////
    TreeNode* upsidedown4(TreeNode* root){
        if(!root) return nullptr;

        TreeNode *cur=root,
                 *parent=nullptr,
                 *right=nullptr,
                 *next;

        while(cur){
            next=cur->left;
            cur->left=right;
            right=cur->right;
            cur->right=parent;
            parent=cur;
            cur=next;
        }

        return parent;
    }

};

void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8));
    /*      6
        3       8
     1    4

    */

    auto b=a.upsidedown4(tree);
    print(b);


}
