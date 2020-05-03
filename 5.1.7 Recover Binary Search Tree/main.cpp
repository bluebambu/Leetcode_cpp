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
    TreeNode *first=nullptr, *firstnext=nullptr, *second=nullptr, *prev=nullptr;
public:
    void recoverTree(TreeNode* root){
        inorder(root);

        cout<<first<<endl<<firstnext<<endl<<second;

        if(second){
            swap(first->val, second->val);
        }else
            swap(first->val, firstnext->val);
    }

    void inorder(TreeNode* root) {
        if(!root) return;

        inorder(root->left);

        if(!first && prev && (prev->val > root->val)){
            first = prev;
            firstnext=root;
        }

        if(first && root!=firstnext && (prev->val > root->val)){
            second=root;
        }

        prev=root;

        inorder(root->right);
    }

///////////// leetcode passed, stack /////////
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> stack;
        TreeNode *cur=root, *prev=nullptr, *first=nullptr, *second=nullptr;

        while(cur ||  stack.size()){
            while(cur){
                stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node=stack.back();
            stack.pop_back();

            if(prev && node->val < prev->val && !first)
                first=prev;
            if(first && node->val < prev->val)
                second=node;

            prev=node;

            if(node->right) cur=node->right;
        }

        swap(first->val, second->val);
    }
//////////////// leetcode passed, morris traversal //////////////
    void recoverTree(TreeNode* root) {
        TreeNode *cur=root, *prev=nullptr, *first=nullptr, *second=nullptr;

        while(cur){
            if(!cur->left){
                compare(prev, cur, first, second);
                prev=cur;
                cur=cur->right;
            }else{
                TreeNode* node=cur->left;
                while(node->right && node->right!=cur){
                    node=node->right;
                }

                if(node->right==nullptr){
                    node->right=cur;
                    cur=cur->left;
                }else{
                    node->right=nullptr;
                    compare(prev, cur, first, second);
                    prev=cur;
                    cur=cur->right;
                }
            }
        }

        swap(first->val, second->val);
    }

    void compare(TreeNode *&prev, TreeNode *&cur, TreeNode *&first, TreeNode *&second){
        if(prev && cur->val < prev->val && !first)
            first=prev;
        if(first && cur->val < prev->val)
            second=cur;
    }
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.preorderTraversMorris(tree);

    for(auto i:b)
        cout<<i<<" ";
}
