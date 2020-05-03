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

////////////////////////////////////////
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right) return sum==root->val;
        bool left=false;
        bool right=false;
        if(root->left) left=hasPathSum(root->left, sum-(root->val));
        if(root->right) right=hasPathSum(root->right, sum-(root->val));

        return left || right;
    }
/////////////////////////////////////////////
    bool hasPathSum2(TreeNode *root, int sum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) // leaf
        return sum == root->val;
        return hasPathSum(root->left, sum - root->val)
                || hasPathSum(root->right, sum - root->val);
    }
////////////////////////////////////////////////
    bool hasPathSum3(TreeNode* root, int sum) {
            if(root==nullptr) return false;
            vector<pair<TreeNode*, int>> stack;
            auto cur=make_pair(root, root->val);

            while(cur.first || stack.size()){
                while(cur.first){
                    stack.push_back(cur);
                    if(cur.first->left==nullptr)
                        cur=make_pair(cur.first->left, 0);
                    else
                        cur=make_pair(cur.first->left, cur.second+cur.first->left->val);
                }

                auto node=stack.back();
                stack.pop_back();

                if(node.first->left==nullptr && node.first->right==nullptr)
                    if(node.second==sum)
                        return true;

                if(node.first->right) cur=make_pair(node.first->right, node.second+node.first->right->val);
            }

            return false;
    }
    ///////////////////////////////////////////////////
    bool hasPathSum5(TreeNode* root, int sum) {
        if(!root) return false;

        vector<TreeNode*> stack;
        int total=0;
        TreeNode* cur=root;
        TreeNode* prev=nullptr;

        while(cur || stack.size()){
            while(cur){
                stack.push_back(cur);
                total+=cur->val;
                cur=cur->left;
            }

            TreeNode* node=stack.back();

            if(node->right==nullptr || node->right==prev){
                if(node->left==nullptr && node->right==nullptr)
                    if(total==sum)
                        return true;
                stack.pop_back();
                total-=node->val;
                prev=node;
            }else if(node->right && prev!=node->right){
                cur=node->right;
            }
        }
        return false;
    }
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(1);
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.hasPathSum5(tree, 0);


        cout<<b<<" ";
}
